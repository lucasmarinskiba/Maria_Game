#pragma once
#include "raylib.h"
#include <vector>

struct Interactable {
    Vector3 position;
    float radius;
    std::string prompt;
    void (*onInteract)();
};

class InteractionSystem {
public:
    std::vector<Interactable> objects;

    int FindNearby(const Vector3& playerPos) {
        for (size_t i=0; i<objects.size(); ++i)
            if (Vector3Distance(objects[i].position, playerPos) < objects[i].radius)
                return i;
        return -1;
    }
    void DrawPrompt(int idx, int screenWidth, int screenHeight) {
        if (idx >= 0)
            DrawText(objects[idx].prompt.c_str(), screenWidth/2-60, screenHeight-60, 18, LIGHTGRAY);
    }
};
