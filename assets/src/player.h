#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();
    void update(float deltaTime); // Add deltaTime parameter
    void draw(sf::RenderWindow &window);
    sf::RectangleShape getShape();

private:
    sf::RectangleShape shape;
    sf::Vector2f velocity; // Change type to sf::Vector2f
    float gravity;
    float jumpVelocity; // Renamed from jumpHeight
    bool isJumping;
};

#endif
