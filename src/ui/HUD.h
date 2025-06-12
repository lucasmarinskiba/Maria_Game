#pragma once
#include "raylib.h"

inline void DrawBar(float x, float y, float width, float height, float percent, Color colorFill, Color colorBg) {
    DrawRectangle(x, y, width, height, colorBg);
    DrawRectangle(x, y, width * percent, height, colorFill);
}

inline void DrawHUD(float health, float maxHealth, float faith, float maxFaith) {
    DrawBar(20, 20, 200, 24, health / maxHealth, RED, DARKGRAY);
    DrawText("Salud", 24, 22, 18, WHITE);

    DrawBar(20, 50, 200, 14, faith / maxFaith, SKYBLUE, DARKGRAY);
    DrawText("Fe", 24, 52, 12, WHITE);
}
