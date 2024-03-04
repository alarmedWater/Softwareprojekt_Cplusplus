
#include "gpio_control.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// Debounce duration in milliseconds
#define DEBOUNCE_TIME 20

// Utility function to get current time in milliseconds
long get_current_time_millis(void) {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

void gpio_initialize(void) {
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "wiringPi setup failed.\n");
        exit(EXIT_FAILURE); // Exit if wiringPi setup fails
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
    printf("GPIO setup success.\n");
}

int gpio_read_left_button(void) {
    return digitalRead(BUTTON_PIN_LEFT) == LOW; // Button is pressed when pin is LOW
}

int gpio_read_right_button(void) {
    return digitalRead(BUTTON_PIN_RIGHT) == LOW; // Button is pressed when pin is LOW
}

int gpio_read_up_button(void) {
    return digitalRead(BUTTON_PIN_UP) == LOW; // Button is pressed when pin is LOW
}

int gpio_read_down_button(void) {
    return digitalRead(BUTTON_PIN_DOWN) == LOW; // Button is pressed when pin is LOW
}

int gpio_read_space_button(void) {
    return digitalRead(BUTTON_PIN_SPACE) == LOW; // Button is pressed when pin is LOW
}

void gpio_poll_and_push_events(void) {
    // Example of directly pushing an event without debounce logic
    SDL_Event event;
    SDL_zero(event);
    event.type = BUTTON_LEFT_PRESSED; // Simulate left button press
    SDL_PushEvent(&event);
    usleep(100000); // Prevent flooding the event queue
}


    // static int lastLeftState = 0, lastRightState = 0, lastUpState = 0, lastDownState = 0, lastSpaceState = 0;
    // static long lastDebounceTime[5] = {0}; // Array to track the last debounce time for each button

    // // Poll each button and push events for state changes
    // int currentStates[] = {readLeftButton(), readRightButton(), readUpButton(), readDownButton(), readSpaceButton()};
    // int *lastStates[] = {&lastLeftState, &lastRightState, &lastUpState, &lastDownState, &lastSpaceState};
    // Uint32 events[] = {BUTTON_LEFT_PRESSED, BUTTON_RIGHT_PRESSED, BUTTON_UP_PRESSED, BUTTON_DOWN_PRESSED, BUTTON_SPACE_PRESSED};
    
    // long currentTime = getCurrentTimeMillis();

    // for (int i = 0; i < sizeof(currentStates) / sizeof(currentStates[0]); ++i) {
    //     if (currentStates[i] != *lastStates[i] && (currentTime - lastDebounceTime[i]) > DEBOUNCE_TIME) {
    //         if (currentStates[i] == 1) { // Button press detected
    //             SDL_Event event;
    //             SDL_zero(event);
    //             event.type = events[i];
    //             printf("Button %d pressed, pushing event\n", i);
    //             SDL_PushEvent(&event);
    //         }
    //         *lastStates[i] = currentStates[i]; // Update last state
    //         lastDebounceTime[i] = currentTime; // Update last debounce time
    //     }
    // }
