#pragma once
#include "raylib.h"

inline bool CheckGroundCollision(Vector3 pos, float groundY = 0.0f) {
    return pos.y <= groundY;
}

inline void ApplyGravity(Vector3& pos, float& verticalSpeed, float groundY = 0.0f, float gravity = 18.0f, float delta = 1.0f/60) {
    verticalSpeed -= gravity * delta;
    pos.y += verticalSpeed * delta;
    if (CheckGroundCollision(pos, groundY)) {
        pos.y = groundY;
        verticalSpeed = 0.0f;
    }
}
