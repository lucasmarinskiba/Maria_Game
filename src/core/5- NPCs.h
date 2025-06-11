// NPC.h
#pragma once
#include "raylib.h"
#include "MathHelper.h"
#include <string>
#include <vector>
#include <functional>

// Estados avanzados de NPC
enum class NPCState {
    IDLE,           // Estado normal
    WALKING,        // Moviéndose por rutas
    TALKING,        // En diálogo con jugador
    PRAYING,        // Orando (para escenas religiosas)
    AWE,            // Asombrado (durante milagros)
    FLEEING         // Huyendo (para eventos de persecución)
};

class NPC {
public:
    // Constructor completo
    NPC(Vector3 position, 
        std::string name, 
        std::vector<std::string> dialogues,
        float collisionRadius = 0.8f,
        float interactRadius = 2.5f);

    // --- Sistema principal ---
    void Update(float deltaTime, Vector3 playerPosition);
    void Draw() const;
    
    // --- Interacción ---
    std::string Interact();  // Devuelve el diálogo actual
    void ResetInteraction(); // Permite reiniciar la interacción
    
    // --- Estado y comportamiento ---
    void SetState(NPCState newState);
    NPCState GetState() const { return state; }
    
    // --- Diálogos dinámicos ---
    void AddDialogue(const std::string& dialogue);
    void SetDialogues(const std::vector<std::string>& newDialogues);
    void ClearDialogues();
    
    // --- Movimiento y posición ---
    void MoveTo(Vector3 target, float speed);
    bool ReachedDestination() const;
    
    // --- Getters ---
    Vector3 GetPosition() const { return position; }
    std::string GetName() const { return name; }
    bool IsInteractable() const { return isInteractable; }

    // --- Sistema de eventos ---
    void SetInteractionCallback(std::function<void()> callback);

private:
    // Datos básicos
    Vector3 position;
    Vector3 targetPosition;
    std::string name;
    
    // Diálogos
    std::vector<std::string> dialogues;
    size_t currentDialogue;
    
    // Física e interacción
    float collisionRadius;
    float interactRadius;
    float movementSpeed;
    
    // Estado
    NPCState state;
    bool isInteractable;
    
    // Gráficos
    Model model;
    Texture2D texture;
    Texture2D stateTextures[6]; // Texturas por estado
    
    // Animación
    float animationTime;
    Vector3 drawOffset; // Para efectos de flotación
    
    // Callback
    std::function<void()> onInteract;

    // Métodos internos
    void UpdateAnimation(float deltaTime);
    void LoadDefaultModel();
};