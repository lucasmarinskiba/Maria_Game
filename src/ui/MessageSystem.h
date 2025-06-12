#pragma once
#include <vector>
#include <string>
#include "raylib.h"

struct FloatingMessage {
    std::string text;
    Vector2 position;
    float timer;
};

class MessageSystem {
public:
    std::vector<FloatingMessage> messages;

    void AddMessage(const std::string& text, Vector2 pos) {
        messages.push_back({text, pos, 2.0f});
    }
    void Update(float delta) {
        for (auto& m : messages) m.timer -= delta;
        messages.erase(std::remove_if(messages.begin(), messages.end(),
            [](const FloatingMessage& m){ return m.timer < 0; }), messages.end());
    }
    void Draw() {
        for (const auto& m : messages)
            DrawText(m.text.c_str(), m.position.x, m.position.y - (2.0f - m.timer)*30, 20, YELLOW);
    }
};
