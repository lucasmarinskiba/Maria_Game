// MiracleSystem.h
#pragma once
#include "raylib.h"
#include <vector>
#include <functional>
#include <string>

class MiracleSystem {
public:
    bool isActive = false;
    float duration = 0.0f;
    float maxDuration = 5.0f;
    Vector3 position;
    
    void Activate(Vector3 pos, int faithCost) {
        if (!isActive) {
            position = pos;
            isActive = true;
            duration = maxDuration;
        }
    }
    
    void Update() {
        if (isActive) {
            duration -= GetFrameTime();
            if (duration <= 0) {
                isActive = false;
            }
        }
    }
    
    void Draw() {
        if (isActive) {
            // Efecto visual del milagro (danza del sol)
            DrawSphere(position, 3.0f + sin(GetTime()*5)*0.5f, YELLOW);
            DrawRing(position, 4.0f, 6.0f, 0, 360, 32, Fade(GOLD, 0.5f));
        }
    }
};

// Tipos de milagros disponibles
enum class MiracleType {
    DANCE_OF_SUN,   // Danza del sol (Fátima)
    HEALING_SPRING, // Fuente curativa (Lourdes)
    HOLY_IMAGE,     // Imagen sagrada (Guadalupe)
    PROTECTION,      // Protección divina (La Vang)
    LIGHT_STRIKE    // Rayo de luz (combate)
};

struct MiracleEffect {
    Vector3 position;
    float radius;
    float duration;
    float elapsed = 0.0f;
    bool isActive = false;
    
    // Función de efecto personalizado
    std::function<void()> onActivate;
    std::function<void(float)> onUpdate;
    std::function<void()> onEnd;
};

class MiracleSystem {
public:
    MiracleSystem();
    ~MiracleSystem();
    
    // Inicialización con recursos
    void LoadResources();
    
    // Activar un milagro
    bool ActivateMiracle(
        MiracleType type, 
        Vector3 position, 
        int& faithPoints
    );
    
    // Actualizar efectos
    void Update(float deltaTime);
    
    // Dibujar efectos
    void Draw();
    
    // Verificar si un punto está afectado por un milagro
    bool IsPositionAffected(Vector3 position, MiracleType type) const;
    
    // Obtener milagros activos
    const std::vector<MiracleEffect>& GetActiveMiracles() const;

private:
    std::vector<MiracleEffect> activeEffects;
    
    // Texturas y modelos
    Model sunModel;
    Model waterSpringModel;
    Texture2D holyImage;
    Sound miracleSound;
    
    // Partículas
    Shader miracleShader;
    RenderTexture2D particlesRT;
    
    // Configuraciones
    const std::unordered_map<MiracleType, int> FAITH_COSTS = {
        {MiracleType::DANCE_OF_SUN, 50},
        {MiracleType::HEALING_SPRING, 40},
        {MiracleType::HOLY_IMAGE, 60},
        {MiracleType::PROTECTION, 30},
        {MiracleType::LIGHT_STRIKE, 25}
    };
    
    // Inicializar efectos específicos
    void SetupDanceOfSun(MiracleEffect& effect);
    void SetupHealingSpring(MiracleEffect& effect);
    void SetupHolyImage(MiracleEffect& effect);
};

