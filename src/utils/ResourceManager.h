// ResourceManager.h
#pragma once
#include "raylib.h"

class ResourceManager {
public:
    // Texturas
    static Texture2D LoadTexture(const char* path);
    static void UnloadTexture(const char* path);

    // Modelos 3D
    static Model LoadModel(const char* path);
    static void UnloadModel(const char* path);

    // Sonidos
    static Sound LoadSound(const char* path);
    static void UnloadSound(const char* path);

    // Fuentes
    static Font LoadFont(const char* path);
    static void UnloadFont(const char* path);

    // Limpieza
    static void UnloadAll();
};

static Model LoadModelWithTextures(const char* modelPath, const char* texturePath);
static Shader LoadShader(const char* vsPath, const char* fsPath);