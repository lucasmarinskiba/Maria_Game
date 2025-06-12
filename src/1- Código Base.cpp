#include "raylib.h"
#include "Player.h"
#include "NPC.h"
#include "FatimaLevel.h"
#include "MathHelper.h"

int main() {
    // Inicialización
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Aparición de Fátima");
    SetTargetFPS(60);

    // Cargar nivel de Fátima
    FatimaLevel fatimaLevel;
    fatimaLevel.Load();

    // Jugador (Virgen María)
    Player maria = fatimaLevel.GetPlayer();

    Vector3 playerPos = fatimaLevel.GetPlayerStartPosition();

    // Bucle principal
    while (!WindowShouldClose()) {
        // Actualizar
        maria.Update();
        fatimaLevel.Update(maria.position);
        
        if (IsKeyDown(KEY_W)) playerPos.z -= 0.1f;
        if (IsKeyDown(KEY_S)) playerPos.z += 0.1f;

        fatimaLevel.Update();

        // Dibujado
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // Dibujar nivel
            fatimaLevel.Draw();
            fatimaLevel.DrawUI();

            // Dibujar jugador
            maria.Draw();
            
            // UI
            DrawText(TextFormat("Fe: %i", maria.GetFaith()), 20, 20, 30, GOLD);
            DrawText("Fátima, Portugal - 1917", 20, 60, 25, DARKGRAY);
            DrawText("Presiona E para interactuar", 20, 100, 20, DARKGREEN);
            DrawText("Presiona M para realizar milagro", 20, 130, 20, BLUE);
            
            // Diálogos
            fatimaLevel.DrawDialogue();
            
        EndDrawing();
    }

    fatimaLevel.Unload();
    CloseWindow();
    return 0;
}

    SetTargetFPS(60);

    // Bucle principal del juego
    while (!WindowShouldClose()) {
        // Movimiento (ejemplo básico)
        if (IsKeyDown(KEY_W)) playerPosition.z -= 0.1f;
        if (IsKeyDown(KEY_S)) playerPosition.z += 0.1f;
        if (IsKeyDown(KEY_A)) playerPosition.x -= 0.1f;
        if (IsKeyDown(KEY_D)) playerPosition.x += 0.1f;

        // Milagro: Crear tilma (tecla E)
        if (IsKeyPressed(KEY_E) && faithPoints >= 20) {
            faithPoints -= 20;
            DrawTexture(tilma, screenWidth/2, screenHeight/2, WHITE);
            // Lógica del milagro aquí
        }

        // Declara e inicializa una instancia
        ThirdPersonCamera tpcam;
        
        // Dibujado
        BeginDrawing();
            ClearBackground(SKYBLUE);
            tpcam.Update(player.position);
            BeginMode3D(tpcam.GetCamera());
                DrawModel(maria, playerPosition, 1.0f, WHITE);
                DrawGrid(20, 1.0f); // Suelo
            EndMode3D();

            DrawHUD(player.health, player.maxHealth, player.faith, player.maxFaith);
            // UI: Puntos de Fe
            DrawText(TextFormat("Fe: %i", faithPoints), 20, 20, 30, GOLD);
        EndDrawing();
    }

    UnloadModel(maria);
    CloseWindow();
    return 0;
}

// Sistema de diálogos con NPCs
void showDialogue(const char* character, const char* message) {
    DrawRectangle(0, screenHeight-150, screenWidth, 150, Fade(BLACK, 0.5f));
    DrawText(character, 50, screenHeight-130, 30, YELLOW);
    DrawText(message, 50, screenHeight-80, 25, WHITE);
}

// Sistema de colección de objetos
if (CheckCollision(player, rose)) {
    faithPoints += 10;
    PlaySound(collectSfx);
}


class Player {
public:
    Vector3 position;
    int faith;
    
    Player(Vector3 startPos) : position(startPos), faith(100) {}
    
    void Update() {
        // Movimiento básico
        if (IsKeyDown(KEY_W)) position.z -= 0.1f;
        if (IsKeyDown(KEY_S)) position.z += 0.1f;
        if (IsKeyDown(KEY_A)) position.x -= 0.1f;
        if (IsKeyDown(KEY_D)) position.x += 0.1f;
        
        // Mantener dentro del área
        position.x = Clamp(position.x, -20, 20);
        position.z = Clamp(position.z, -20, 20);
    }
    
    void Draw() {
        // Representación temporal de María
        DrawCylinder(position, 0.5f, 0.5f, 2.0f, 10, BLUE);
        DrawSphere({position.x, position.y + 1.5f, position.z}, 0.5f, SKYBLUE);
    }
    
    void AddFaith(int amount) {
        faith += amount;
        if (faith > 200) faith = 200;
    }
    
    int GetFaith() const { return faith; }
};


class NPC {
public:
    std::string name;
    Vector3 position;
    std::vector<std::string> dialogues;
    Texture2D texture;
    
    void Draw() {
        DrawTexture(texture, position.x, position.z, WHITE);
    }
    
    void Interact(Player* player) {
        if (CheckCollision(player->position, this->position)) {
            // Mostrar diálogo aleatorio
            int randomIndex = rand() % dialogues.size();
            DrawDialog(dialogues[randomIndex]);
            
            // Ejemplo: Bendición al jugador
            player->faith += 10;
        }
    }
};

class Item {
public:
    enum Type { ROSA, AGUA_BENDITA, TILMA, VELA };
    Type type;
    Texture2D icon;
    
    void Use(Player* player) {
        switch(type) {
            case ROSA:
                player->health += 20;
                break;
            case AGUA_BENDITA:
                // Purificar enemigos cercanos
                break;
        }
    }
};

void Player::CastMiracle(MiracleType type) {
    if (faith >= type.cost) {
        faith -= type.cost;
        
        switch(type) {
            case HEAL:
                // Curar NPCs en área
                break;
            case LIGHT_STRIKE:
                // Daño a entidades oscuras
                break;
            case WATER_BLESS:
                // Crear fuente de agua curativa
                break;
        }
    }
}

class Quest {
    std::string title;
    bool completed;
    std::function<bool()> checkCompletion;
};

class QuestSystem {
public:
    struct Quest {
        string title;
        string description;
        bool completed;
        function<bool()> checkCompletion;
    };
    
    vector<Quest> activeQuests;
    
    void AddQuest(string title, string desc, function<bool()> checker) {
        activeQuests.push_back({title, desc, false, checker});
    }
};

if (MathHelper::CheckSphereCollision(miraclePos, 3.0f, npcPos, 1.5f)) {
    npc.Heal(20); // Cura al NPC
}

cameraPosition.x = MathHelper::Lerp(cameraPosition.x, targetPosition.x, 0.1f);

Vector3 particlePos = MathHelper::RandomInUnitSphere();

float angle = MathHelper::AngleBetween(
    {maria.x, maria.z}, 
    {target.x, target.z}
);

float distance = MathHelper::Distance(playerPos, enemyPos);

// Por ejemplo al apretar una tecla:
if (IsKeyPressed(KEY_SPACE)) {
    combatSystem.PlayerAttack(player.position, 2.0f, 30.0f);
}

messageSys.AddMessage("¡Pulsa E para interactuar!", {screenWidth/2-80, screenHeight-100});
messageSys.Update(GetFrameTime());
messageSys.Draw();

ApplyGravity(player.position, player.verticalSpeed);
