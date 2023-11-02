#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>

// Define different types of objects that can be in a cell
enum class CellType {
    Empty,
    Block,
    Enemy,
    Collectible
};

class Level {
private:
    std::vector<std::vector<CellType>> grid; // 2D vector for the grid
    sf::Texture blockTexture; // Texture for blocks
    sf::Texture enemyTexture; // Texture for enemies
    sf::Texture collectibleTexture; // Texture for collectibles
    const int cellSize = 40; // Size of each cell in pixels

public:
    Level();
    void draw(sf::RenderWindow &window);
    bool isCollision(int x, int y);
    CellType getCellType(int x, int y);
    void setCellType(int x, int y, CellType type);
};

#endif // LEVEL_H
