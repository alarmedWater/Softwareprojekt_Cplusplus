#ifndef LEVEL_EDITOR_H
#define LEVEL_EDITOR_H

#include <SDL2/SDL.h>

#define LEVEL_WIDTH  10  // Die Breite des Levels, ändern Sie dies entsprechend
#define LEVEL_HEIGHT 10  // Die Höhe des Levels, ändern Sie dies entsprechend

// Struktur, um Level-Daten zu speichern
typedef struct {
    char grid[LEVEL_HEIGHT][LEVEL_WIDTH];
} Level;

// Funktionen für den Level-Editor
void initLevelGrid(Level *level);
void handleMouseClick(SDL_MouseButtonEvent button, Level *level);
void renderGrid(SDL_Renderer *renderer, const Level *level);
void saveLevel(const Level *level);

#endif // LEVEL_EDITOR_H
#ifndef LEVEL_EDITOR_H
#define LEVEL_EDITOR_H

#include <SDL2/SDL.h>

#define LEVEL_WIDTH  10  // Die Breite des Levels, ändern Sie dies entsprechend
#define LEVEL_HEIGHT 10  // Die Höhe des Levels, ändern Sie dies entsprechend

// Struktur, um Level-Daten zu speichern
typedef struct {
    char grid[LEVEL_HEIGHT][LEVEL_WIDTH];
} Level;

// Funktionen für den Level-Editor
void initLevelGrid(Level *level);
void handleMouseClick(SDL_MouseButtonEvent button, Level *level);
void renderGrid(SDL_Renderer *renderer, const Level *level);
void saveLevel(const Level *level);

#endif // LEVEL_EDITOR_H
