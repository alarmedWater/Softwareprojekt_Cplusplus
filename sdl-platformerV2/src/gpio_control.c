#include "gpio_control.h"

// Define your GPIO pin numbers here
#define BUTTON_PIN_LEFT 25  // WiringPi pin number for left button
#define BUTTON_PIN_RIGHT 24 // WiringPi pin number for right button
#define BUTTON_PIN_UP 23    // WiringPi pin number for up button
#define BUTTON_PIN_DOWN 1  // WiringPi pin number for down button
#define BUTTON_PIN_SPACE 21 // WiringPi pin number for space button

// Debounce duration in milliseconds
#define DEBOUNCE_TIME 200

// Utility function to get current time in milliseconds
long getCurrentTimeMillis() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}


void initGPIO() {
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
      printf("wiringPi setup  successe!.\n");
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
    static long lastDebounceTime[5] = {0}; // Array to track the last debounce time for each button

    // Poll each button and push events for state changes
    int currentStates[] = {readLeftButton(), readRightButton(), readUpButton(), readDownButton(), readSpaceButton()};
    int *lastStates[] = {&lastLeftState, &lastRightState, &lastUpState, &lastDownState, &lastSpaceState};
    Uint32 events[] = {BUTTON_LEFT_PRESSED, BUTTON_RIGHT_PRESSED, BUTTON_UP_PRESSED, BUTTON_DOWN_PRESSED, BUTTON_SPACE_PRESSED};
    
    long currentTime = getCurrentTimeMillis();

    for (int i = 0; i < sizeof(currentStates) / sizeof(currentStates[0]); ++i) {
        if (currentStates[i] != *lastStates[i] && (currentTime - lastDebounceTime[i]) > DEBOUNCE_TIME) {
            if (currentStates[i] == 1) { // Button press detected
                SDL_Event event;
                SDL_zero(event);
                event.type = events[i];
                SDL_PushEvent(&event);
            }
            *lastStates[i] = currentStates[i]; // Update last state
            lastDebounceTime[i] = currentTime; // Update last debounce time
        }
    }
}