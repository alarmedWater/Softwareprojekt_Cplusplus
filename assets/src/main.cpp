#include <SFML/Graphics.hpp>
#include <iostream>

#include "player.h"
#include "level.h"

int main() {
    // Create a window
    sf::Vector2u windowSize(800, 600);
    sf::VideoMode mode(windowSize);
    sf::RenderWindow window(mode, "SFML Hello World");
    sf::Clock clock;
    
    // Create a player object
    Player player;

    // Create a level object
    Level level;

    // Main loop
    while (window.isOpen()) {

        //Clock
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update player
        player.update(deltaTime);

        // Clear the window
        window.clear();

        // Draw the level
        level.draw(window);

        // Draw the player
        player.draw(window);

        // Display the rendered frame
        window.display();
    }

    return 0;
}