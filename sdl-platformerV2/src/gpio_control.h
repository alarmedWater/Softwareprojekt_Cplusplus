#ifndef GPIO_CONTROL_H
#define GPIO_CONTROL_H

#include <wiringPi.h>

// Function declarations
void initializeGPIO();
int readLeftButton();
int readRightButton();

#endif // GPIO_CONTROL_H
