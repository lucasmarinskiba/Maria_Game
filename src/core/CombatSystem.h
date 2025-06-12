#pragma once
#include "raylib.h"
#include <vector>

class Enemy {
public:
    Vector3 position;
    float health = 100.0f;
    bool alive = true;

    void Update(const Vector3& playerPos);
    void TakeDamage(float dmg);
};

class CombatSystem {
public:
    std::vector<Enemy> enemies;

    void Update(const Vector3& playerPos);
    void PlayerAttack(Vector3 attackPos, float radius, float damage);
};
