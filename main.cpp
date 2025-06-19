#include <SFML/Graphics.hpp>
// Incluye aquí tus otros headers personalizados
// #include "Player.h"
// #include "NPC.h"
// #include "Level.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Maria Game con SFML");
    window.setFramerateLimit(60); // Limita los FPS para suavidad

    // Ejemplo de carga de textura
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/textures/player.png")) {
        // Manejo de error
    }
    sf::Sprite playerSprite(playerTexture);
    playerSprite.setPosition(100, 100);

    // Temporizador para animaciones/movimiento
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // --- Actualización de lógica ---
        float dt = clock.restart().asSeconds();

        // Ejemplo de movimiento básico con teclado
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            playerSprite.move(-100 * dt, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            playerSprite.move(100 * dt, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            playerSprite.move(0, -100 * dt);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            playerSprite.move(0, 100 * dt);

        // --- Dibujo ---
        window.clear(sf::Color::Black);
        window.draw(playerSprite);
        window.display();
    }

    return 0;
}
