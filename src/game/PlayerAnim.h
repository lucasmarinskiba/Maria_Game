#pragma once
#include "raylib.h"

class PlayerAnim {
public:
    Model model;
    ModelAnimation* anims;
    int animCount;
    int currentAnim = 0;
    float animFrame = 0.0f;

    void Update(float delta) {
        animFrame += 10.0f * delta;
        if (animFrame >= anims[currentAnim].frameCount) animFrame = 0;
        UpdateModelAnimation(model, anims[currentAnim], (int)animFrame);
    }
    void Draw(Vector3 pos) {
        DrawModel(model, pos, 1.0f, WHITE);
    }
};
