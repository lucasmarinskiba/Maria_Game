#include "FatimaLevel.h"
#include "raylib.h"
#include "NPC.h"
#include "MiracleSystem.h"
#include "ResourceManager.h"
#include "MathHelper.h"
#include <vector>

FatimaLevel::FatimaLevel() {
    // Crear NPCs con diálogos
    std::vector<std::string> luciaDialogs = {
        "¡Mira! Es la Virgen María...",
        "Rezad el rosario todos los días...",
        "El sol bailará como prueba..."
    };
    
    std::vector<std::string> franciscoDialogs = {
        "¡Qué hermosa es la Señora!",
        "Ofreceré sufrimientos por los pecadores..."
    };
    
    std::vector<std::string> jacintaDialogs = {
        "La Señora nos pide oración por los pecadores",
        "¡El corazón de María está triste!"
    };

    // Crear instancias de NPC
    npcs.push_back(NPC(Vector3{-5, 0, 3}, "Lucía", luciaDialogs));
    npcs.push_back(NPC(Vector3{0, 0, 5}, "Francisco", franciscoDialogs));
    npcs.push_back(NPC(Vector3{5, 0, 0}, "Jacinta", jacintaDialogs));
}

void FatimaLevel::Load() {
    // Cargar recursos usando ResourceManager
    groundTex = ResourceManager::LoadTexture("assets/fatima_ground.png");
    treeModel = ResourceManager::LoadModel("assets/tree.obj");
    miracleSound = ResourceManager::LoadSound("sounds/angelic_choir.wav");
    
    // Configurar NPCs
    for (auto& npc : npcs) {
        npc.LoadTexture("assets/npc_default.png");
    }
    
    // Configurar NPC Lucía específicamente
    NPC& lucia = npcs[0];
    lucia.SetStateTexture(NPCState::PRAYING, "assets/npc_pray.png");
    lucia.SetStateTexture(NPCState::AWE, "assets/npc_awe.png");
    
    lucia.SetInteractionCallback([]() {
        PlaySound(ResourceManager::GetSound("sounds/angel_choir.wav"));
        // player.AddFaith(20); // Descomentar cuando tengas referencia al jugador
    });

    // Posicionar jugador
    player.position = Vector3{0, 0, -5};
    
    // Cargar sonido de multitud
    crowdSound = ResourceManager::LoadSound("sounds/crowd.wav");
    SetSoundVolume(crowdSound, 0.7f);
    
    // Cargar modelo para el milagro del sol
    sunModel = ResourceManager::LoadModel("assets/sun_miracle.obj");
}

void FatimaLevel::Update(Vector3 playerPos) {
    // Verificar interacciones con NPCs
    if (IsKeyPressed(KEY_E)) {
        for (auto& npc : npcs) {
            if (Vector3Distance(playerPos, npc.GetPosition()) < 3.0f) {
                npc.Interact();
                activeNPC = &npc;
                // player.AddFaith(20); // Descomentar cuando tengas referencia al jugador
                break;
            }
        }
    }
    
    // Activar milagro con tecla M
    if (IsKeyPressed(KEY_M)) {
        miracleSystem.ActivateMiracle(
            MiracleType::DANCE_OF_SUN,
            Vector3{0, 10, 0},   // Posición sobre los niños
            50                    // Costo de fe
        );
        
        // Restar fe al jugador
        // player.AddFaith(-50); // Descomentar cuando tengas referencia al jugador
    }
    
    // Actualizar sistema de milagros
    miracleSystem.Update(GetFrameTime());
    
    // Verificar efectos en NPCs
    for (auto& npc : npcs) {
        if (miracleSystem.IsPositionAffected(
            npc.GetPosition(), 
            MiracleType::DANCE_OF_SUN
        )) {
            npc.SetState(NPCState::AWE); // Estado de asombro
        }
    }
}

void FatimaLevel::Draw() {
    // Dibujar terreno
    DrawPlane(Vector3{0, 0, 0}, Vector2{40, 40}, GREEN);
    
    // Dibujar árboles
    for (int i = -15; i <= 15; i += 5) {
        DrawModel(treeModel, Vector3{static_cast<float>(i), 0, -15}, 1.0f, GREEN);
        DrawModel(treeModel, Vector3{static_cast<float>(i), 0, 15}, 1.0f, GREEN);
        DrawModel(treeModel, Vector3{-15, 0, static_cast<float>(i)}, 1.0f, GREEN);
        DrawModel(treeModel, Vector3{15, 0, static_cast<float>(i)}, 1.0f, GREEN);
    }
    
    // Dibujar NPCs
    for (auto& npc : npcs) {
        npc.Draw();
    }
    
    // Dibujar milagro
    miracleSystem.Draw();
}

void FatimaLevel::DrawDialogue() {
    if (activeNPC && activeNPC->HasInteracted()) {
        DrawRectangle(0, 500, screenWidth, 120, Fade(BLACK, 0.7f));
        DrawText(activeNPC->GetName().c_str(), 50, 520, 30, YELLOW);
        DrawText(activeNPC->GetCurrentDialogue().c_str(), 50, 560, 25, WHITE);
        
        if (IsKeyPressed(KEY_ENTER)) {
            activeNPC->ResetInteraction();
            activeNPC = nullptr;
        }
    }
}

void FatimaLevel::Unload() {
    // Liberar recursos usando ResourceManager
    ResourceManager::UnloadTexture("assets/fatima_ground.png");
    ResourceManager::UnloadModel("assets/tree.obj");
    ResourceManager::UnloadSound("sounds/angelic_choir.wav");
    ResourceManager::UnloadSound("sounds/crowd.wav");
}

void FatimaLevel::AddEvents() {
    // Evento de la lluvia antes del milagro
    events.push_back(WeatherEvent("Lluvia intensa", -10));
    
    // Evento de la multitud
    events.push_back(CrowdEvent(5000, Vector3{0, 0, 10}));
}