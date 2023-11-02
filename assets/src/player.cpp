// Player.cpp


#include <SFML/Graphics.hpp>

#include "player.h"

Player::Player() {
    // Load texture from a file
    if (!texture.loadFromFile("/home/parallels/Documents/SW_Pro/Softwareprojekt_Cplusplus/assets/texture/Charaters/Main/main_standing.png")) {
        // Handle error
    }
    // Set the sprite to use the loaded texture
    setTextureAndScale("/home/parallels/Documents/SW_Pro/Softwareprojekt_Cplusplus/assets/texture/Charaters/Main/main_standing.png");

    // Initialize player attributes
    sprite.setPosition(100.0f, 550.0f);
    velocity = sf::Vector2f(0.0f, 0.0f);
    gravity = 150.0f; // Adjusted gravity
    jumpVelocity = -400.0f; // Adjusted jump velocity for a more natural feel
    isJumping = false;
}


void Player::setTextureAndScale(const std::string& texturePath) {
    if (!texture.loadFromFile(texturePath)) {
        // Handle error
    }
    sprite.setTexture(texture);

    // Calculate scale factors to size the player as two grid cells
    float scaleFactorX = (2.0f * cellSize) / texture.getSize().x;
    float scaleFactorY = (2.0f * cellSize) / texture.getSize().y;
    sprite.setScale(scaleFactorX, scaleFactorY);

    // Adjust the position to account for the new size
    sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y - cellSize); // Adjust Y if needed
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

    // Update the sprite's position
    sprite.move(velocity.x * deltaTime, velocity.y * deltaTime);

    // Jumping
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !isJumping) {
        isJumping = true;
        velocity.y = jumpVelocity;
    }

    // Apply gravity
    velocity.y += gravity * deltaTime;
    sprite.move(0.0f, velocity.y * deltaTime);



    // Ground check and reset jumping
    if (sprite.getPosition().y >= 550.0f) {
        sprite.setPosition(sprite.getPosition().x, 550.0f);
        velocity.y = 0.0f;
        isJumping = false;
    }
}



void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}


