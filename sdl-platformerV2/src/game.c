/**
 * @file game.h
 * @brief Game state definitions and main game structure for the SDL Platformer.
 */
#include <stdio.h>
#include <math.h>
/**
 * @enum GAME_STATE
 * @brief Enumeration of the possible states in the game.
 *
 * This enumeration defines various states that the game can be in at any given moment,
 * such as playing, game over, level complete, etc.
 */
typedef enum
{
    STATE_QUIT = 0,         /**< State when the game is set to quit. */
    STATE_PLAYING,          /**< State when the game is currently being played. */
    STATE_KILLED,           /**< State when the player has been killed. */
    STATE_GAMEOVER,         /**< State indicating game over. */
    STATE_LEVELCOMPLETE     /**< State when a level is completed. */
} GAME_STATE;

/**
 * @struct
 * @brief Represents the main game state and properties.
 *
 * This structure holds the current state of the game, including the current game state,
 * keyboard state, respawn position, time until the level is cleaned, and jump status.
 */
static struct {
    GAME_STATE state;            /**< Current state of the game. */
    const Uint8* keystate;       /**< Current state of the keyboard. */
    struct { double x, y; } respawnPos; /**< Position where the player respawns. */
    double cleanTime;            /**< Time remaining until the level is cleaned. */
    int jumpDenied;              /**< Flag indicating if jumping is denied. */
} game;
