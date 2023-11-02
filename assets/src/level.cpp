#include "level.h"
#include <SFML/Graphics.hpp>

Level::Level() {
    // Initialize the grid with empty cells
    grid.resize(20, std::vector<CellType>(20, CellType::Empty));

    // Load textures
    blockTexture.loadFromFile("/home/parallels/Documents/SW_Pro/Softwareprojekt_Cplusplus/assets/texture/Blocks/Ground_1.png");
    enemyTexture.loadFromFile("/home/parallels/Documents/SW_Pro/Softwareprojekt_Cplusplus/assets/texture/Blocks/Ground_1.png");
    collectibleTexture.loadFromFile("/home/parallels/Documents/SW_Pro/Softwareprojekt_Cplusplus/assets/texture/Blocks/Ground_1.png");

    //Smooth Operator 
    blockTexture.setSmooth(true);
    enemyTexture.setSmooth(true);
    collectibleTexture.setSmooth(true);

    // Set up a simple level layout
    for (int i = 0; i < 20; ++i) {
        grid[19][i] = CellType::Block; // Ground
    }

    // Add some blocks and enemies for example
    grid[15][5] = CellType::Block;
    grid[10][10] = CellType::Enemy;
    grid[5][15] = CellType::Collectible;
}

void Level::draw(sf::RenderWindow &window) {
    for (int y = 0; y < 20; ++y) {
        for (int x = 0; x < 20; ++x) {
            sf::Sprite sprite;
            switch (grid[y][x]) {
                case CellType::Block:
                    sprite.setTexture(blockTexture);
                    break;
                case CellType::Enemy:
                    sprite.setTexture(enemyTexture);
                    break;
                case CellType::Collectible:
                    sprite.setTexture(collectibleTexture);
                    break;
                default:
                    continue; // Skip empty cells
            }

            // Assuming the textures are square and your cells are also square.
            // If not, you would need separate scale factors for width and height.
            float scaleFactor = static_cast<float>(cellSize) / sprite.getTexture()->getSize().x;
            sprite.setScale(scaleFactor, scaleFactor);

            sprite.setPosition(x * cellSize, y * cellSize);
            window.draw(sprite);
        }
    }
}

bool Level::isCollision(int x, int y) {
    if (x < 0 || x >= 20 || y < 0 || y >= 20) {
        return false;
    }
    return grid[y][x] != CellType::Empty;
}

CellType Level::getCellType(int x, int y) {
    if (x < 0 || x >= 20 || y < 0 || y >= 20) {
        return CellType::Empty;
    }
    return grid[y][x];
}

void Level::setCellType(int x, int y, CellType type) {
    if (x >= 0 && x < 20 && y >= 0 && y < 20) {
        grid[y][x] = type;
    }
}

