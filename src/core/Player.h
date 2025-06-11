//Player.h
#pragma once
#include "raylib.h"
#include "MathHelper.h"

class Player {
public:
    Vector3 position{0};
    int faith;
    
    Player(Vector3 startPos) : position(startPos), faith(100) {}  // Corregido: Vector3
    
    void Update() {
        // Movimiento básico
        if (IsKeyDown(KEY_W)) position.z -= 0.1f;
        if (IsKeyDown(KEY_S)) position.z += 0.1f;
        if (IsKeyDown(KEY_A)) position.x -= 0.1f;
        if (IsKeyDown(KEY_D)) position.x += 0.1f;

        // Mantener dentro del área - USANDO FUNCIÓN CORRECTA
        position.x = MathHelper::Clamp(position.x, -20.0f, 20.0f);
        position.z = MathHelper::Clamp(position.z, -20.0f, 20.0f);
    }
    
    void Draw() const {
        // Representación temporal de María - FUNCIONES CORRECTAS
        DrawCylinder(position, 0.5f, 0.5f, 2.0f, 10, BLUE);
        DrawSphere((Vector3){position.x, position.y + 1.5f, position.z}, 0.5f, SKYBLUE);
    }
    
    void AddFaith(int amount) {
        faith += amount;
        if (faith > 200) faith = 200;
    }
    
    int GetFaith() const { return faith; }
};