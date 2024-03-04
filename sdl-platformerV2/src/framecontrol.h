#ifndef FRAMECONTROL_H
#define FRAMECONTROL_H

void startFrameControler( int fps, double maxDeltaTime );
void stopFrameControler();      // Must be called after startFrameControler(), before the program exits
void waitForNextFrame();
double getElapsedFrameTime(); // ms
double getElapsedTime();      // ms
double getCurrentFps();

#endif