//NPCS.cpp
#include "NPC.h"
#include "ResourceManager.h"
#include "MathHelper.h"
#include <raylib.h>
#include <algorithm>

//---------------------------------------------------------
// Constructor
//---------------------------------------------------------
NPC::NPC(Vector3 position, std::string name, std::vector<std::string> dialogues) 
    : position(position), name(name), dialogues(dialogues), 
      currentDialogue(0), isInteractable(true), state(NPCState::IDLE) {
    
    // Configuración por defecto
    collisionRadius = 1.0f;
    interactRadius = 2.5f;
    rotationAngle = 0.0f;
    texture = ResourceManager::LoadTexture("assets/npc_default.png");
    model = ResourceManager::LoadModel("assets/npc_base.obj");
}

//---------------------------------------------------------
// Actualización lógica
//---------------------------------------------------------
void NPC::Update(float deltaTime, Vector3 playerPosition) {
    // Rotación suave hacia el jugador cuando está cerca
    if (MathHelper::Distance(position, playerPosition) < 5.0f) {
        Vector3 direction = {
            playerPosition.x - position.x,
            0,
            playerPosition.z - position.z
        };
        rotationAngle = atan2f(direction.x, direction.z) * RAD2DEG;
    }

    // Animación de flotación básica
    if (state == NPCState::IDLE) {
        float bounceHeight = sinf(GetTime() * 2.0f) * 0.1f;
        drawPosition = {position.x, position.y + bounceHeight, position.z};
    }

    // Resetear interacción si el jugador se aleja
    if (MathHelper::Distance(position, playerPosition) > interactRadius) {
        isInteractable = true;
    }
}

//---------------------------------------------------------
// Dibujado del NPC
//---------------------------------------------------------
void NPC::Draw() const {
    // Dibujar modelo con transformaciones
    Matrix transform = MatrixRotateY(rotationAngle * DEG2RAD);
    transform = MatrixMultiply(transform, MatrixTranslate(drawPosition.x, drawPosition.y, drawPosition.z));
    
    DrawModel(model, transform, 1.0f, WHITE);

    // Indicador de interacción
    if (isInteractable) {
        Vector3 indicatorPos = {position.x, position.y + 2.5f, position.z};
        DrawSphere(indicatorPos, 0.2f, YELLOW);
    }

    // Debug: Mostrar radio de interacción
    if (IsKeyDown(KEY_F3)) {
        DrawSphereWires(position, interactRadius, 8, 8, GREEN);
    }
}

//---------------------------------------------------------
// Interacción con el jugador
//---------------------------------------------------------
std::string NPC::Interact() {
    if (!isInteractable || dialogues.empty()) return "";

    // Rotar diálogos
    currentDialogue = (currentDialogue + 1) % dialogues.size();
    isInteractable = false;
    state = NPCState::TALKING;

    // Sonido de interacción
    PlaySound(ResourceManager::GetSound("sounds/npc_talk.wav"));

    return dialogues[currentDialogue];
}

//---------------------------------------------------------
// Cambiar estado del NPC
//---------------------------------------------------------
void NPC::SetState(NPCState newState) {
    state = newState;
    
    switch(state) {
        case NPCState::PRAYING:
            texture = ResourceManager::LoadTexture("assets/npc_pray.png");
            break;
            
        case NPCState::AWE: // Asombro (durante milagros)
            texture = ResourceManager::LoadTexture("assets/npc_awe.png");
            break;
            
        default:
            texture = ResourceManager::LoadTexture("assets/npc_default.png");
    }
}

//---------------------------------------------------------
// Sistema de diálogos
//---------------------------------------------------------
void NPC::AddDialogue(const std::string& dialogue) {
    dialogues.push_back(dialogue);
}

void NPC::ClearDialogues() {
    dialogues.clear();
    currentDialogue = 0;
}

//---------------------------------------------------------
// Gestión de colisiones
//---------------------------------------------------------
bool NPC::CheckCollision(Vector3 point) const {
    return MathHelper::Distance(position, point) <= collisionRadius;
}