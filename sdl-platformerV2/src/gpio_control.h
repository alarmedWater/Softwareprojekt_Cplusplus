#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

#include <wiringPi.h>
#include <SDL2/SDL.h> 

// GPIO Pin-Definitionen
#define BUTTON_PIN_LEFT 25
#define BUTTON_PIN_RIGHT 24
#define BUTTON_PIN_UP 23
#define BUTTON_PIN_DOWN 22
#define BUTTON_PIN_SPACE 21

// SDL Custom Event-Definitionen
#define BUTTON_LEFT_PRESSED SDL_USEREVENT + 1
#define BUTTON_RIGHT_PRESSED SDL_USEREVENT + 2
#define BUTTON_UP_PRESSED SDL_USEREVENT + 3
#define BUTTON_DOWN_PRESSED SDL_USEREVENT + 4
#define BUTTON_SPACE_PRESSED SDL_USEREVENT + 5

// Funktionsdeklarationen
void initializeGPIO();
int readLeftButton();
int readRightButton();
int readUpButton();
int readDownButton();
int readSpaceButton();
void pollGPIOAndPushEvents();

#endif // GPIO_CONTROL_H
