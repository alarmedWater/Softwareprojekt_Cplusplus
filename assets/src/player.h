// Player.h
#include <SFML/Graphics.hpp>

class Player {
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f velocity;
    float gravity;
    float jumpVelocity;
    bool isJumping;
    const int cellSize = 50; // Set this to your actual cell size

public:
    Player();
    void update(float deltaTime);
    void draw(sf::RenderWindow &window);
    void setTextureAndScale(const std::string& texturePath);

private:
    void loadTexture(const std::string& texturePath); // Optional: A method to handle texture loading
};
