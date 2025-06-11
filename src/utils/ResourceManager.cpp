//ResourceManager.cpp
#include "ResourceManager.h"
#include <unordered_map>
#include <string>
#include "raylib.h"

// Mapa de recursos cargados
namespace {
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, Model> models;
    std::unordered_map<std::string, Sound> sounds;
    std::unordered_map<std::string, Font> fonts;
}

//---------------------------------------------------------
// Texturas
//---------------------------------------------------------
Texture2D ResourceManager::LoadTexture(const char* path) {
    auto it = textures.find(path);
    if (it != textures.end()) {
        return it->second; // Ya cargada
    }

    Texture2D tex = LoadTexture(path);
    textures[path] = tex;
    return tex;
}

void ResourceManager::UnloadTexture(const char* path) {
    auto it = textures.find(path);
    if (it != textures.end()) {
        UnloadTexture(it->second);
        textures.erase(it);
    }
}

//---------------------------------------------------------
// Modelos 3D
//---------------------------------------------------------
Model ResourceManager::LoadModel(const char* path) {
    auto it = models.find(path);
    if (it != models.end()) {
        return it->second;
    }

    Model model = LoadModel(path);
    models[path] = model;
    return model;
}

void ResourceManager::UnloadModel(const char* path) {
    auto it = models.find(path);
    if (it != models.end()) {
        UnloadModel(it->second);
        models.erase(it);
    }
}

//---------------------------------------------------------
// Sonidos
//---------------------------------------------------------
Sound ResourceManager::LoadSound(const char* path) {
    auto it = sounds.find(path);
    if (it != sounds.end()) {
        return it->second;
    }

    Sound sound = LoadSound(path);
    sounds[path] = sound;
    return sound;
}

void ResourceManager::UnloadSound(const char* path) {
    auto it = sounds.find(path);
    if (it != sounds.end()) {
        UnloadSound(it->second);
        sounds.erase(it);
    }
}

//---------------------------------------------------------
// Fuentes
//---------------------------------------------------------
Font ResourceManager::LoadFont(const char* path) {
    auto it = fonts.find(path);
    if (it != fonts.end()) {
        return it->second;
    }

    Font font = LoadFont(path);
    fonts[path] = font;
    return font;
}

void ResourceManager::UnloadFont(const char* path) {
    auto it = fonts.find(path);
    if (it != fonts.end()) {
        UnloadFont(it->second);
        fonts.erase(it);
    }
}

//---------------------------------------------------------
// Limpieza total
//---------------------------------------------------------
void ResourceManager::UnloadAll() {
    for (auto& pair : textures) UnloadTexture(pair.second);
    for (auto& pair : models) UnloadModel(pair.second);
    for (auto& pair : sounds) UnloadSound(pair.second);
    for (auto& pair : fonts) UnloadFont(pair.second);

    textures.clear();
    models.clear();
    sounds.clear();
    fonts.clear();
}