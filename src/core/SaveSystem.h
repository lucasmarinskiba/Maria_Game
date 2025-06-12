#pragma once
#include <fstream>
#include <string>
#include "raylib.h"

struct PlayerData {
    Vector3 position;
    float health, faith;
};

inline void SaveGame(const std::string& filepath, const PlayerData& data) {
    std::ofstream file(filepath, std::ios::binary);
    file.write((char*)&data, sizeof(PlayerData));
}

inline bool LoadGame(const std::string& filepath, PlayerData& data) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file.good()) return false;
    file.read((char*)&data, sizeof(PlayerData));
    return true;
}
