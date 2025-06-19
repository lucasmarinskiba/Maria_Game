#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <string>
#include "Player.h"
#include "NPC.h"
#include "Level.h"
#include "QuestSystem.h"
#include "ResourceManager.h"
#include "HUD.h"

// Estados del juego
enum class GameState {
    MENU,
    FATIMA,
    GUADALUPE,
    LOURDES
};

// Simple función para mostrar texto centrado
void drawTextCentered(sf::RenderWindow& window, sf::Font& font, const std::string& text, unsigned size, float y, sf::Color color) {
    sf::Text sfText(text, font, size);
    sf::FloatRect bounds = sfText.getLocalBounds();
    sfText.setOrigin(bounds.width / 2, bounds.height / 2);
    sfText.setPosition(window.getSize().x / 2, y);
    sfText.setFillColor(color);
    window.draw(sfText);
}

int main() {
    // Inicialización de ventana y recursos globales
    int screenWidth = 1280, screenHeight = 720;
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Apariciones Marianas");
    window.setFramerateLimit(60);

    // Recursos globales
    ResourceManager resourceManager;
    sf::Font mainFont = resourceManager.loadFont("assets/fonts/pixel.ttf");
    sf::SoundBuffer clickBuffer;
    clickBuffer.loadFromFile("assets/sounds/click.wav");
    sf::Sound clickSound(clickBuffer);

    // Estados y sistemas principales
    GameState currentState = GameState::MENU;
    bool running = true;

    // Niveles
    std::unique_ptr<Level> fatimaLevel = std::make_unique<FatimaLevel>(resourceManager);
    // Puedes agregar más niveles aquí

    // Jugador
    Player player(resourceManager); // asegúrate de tener constructor adecuado

    // NPCs y sistema de misiones
    std::vector<NPC> npcs; // Llénalo según el nivel
    QuestSystem questSystem;

    // HUD
    // Suponiendo que tienes un HUD adaptado a SFML

    // Variables de juego
    float playerHealth = player.getMaxHealth();
    float playerFaith = player.getMaxFaith();
    std::string currentDialogue;

    // Música de fondo (opcional)
    sf::Music bgMusic;
    bgMusic.openFromFile("assets/music/background.ogg");
    bgMusic.setLoop(true);
    bgMusic.play();

    while (window.isOpen() && running) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                running = false;
                window.close();
            }

            // Menú principal
            if (currentState == GameState::MENU) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    currentState = GameState::FATIMA;
                    clickSound.play();
                }
            }
        }

        // --- LÓGICA DE JUEGO ---
        float deltaTime = 1.0f / 60.0f; // O usa clock.getElapsedTime()
        if (currentState == GameState::FATIMA) {
            // Actualización de jugador
            player.update(deltaTime, window);

            // Actualización de NPCs
            for (auto& npc : npcs) {
                npc.update(deltaTime, player.getPosition());
                // Colisión/interacción básica
                if (npc.canInteract() && player.canInteractWith(npc)) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                        currentDialogue = npc.interact();
                    }
                }
            }

            // Actualización de nivel
            fatimaLevel->update(deltaTime, player, npcs);

            // Misiones
            questSystem.update();
        }

        // --- DIBUJADO ---
        window.clear(sf::Color(10, 10, 20)); // Fondo oscuro

        // Menú principal
        if (currentState == GameState::MENU) {
            drawTextCentered(window, mainFont, "APARICIONES MARIANAS", 60, 200, sf::Color::White);
            drawTextCentered(window, mainFont, "Presiona ENTER para comenzar", 32, 350, sf::Color(180,180,180));
        }

        // Juego principal
        if (currentState == GameState::FATIMA) {
            fatimaLevel->draw(window);

            // Dibuja NPCs
            for (auto& npc : npcs) {
                npc.draw(window);
            }

            // Dibuja jugador
            player.draw(window);

            // Dibuja HUD
            drawHUD(window, mainFont, player.getHealth(), player.getMaxHealth(), player.getFaith(), player.getMaxFaith());

            // Dibuja diálogo actual
            if (!currentDialogue.empty()) {
                sf::RectangleShape dialogBg(sf::Vector2f(screenWidth * 0.7f, 80));
                dialogBg.setFillColor(sf::Color(0,0,0,200));
                dialogBg.setPosition(screenWidth*0.15f, screenHeight - 120);
                window.draw(dialogBg);

                sf::Text dialogText(currentDialogue, mainFont, 24);
                dialogText.setFillColor(sf::Color::White);
                dialogText.setPosition(screenWidth*0.17f, screenHeight - 110);
                window.draw(dialogText);
            }
        }

        window.display();
    }

    // Limpieza de recursos automática por destructores

    return 0;
}
