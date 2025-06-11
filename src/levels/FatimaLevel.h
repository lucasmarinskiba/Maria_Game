//FatimaLevel.h
#pragma once

#include "raylib.h"           // Incluir primero
#include "NPC.h"
#include "MiracleSystem.h"
#include "ResourceManager.h"
#include "MathHelper.h"

#include <vector>
#include <memory>

class FatimaLevel {
public:
    FatimaLevel();
    ~FatimaLevel();

    void Load();       // Cargar recursos
    void Unload();     // Liberar recursos
    void Update(Vector3 playerPos);     // Actualizar lógica
    void Draw();       // Dibujar nivel
    void DrawUI();     // Dibujar interfaz
    void DrawDialogue();
    void AddEvents();
    void LoadSounds();
    void LoadModels();
    void LoadTextures();
    void LoadShaders();
    void LoadNPCs();
    void LoadMiracleSystem();
    void LoadPlayer();
    void LoadEnvironment();
    void LoadLighting();
    void LoadCamera();
    void LoadLevel();
    void LoadLevelAssets();
    void LoadLevelSettings();
    void LoadLevelResources();
    void LoadLevelNPCs();
    void LoadLevelMiracles();
    void LoadLevelUI();
    void LoadLevelEffects();
    void LoadLevelConfiguration();
    void LoadLevelData();
    void LoadLevelComponents();
    void LoadLevelEntities();
    void LoadLevelScripts();
    void LoadLevelLogic();
    void LoadLevelEvents();
    void LoadLevelInteractions();
    void LoadLevelAnimations();
    void LoadLevelAudio();
    void LoadLevelVisuals();

    
    // Jugador
    Vector3 GetPlayerStartPosition() const { return {0.0f, 0.0f, -8.0f}; }

    // NPCs
    const std::vector<NPC>& GetNPCs() const { return npcs; }

private:
    // NPCs
    std::vector<NPC> npcs;

    // Sistema de milagros
    MiracleSystem miracleSystem;

    // Recursos
    Model groundModel;
    Model treeModel;
    Model sunModel;
    Texture2D skybox;

    Sound crowdSound;
    Sound miracleSound;

    // Jugador (referencia externa)
    Vector3 playerPosition;

    // Diálogos
    NPC* activeNPC = nullptr;
    bool showDialogue = false;

    // Efectos
    Shader lightShader;
    RenderTexture2D lightMap;

    // Configuración
    const float levelRadius = 30.0f; // Radio del área jugable

    const int screenWidth = 1280;
    const int screenHeight = 720;
};

// Implementación de funciones clave (para evitar linking errors)
inline void FatimaLevel::Load() {
    // Cargar modelos y texturas
    groundModel = LoadModelFromMesh(GenMeshPlane(levelRadius * 2, levelRadius * 2, 10, 10));
    treeModel = LoadModel("assets/tree.obj");
    skybox = LoadTexture("assets/fatima_skybox.png");

    // Configurar NPCs
    npcs.push_back(NPC({-5.0f, 0.0f, 3.0f}, "Lucía", {
        "¡La Señora viene del cielo!",
        "Rezad el rosario cada día...",
        "El sol bailará para todos."
    }));

    npcs.push_back(NPC({3.0f, 0.0f, 0.0f}, "Francisco", {
        "No tengáis miedo...",
        "Ofreced sacrificios por los pecadores."
    }));

    // Cargar shader para efectos de luz
    lightShader = LoadShader("assets/light.vs", "assets/light.fs");
    lightMap = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());
}

inline void FatimaLevel::Update() {
    // Verificar interacción con NPCs
    if (IsKeyPressed(KEY_E)) {
        for (auto& npc : npcs) {
            if (Vector3Distance(playerPosition, npc.position) < 3.0f) {
                activeNPC = &npc;
                showDialogue = true;
                break;
            }
        }
    }

    // Actualizar milagros
    if (IsKeyPressed(KEY_M)) {
        miracleSystem.ActivateMiracle(
            MiracleType::DANCE_OF_SUN,
            {0.0f, 10.0f, 0.0f}, // Posición sobre el grupo
            50                    // Costo de fe
        );
    }
    miracleSystem.Update(GetFrameTime());
}

inline void FatimaLevel::Draw() {
    // Dibujar cielo
    DrawSkybox(skybox);

    // Dibujar terreno
    DrawModel(groundModel, {0.0f, -1.0f, 0.0f}, 1.0f, BEIGE);

    // Dibujar árboles alrededor
    for (float x = -levelRadius; x <= levelRadius; x += 5.0f) {
        DrawModel(treeModel, {x, 0.0f, -levelRadius}, 1.0f, DARKGREEN);
        DrawModel(treeModel, {x, 0.0f, levelRadius}, 1.0f, DARKGREEN);
    }

    // Dibujar NPCs
    for (const auto& npc : npcs) {
        npc.Draw();
    }

    // Dibujar milagros
    BeginShaderMode(lightShader);
    miracleSystem.Draw();
    EndShaderMode();
}

inline void FatimaLevel::DrawUI() {
    // Barra de fe
    DrawRectangle(10, 10, 200, 30, Fade(BLACK, 0.5f));
    DrawRectangle(10, 10, miracleSystem.GetFaith(), 30, GOLD);

    // Diálogos
    if (showDialogue && activeNPC) {
        DrawRectangle(0, GetScreenHeight() - 150, GetScreenWidth(), 150, Fade(BLACK, 0.8f));
        DrawText(activeNPC->name.c_str(), 50, GetScreenHeight() - 130, 30, YELLOW);
        DrawText(activeNPC->GetCurrentDialogue().c_str(), 50, GetScreenHeight() - 90, 25, WHITE);

        if (IsKeyPressed(KEY_ENTER)) {
            showDialogue = false;
        }
    }
}

inline void FatimaLevel::Unload() {
    UnloadModel(groundModel);
    UnloadModel(treeModel);
    UnloadTexture(skybox);
    UnloadShader(lightShader);
    UnloadRenderTexture(lightMap);
}