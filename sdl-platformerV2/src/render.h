#ifndef RENDER_H
#define RENDER_H

#include "types.h"

extern SDL_Renderer* renderer;

void initializeRender( const char* spritesPath, const char* fontPath );
void drawSprite( SDL_Rect spriteRect, int x, int y, int frame, SDL_RendererFlip flip );
void drawObject( Object* object );
void drawMessage( MessageId message );
void drawScreen();
void setAnimation( Object* object, int frameStart, int frameEnd, int fps );
void setAnimationWave( Object* object, int fps );
void setAnimationFlip( Object* object, int frame, int fps );

#endif