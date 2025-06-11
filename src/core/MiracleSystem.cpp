// MiracleSystem.cpp
#include "MiracleSystem.h"
#include "ResourceManager.h"
#include <math.h>

MiracleSystem::MiracleSystem() {
    // Cargar shaders y texturas
    miracleShader = LoadShader(0, "assets/shaders/miracle.fs");
    particlesRT = LoadRenderTexture(256, 256);
}

void MiracleSystem::LoadResources() {
    sunModel = ResourceManager::LoadModel("sun");
    waterSpringModel = ResourceManager::LoadModel("water_spring");
    holyImage = ResourceManager::LoadTexture("tilma");
    miracleSound = ResourceManager::LoadSound("miracle_effect");
}

bool MiracleSystem::ActivateMiracle(
    MiracleType type, 
    Vector3 position, 
    int& faithPoints
) {
    // Verificar costo de fe
    auto costIt = FAITH_COSTS.find(type);
    if (costIt == FAITH_COSTS.end() || faithPoints < costIt->second) {
        return false;
    }
    
    // Crear nuevo efecto
    MiracleEffect newEffect;
    newEffect.position = position;
    newEffect.isActive = true;
    
    // Configurar según tipo
    switch(type) {
        case MiracleType::DANCE_OF_SUN:
            newEffect.radius = 15.0f;
            newEffect.duration = 10.0f;
            SetupDanceOfSun(newEffect);
            break;
            
        case MiracleType::HEALING_SPRING:
            newEffect.radius = 8.0f;
            newEffect.duration = 20.0f;
            SetupHealingSpring(newEffect);
            break;
            
        case MiracleType::HOLY_IMAGE:
            newEffect.radius = 5.0f;
            newEffect.duration = 9999.0f; // Permanente
            SetupHolyImage(newEffect);
            break;
            
        // ... otros milagros
    }
    
    // Aplicar costo de fe
    faithPoints -= costIt->second;
    PlaySound(miracleSound);
    
    // Añadir a efectos activos
    activeEffects.push_back(newEffect);
    return true;
}

void MiracleSystem::SetupDanceOfSun(MiracleEffect& effect) {
    effect.onActivate = []() {
        // Cambiar iluminación global
        SetAmbientLight(0.8f, 0.8f, 0.8f, 1.0f);
    };
    
    effect.onUpdate = [](float delta) {
        // Efecto de temblor en cámara
        float shakeIntensity = sinf(GetTime() * 10.0f) * 0.05f;
        Camera3D cam = GetCamera();
        cam.position.x += shakeIntensity;
        cam.position.z += shakeIntensity;
        SetCamera(cam);
    };
    
    effect.onEnd = []() {
        // Restaurar iluminación
        SetAmbientLight(0.4f, 0.4f, 0.4f, 1.0f);
    };
}

void MiracleSystem::SetupHealingSpring(MiracleEffect& effect) {
    effect.onActivate = [&effect]() {
        // Crear fuente de agua
        effect.position.y -= 1.0f; // Ajustar al suelo
    };
    
    effect.onUpdate = [](float delta) {
        // Generar partículas de agua
        // (implementar sistema de partículas)
    };
    
    effect.onEnd = []() {
        // Eliminar efectos visuales
    };
}

void MiracleSystem::Update(float deltaTime) {
    for (auto& effect : activeEffects) {
        if (!effect.isActive) continue;
        
        effect.elapsed += deltaTime;
        
        // Ejecutar lógica de actualización
        if (effect.onUpdate) {
            effect.onUpdate(deltaTime);
        }
        
        // Finalizar efecto si expira
        if (effect.elapsed >= effect.duration) {
            effect.isActive = false;
            if (effect.onEnd) {
                effect.onEnd();
            }
        }
    }
    
    // Eliminar efectos inactivos
    activeEffects.erase(
        std::remove_if(
            activeEffects.begin(),
            activeEffects.end(),
            [](const MiracleEffect& e) { return !e.isActive; }
        ),
        activeEffects.end()
    );
}

void MiracleSystem::Draw() {
    BeginShaderMode(miracleShader);
    
    for (const auto& effect : activeEffects) {
        if (!effect.isActive) continue;
        
        switch(GetMiracleType(effect)) { // Función auxiliar
            case MiracleType::DANCE_OF_SUN:
                DrawModel(sunModel, effect.position, 2.0f, YELLOW);
                break;
                
            case MiracleType::HEALING_SPRING:
                DrawModel(waterSpringModel, effect.position, 1.0f, BLUE);
                break;
                
            case MiracleType::HOLY_IMAGE:
                DrawBillboard(
                    GetCamera(),
                    holyImage,
                    effect.position,
                    5.0f,
                    WHITE
                );
                break;
        }
    }
    
    EndShaderMode();
}