#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

#include <wiringPi.h>
#include <SDL2/SDL.h>

// Define your GPIO pin numbers here
#define BUTTON_PIN_LEFT 6  // WiringPi pin number for left button
#define BUTTON_PIN_RIGHT 24 // WiringPi pin number for right button
#define BUTTON_PIN_UP 25    // WiringPi pin number for up button
#define BUTTON_PIN_DOWN 23  // WiringPi pin number for down button
#define BUTTON_PIN_SPACE 21

// SDL Custom Event Definitions
#define BUTTON_LEFT_PRESSED SDL_USEREVENT + 1
#define BUTTON_RIGHT_PRESSED SDL_USEREVENT + 2
#define BUTTON_UP_PRESSED SDL_USEREVENT + 3
#define BUTTON_DOWN_PRESSED SDL_USEREVENT + 4
#define BUTTON_SPACE_PRESSED SDL_USEREVENT + 5

// Function Declarations
void gpio_initialize(void);
int gpio_read_left_button(void);
int gpio_read_right_button(void);
int gpio_read_up_button(void);
int gpio_read_down_button(void);
int gpio_read_space_button(void);
void gpio_poll_and_push_events(void);

#endif // GPIO_CONTROL_H
