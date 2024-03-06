//gcc button_test.c -lwiringPi -o button_test


#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h> 
#include <stdlib.h>

// Define your GPIO pin numbers here
#define BUTTON_PIN_LEFT 22  // WiringPi pin number for left button
#define BUTTON_PIN_RIGHT 24 // WiringPi pin number for right button
#define BUTTON_PIN_UP 25    // WiringPi pin number for up button
#define BUTTON_PIN_DOWN 23  // WiringPi pin number for down button
#define BUTTON_PIN_SPACE 21 // WiringPi pin number for space button

void initializeializeGPIO() {
    if (wiringPiSetup() == -1) {
        printf("Failed to setup WiringPi\n");
        exit(1);
    }

    pinMode(BUTTON_PIN_LEFT, INPUT);
    pinMode(BUTTON_PIN_RIGHT, INPUT);
    pinMode(BUTTON_PIN_UP, INPUT);
    pinMode(BUTTON_PIN_DOWN, INPUT);
    pinMode(BUTTON_PIN_SPACE, INPUT);

    pullUpDnControl(BUTTON_PIN_LEFT, PUD_UP);
    pullUpDnControl(BUTTON_PIN_RIGHT, PUD_UP);
    pullUpDnControl(BUTTON_PIN_UP, PUD_UP);
    pullUpDnControl(BUTTON_PIN_DOWN, PUD_UP);
    pullUpDnControl(BUTTON_PIN_SPACE, PUD_UP);
}

int main() {
    initializeializeGPIO();

    while(1) {
        if(digitalRead(BUTTON_PIN_LEFT) == 0) {
            printf("Left button pressed\n");
        }
        if(digitalRead(BUTTON_PIN_RIGHT) == 0) {
            printf("Right button pressed\n");
        }
        if(digitalRead(BUTTON_PIN_UP) == 0) {
            printf("Up button pressed\n");
        }
        if(digitalRead(BUTTON_PIN_DOWN) == 0) {
            printf("Down button pressed\n");
        }
        if(digitalRead(BUTTON_PIN_SPACE) == 0) {
            printf("Space button pressed\n");
        }

        // Simple debouncing mechanism
        usleep(100000); // Sleep for 100 milliseconds
    }

    return 0;
}//gcc button_test.c -lwiringPi -o button_test