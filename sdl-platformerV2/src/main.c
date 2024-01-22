#include "game.h"

/**
 * @file main.c
 * @brief Entry point for the SDL Platformer game.
 * 
 * Initializes and runs the game. The game is set up in initGame() and 
 * executed in runGame(). This is the main entry point for the application.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments.
 * @return Integer 0 upon exit success.
 */
int main( int argc, char* argv[] )
{
    initGame();
    runGame();
    return 0;
}
