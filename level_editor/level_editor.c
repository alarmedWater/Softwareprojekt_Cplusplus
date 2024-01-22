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


void initLevelGrid(char grid[LEVEL_HEIGHT][LEVEL_WIDTH]) {
    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        for (int j = 0; j < LEVEL_WIDTH; j++) {
            grid[i][j] = ' '; // Leere Zelle
        }
    }
}


void handleMouseClick(SDL_MouseButtonEvent button, char grid[LEVEL_HEIGHT][LEVEL_WIDTH]) {
    int x = button.x / (800 / LEVEL_WIDTH);  // Annahme: Fensterbreite ist 800
    int y = button.y / (600 / LEVEL_HEIGHT); // Annahme: Fensterhöhe ist 600

    if (x < LEVEL_WIDTH && y < LEVEL_HEIGHT) {
        // Hier Code zur Änderung des Zellentyps
        // Beispiel: Zyklus durch einige Zeichen
        if (grid[y][x] == ' ') grid[y][x] = '*';
        else if (grid[y][x] == '*') grid[y][x] = 'x';
        else grid[y][x] = ' ';
    }
}

void renderGrid(SDL_Renderer *renderer, char grid[LEVEL_HEIGHT][LEVEL_WIDTH]) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // Weiß
    SDL_RenderClear(renderer);

    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        for (int j = 0; j < LEVEL_WIDTH; j++) {
            // Zeichnen Sie hier jede Zelle basierend auf ihrem Typ
            // Beispiel: Zeichnen eines Rechtecks für 'x' und eines Kreises für '*'
        }
    }
}


void saveLevel(char grid[LEVEL_HEIGHT][LEVEL_WIDTH]) {
    FILE *file = fopen("level.txt", "w");
    if (file == NULL) {
        // Fehlerbehandlung
        return;
    }

    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        for (int j = 0; j < LEVEL_WIDTH; j++) {
            fputc(grid[i][j], file);
        }
        fputc('\n', file);
    }

    fclose(file);
}
