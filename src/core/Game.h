//Game.h
#pragma once
#include "raylib.h"
#include <memory>
#include <array>

// Estados del juego
enum class GameState {
    MENU,
    FATIMA,
    GUADALUPE,
    LOURDES
};

// Forward declarations
class Level;

class Game {
public:
    Game();
    ~Game();

    void Run();

private:
    void ProcessInput();
    void Update(float deltaTime);
    void Render();
    void DrawMenu();
    void ChangeLevel(GameState newLevel);

    // Configuración
    const int screenWidth = 1280;
    const int screenHeight = 720;

    // Estado actual
    GameState currentState;
    bool isRunning;

    // Niveles
    std::array<std::unique_ptr<Level>, 4> levels;
};

// Para añadir nuevos niveles
levels[static_cast<int>(GameState::GUADALUPE)] = std::make_unique<GuadalupeLevel>();