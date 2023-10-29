#include <SFML/Graphics.hpp>
#include <iostream>

#include "player.h"

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Hello World");
    sf::Clock clock;
    
    // Create a player object
    Player player;

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

        // Draw the player
        player.draw(window);

        // Display the rendered frame
        window.display();
    }

    return 0;
}