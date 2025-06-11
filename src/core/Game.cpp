//Game.cpp
#include "Game.h"
#include "FatimaLevel.h"
#include "ResourceManager.h"
#include "MathHelper.h"
#include <iostream>

//---------------------------------------------------------
// Constructor/Destructor
//---------------------------------------------------------
Game::Game() : currentState(GameState::MENU), isRunning(true) {
    InitWindow(screenWidth, screenHeight, "Apariciones Marianas");
    InitAudioDevice();
    SetTargetFPS(60);

    // Cargar recursos globales
    ResourceManager::LoadFont("fonts/pixel.ttf");
    ResourceManager::LoadSound("sounds/click.wav");

    // Inicializar niveles
    levels[static_cast<int>(GameState::FATIMA)] = std::make_unique<FatimaLevel>();
    levels[static_cast<int>(GameState::FATIMA)]->Load();
}

Game::~Game() {
    ResourceManager::UnloadAll();
    CloseAudioDevice();
    CloseWindow();
}

//---------------------------------------------------------
// Bucle principal
//---------------------------------------------------------
void Game::Run() {
    while (isRunning && !WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        ProcessInput();
        Update(deltaTime);
        Render();
    }
}

//---------------------------------------------------------
// Gestión de inputs
//---------------------------------------------------------
void Game::ProcessInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        if (currentState == GameState::MENU) isRunning = false;
        else currentState = GameState::MENU;
    }

    switch (currentState) {
        case GameState::MENU:
            if (IsKeyPressed(KEY_ENTER)) {
                currentState = GameState::FATIMA;
                PlaySound(ResourceManager::GetSound("sounds/click.wav"));
            }
            break;

        case GameState::FATIMA:
            levels[static_cast<int>(currentState)]->ProcessInput();
            break;
    }
}

//---------------------------------------------------------
// Función auxiliar en Game.cpp o PhysicsSystem.cpp
//---------------------------------------------------------
bool CheckCollision(const Player& player, const NPC& npc) {
    return MathHelper::Distance(
        player.GetPosition(),
        npc.GetPosition()
    ) <= npc.GetInteractRadius();
}

//---------------------------------------------------------
// Actualización lógica
//---------------------------------------------------------
void Game::Update(float deltaTime) {
    switch (currentState) {
        case GameState::FATIMA:
            levels[static_cast<int>(currentState)]->Update(deltaTime);
            break;
    }
    for (auto& npc : currentLevel->GetNPCs()) {
        npc.Update(deltaTime, player.GetPosition());
        
        // Verificar interacción
        if (npc.IsInteractable() && CheckCollision(player, npc)) {
            currentDialogue = npc.Interact();
        }
    }
}

//---------------------------------------------------------
// Renderizado
//---------------------------------------------------------
void Game::Render() {
    for (auto& npc : currentLevel->GetNPCs()) {
        npc.Draw();
    }
    
    if (!currentDialogue.empty()) {
        DrawText(currentDialogue.c_str(), screenWidth/2, 50, 20, WHITE);
    }

    BeginDrawing();
        ClearBackground(BLACK);

        switch (currentState) {
            case GameState::MENU:
                DrawMenu();
                break;

            case GameState::FATIMA:
                levels[static_cast<int>(currentState)]->Draw();
                break;
        }

        DrawFPS(10, 10);
    EndDrawing();
}

//---------------------------------------------------------
// Menú principal
//---------------------------------------------------------
void Game::DrawMenu() {
    Font font = ResourceManager::GetFont("fonts/pixel.ttf");
    const char* title = "APARICIONES MARIANAS";
    const char* subtitle = "Presiona ENTER para comenzar";

    Vector2 titleSize = MeasureTextEx(font, title, 48, 2);
    Vector2 subtitleSize = MeasureTextEx(font, subtitle, 24, 1);

    DrawTextEx(font, title, 
        Vector2{screenWidth/2 - titleSize.x/2, screenHeight/3}, 
        48, 2, GOLD);

    DrawTextEx(font, subtitle,
        Vector2{screenWidth/2 - subtitleSize.x/2, screenHeight/2},
        24, 1, WHITE);

    // Efecto parpadeante
    float alpha = 0.5f + sinf(GetTime() * 2) * 0.5f;
    DrawText(">", screenWidth/2 - 100, screenHeight/2 + 50, 30, Fade(WHITE, alpha));
}

//---------------------------------------------------------
// Gestión de niveles
//---------------------------------------------------------
void Game::ChangeLevel(GameState newLevel) {
    if (currentState != newLevel) {
        if (levels[static_cast<int>(currentState)]) {
            levels[static_cast<int>(currentState)]->Unload();
        }
        currentState = newLevel;
        levels[static_cast<int>(currentState)]->Load();
    }
}