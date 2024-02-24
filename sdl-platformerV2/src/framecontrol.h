#ifndef FRAMECONTROL_H
#define FRAMECONTROL_H

void startFrameControl( int fps, double maxDeltaTime );
void stopFrameControl();      // Must be called after startFrameControl(), before the program exits
void waitForNextFrame();
double getElapsedFrameTime(); // ms
double getElapsedTime();      // ms
double getCurrentFps();

#endif
