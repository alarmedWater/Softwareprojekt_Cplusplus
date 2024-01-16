

#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL_types.h>

extern Level* level;
extern Player player;

void initGame();
void runGame();

void setLevel( int r, int c );
void completeLevel();

void damagePlayer( int damage );
void killPlayer();

#endif
