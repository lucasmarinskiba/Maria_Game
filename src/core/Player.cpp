#include "Player.h"
#include "raylib.h"

Player::Player(Vector3 startPos) : position(startPos), faith(100) {}

void Player::Update() {
    // Movimiento WASD (C++ puro)
    float speed = 0.1f;
    if (IsKeyDown(KEY_W)) position.z -= speed;
    if (IsKeyDown(KEY_S)) position.z += speed;
    if (IsKeyDown(KEY_A)) position.x -= speed;
    if (IsKeyDown(KEY_D)) position.x += speed;
}

void Player::Draw() const {
    // Dibujado con Raylib (API C, pero llamada desde C++)
    DrawCube(position, 1.0f, 2.0f, 1.0f, BLUE);
    DrawCubeWires(position, 1.0f, 2.0f, 1.0f, DARKBLUE);
}