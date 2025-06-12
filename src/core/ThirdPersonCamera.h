#pragma once
#include "raylib.h"
#include "MathHelper.h"

class ThirdPersonCamera {
public:
    Camera3D camera;
    float distance = 8.0f;        // Distancia detrás del jugador
    float height = 3.0f;          // Altura respecto al jugador
    float minDistance = 4.0f;
    float maxDistance = 15.0f;
    float yaw = 0.0f;             // Rotación horizontal (grados)
    float pitch = 15.0f;          // Rotación vertical (grados)
    float pitchMin = -10.0f;
    float pitchMax = 60.0f;
    float sensitivity = 0.3f;
    float lerpSpeed = 0.15f;      // Suavizado de cámara

    ThirdPersonCamera() {
        camera.fovy = 60.0f;
        camera.up = Vector3{0,1,0};
        camera.projection = CAMERA_PERSPECTIVE;
    }

    void Update(const Vector3& targetPosition) {
        // Rotación con el mouse
        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            yaw   -= GetMouseDelta().x * sensitivity;
            pitch -= GetMouseDelta().y * sensitivity;
            pitch = MathHelper::Clamp(pitch, pitchMin, pitchMax);
        }

        // Zoom con rueda del mouse
        distance += GetMouseWheelMove() * -1.0f;
        distance = MathHelper::Clamp(distance, minDistance, maxDistance);

        // Calcular offset de cámara usando ángulos
        float radYaw = DEG2RAD * yaw;
        float radPitch = DEG2RAD * pitch;

        Vector3 offset = {
            distance * sinf(radYaw) * cosf(radPitch),
            distance * sinf(radPitch) + height,
            distance * cosf(radYaw) * cosf(radPitch)
        };

        Vector3 desiredPos = Vector3Add(targetPosition, offset);

        // Suavizar la transición (lerp)
        camera.position.x = MathHelper::Lerp(camera.position.x, desiredPos.x, lerpSpeed);
        camera.position.y = MathHelper::Lerp(camera.position.y, desiredPos.y, lerpSpeed);
        camera.position.z = MathHelper::Lerp(camera.position.z, desiredPos.z, lerpSpeed);

        camera.target = Vector3Add(targetPosition, Vector3{0,1.5f,0}); // Mira a la cabeza del jugador
    }

    const Camera3D& GetCamera() const { return camera; }
};
