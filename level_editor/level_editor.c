#include <SDL2/SDL.h>
#include <stdbool.h>


#define LEVEL_HEIGHT 10
#define LEVEL_WIDTH 10


// Pseudocode und SDL-Grundlagen
int main() {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Level Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    char levelGrid[LEVEL_HEIGHT][LEVEL_WIDTH]; // Ihre Level-Daten
    initLevelGrid(levelGrid); // Initialisierungsfunktion für das Grid

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                handleMouseClick(event.button, levelGrid);
            }
        }

        renderGrid(renderer, levelGrid); // Funktion, um das Grid zu zeichnen
        SDL_RenderPresent(renderer);
    }

    saveLevel(levelGrid); // Funktion, um das Level zu speichern

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void handleMouseClick(SDL_MouseButtonEvent button, char grid[][]) {
    // Bestimmen Sie die Zelle, auf die geklickt wurde, und ändern Sie ihren Typ
}

void saveLevel(char grid[][]) {
    // Speichern Sie das Grid in einer Datei
}
