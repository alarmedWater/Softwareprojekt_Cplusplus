// Player.cpp

#include "player.h"

Player::Player() {
    // Initialize player attributes
    shape.setSize(sf::Vector2f(50.0f, 50.0f));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(100.0f, 550.0f);
    velocity = sf::Vector2f(0.0f, 0.0f);
    gravity = 150.0f; // Adjusted gravity
    jumpVelocity = -400.0f; // Adjusted jump velocity for a more natural feel
    isJumping = false;
}

void Player::update(float deltaTime) {
    // Player horizontal movement input
    if (!isJumping) { // Check if the player is not jumping
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            velocity.x = -200.0f; // Set horizontal velocity left
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            velocity.x = 200.0f; // Set horizontal velocity right
        } else {
            velocity.x = 0.0f; // Stop horizontal movement if no key is pressed
        }
    }

    // Apply horizontal movement
    shape.move(velocity.x * deltaTime, 0.0f);

    // Jumping
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) {
        isJumping = true;
        velocity.y = jumpVelocity;
    }

    // Apply gravity
    velocity.y += gravity * deltaTime;
    shape.move(0.0f, velocity.y * deltaTime);

    // Ground check and reset jumping
    if (shape.getPosition().y >= 550.0f) {
        shape.setPosition(shape.getPosition().x, 550.0f);
        velocity.y = 0.0f;
        isJumping = false;
    }
}


void Player::draw(sf::RenderWindow &window) {
    window.draw(shape);
}

sf::RectangleShape Player::getShape() {
    return shape;
}
