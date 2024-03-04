#ifndef GAME_H
#define GAME_H

#define BUTTON_LEFT_PRESSED SDL_USEREVENT + 1
#define BUTTON_RIGHT_PRESSED SDL_USEREVENT + 2

#include "types.h"

extern Level* level;
extern Player player;

void initializeGame();
void runGame();

void setLevel( int r, int c );
void completeLevel();

void damagePlayer( int damage );
void killPlayer();

#endif