// MathHelper.h
#pragma once
#include "raylib.h"
#include <cmath>
#include <vector>

namespace MathHelper {
    ///////////////////////////////////////////////////////////
    // CONSTANTES ÚTILES
    ///////////////////////////////////////////////////////////
    constexpr float PI = 3.14159265358979323846f;
    constexpr float DEG2RAD = PI / 180.0f;
    constexpr float RAD2DEG = 180.0f / PI;

    ///////////////////////////////////////////////////////////
    // FUNCIONES BÁSICAS
    ///////////////////////////////////////////////////////////
    
    // Clamp entre mínimo y máximo
    inline float Clamp(float value, float min, float max) {
        return (value < min) ? min : (value > max) ? max : value;
    }

    // Interpolación lineal (lerp)
    inline float Lerp(float a, float b, float t) {
        return a + t * (b - a);
    }

    // Distancia entre dos puntos 3D
    inline float Distance(Vector3 a, Vector3 b) {
        return sqrtf((a.x - b.x) * (a.x - b.x) + 
                     (a.y - b.y) * (a.y - b.y) + 
                     (a.z - b.z) * (a.z - b.z));
    }

    // Normalizar un vector 3D
    inline Vector3 Normalize(Vector3 v) {
        float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
        return (length > 0) ? Vector3{v.x / length, v.y / length, v.z / length} : Vector3{0, 0, 0};
    }

    // Producto punto (dot product)
    inline float Dot(Vector3 a, Vector3 b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    ///////////////////////////////////////////////////////////
    // COLISIONES Y GEOMETRÍA
    ///////////////////////////////////////////////////////////
    
    // Verificar colisión esfera-esfera
    inline bool CheckSphereCollision(Vector3 center1, float radius1, Vector3 center2, float radius2) {
        return Distance(center1, center2) <= (radius1 + radius2);
    }

    // Verificar colisión esfera-cubo (AABB)
    inline bool CheckSphereAABBCollision(Vector3 sphereCenter, float sphereRadius, Vector3 boxMin, Vector3 boxMax) {
        float x = fmaxf(boxMin.x, fminf(sphereCenter.x, boxMax.x));
        float y = fmaxf(boxMin.y, fminf(sphereCenter.y, boxMax.y));
        float z = fmaxf(boxMin.z, fminf(sphereCenter.z, boxMax.z));
        
        return Distance(sphereCenter, Vector3{x, y, z}) < sphereRadius;
    }

    // Verificar si un punto está dentro de un círculo 2D
    inline bool IsPointInCircle(Vector2 point, Vector2 center, float radius) {
        return ((point.x - center.x) * (point.x - center.x) + 
                (point.y - center.y) * (point.y - center.y)) <= (radius * radius);
    }

    ///////////////////////////////////////////////////////////
    // INTERPOLACIONES AVANZADAS
    ///////////////////////////////////////////////////////////
    
    // Ease-In (suavizado al inicio)
    inline float EaseIn(float t, float power = 2.0f) {
        return powf(t, power);
    }

    // Ease-Out (suavizado al final)
    inline float EaseOut(float t, float power = 2.0f) {
        return 1.0f - powf(1.0f - t, power);
    }

    // Ease-In-Out (combinación)
    inline float EaseInOut(float t, float power = 2.0f) {
        return (t < 0.5f) ? 
               EaseIn(t * 2.0f, power) * 0.5f : 
               0.5f + EaseOut(t * 2.0f - 1.0f, power) * 0.5f;
    }

    ///////////////////////////////////////////////////////////
    // ÁNGULOS Y ROTACIONES
    ///////////////////////////////////////////////////////////
    
    // Ángulo entre dos vectores 2D (en grados)
    inline float AngleBetween(Vector2 a, Vector2 b) {
        float dot = a.x * b.x + a.y * b.y;
        float det = a.x * b.y - a.y * b.x;
        return atan2f(det, dot) * RAD2DEG;
    }

    // Rotar un punto alrededor de un centro (2D)
    inline Vector2 RotatePoint(Vector2 point, Vector2 center, float angleDegrees) {
        float angleRad = angleDegrees * DEG2RAD;
        float s = sinf(angleRad);
        float c = cosf(angleRad);

        point.x -= center.x;
        point.y -= center.y;

        float xNew = point.x * c - point.y * s;
        float yNew = point.x * s + point.y * c;

        return Vector2{xNew + center.x, yNew + center.y};
    }

    ///////////////////////////////////////////////////////////
    // RANDOM
    ///////////////////////////////////////////////////////////
    
    // Número aleatorio en rango [min, max]
    inline float RandomRange(float min, float max) {
        return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
    }

    // Vector3 aleatorio dentro de una esfera unitaria
    inline Vector3 RandomInUnitSphere() {
        return Vector3{
            RandomRange(-1.0f, 1.0f),
            RandomRange(-1.0f, 1.0f),
            RandomRange(-1.0f, 1.0f)
        };
    }
} // namespace MathHelper