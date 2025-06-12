#include "CombatSystem.h"

void Enemy::Update(const Vector3& playerPos) {
    // Movimiento simple hacia el jugador
    if (!alive) return;
    Vector3 dir = Vector3Subtract(playerPos, position);
    float length = sqrtf(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
    if (length > 0.1f) {
        dir = Vector3Scale(dir, 0.03f/length);
        position = Vector3Add(position, dir);
    }
}

void Enemy::TakeDamage(float dmg) {
    health -= dmg;
    if (health <= 0) alive = false;
}

void CombatSystem::Update(const Vector3& playerPos) {
    for (auto& e : enemies) e.Update(playerPos);
}

void CombatSystem::PlayerAttack(Vector3 attackPos, float radius, float damage) {
    for (auto& e : enemies) {
        if (e.alive && Vector3Distance(e.position, attackPos) < radius) {
            e.TakeDamage(damage);
        }
    }
}
