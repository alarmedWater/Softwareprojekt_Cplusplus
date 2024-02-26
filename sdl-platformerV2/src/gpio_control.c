#include "gpio_control.h"

// Define your GPIO pin numbers here
#define BUTTON_PIN_LEFT 25  // WiringPi pin number for left button
#define BUTTON_PIN_RIGHT 24 // WiringPi pin number for right button
#define BUTTON_PIN_UP 23    // WiringPi pin number for up button
#define BUTTON_PIN_DOWN 1  // WiringPi pin number for down button
#define BUTTON_PIN_SPACE 21 // WiringPi pin number for space button


void initializeGPIO() {
    if (wiringPiSetup() == -1) {
        printf("wiringPi setup failed.\n");
        exit(1); // Exit if wiringPi setup fails
    }

    // Initialize pins for left, right, up, down, and space buttons
    pinMode(BUTTON_PIN_LEFT, INPUT);
    pullUpDnControl(BUTTON_PIN_LEFT, PUD_UP);
    pinMode(BUTTON_PIN_RIGHT, INPUT);
    pullUpDnControl(BUTTON_PIN_RIGHT, PUD_UP);
    pinMode(BUTTON_PIN_UP, INPUT);
    pullUpDnControl(BUTTON_PIN_UP, PUD_UP);
    pinMode(BUTTON_PIN_DOWN, INPUT);
    pullUpDnControl(BUTTON_PIN_DOWN, PUD_UP);
    pinMode(BUTTON_PIN_SPACE, INPUT);
    pullUpDnControl(BUTTON_PIN_SPACE, PUD_UP);
}

int readLeftButton() {
    printf("readLeftisCalled!");
    return digitalRead(BUTTON_PIN_LEFT) == 0; // Button is pressed when pin is LOW
}

int readRightButton() {
    return digitalRead(BUTTON_PIN_RIGHT) == 0; // Button is pressed when pin is LOW
}
int readUpButton() {
    return digitalRead(BUTTON_PIN_UP) == 0; // Button is pressed when pin is LOW
}

int readDownButton() {
    return digitalRead(BUTTON_PIN_DOWN) == 0; // Button is pressed when pin is LOW
}

int readSpaceButton() {
    return digitalRead(BUTTON_PIN_SPACE) == 0; // Button is pressed when pin is LOW
}


void pollGPIOAndPushEvents() {
    static int lastLeftState = 0, lastRightState = 0, lastUpState = 0, lastDownState = 0, lastSpaceState = 0;

    // Poll each button and push events for state changes
    int currentStates[] = {
        readLeftButton(), readRightButton(), readUpButton(), readDownButton(), readSpaceButton()
    };
    int *lastStates[] = {
        &lastLeftState, &lastRightState, &lastUpState, &lastDownState, &lastSpaceState
    };
    Uint32 events[] = {
        BUTTON_LEFT_PRESSED, BUTTON_RIGHT_PRESSED, BUTTON_UP_PRESSED, BUTTON_DOWN_PRESSED, BUTTON_SPACE_PRESSED
    };

    for (int i = 0; i < sizeof(currentStates) / sizeof(currentStates[0]); ++i) {
        if (currentStates[i] != *lastStates[i]) {
            if (currentStates[i] == 1) {
                SDL_Event event;
                SDL_zero(event);
                event.type = events[i];
                SDL_PushEvent(&event);
            }
            *lastStates[i] = currentStates[i];
        }
    }
}