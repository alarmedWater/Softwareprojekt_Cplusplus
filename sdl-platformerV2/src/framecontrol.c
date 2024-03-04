#include "framecontrol.h"
#include "helpers.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
typedef long long Time;                  // Nanoseconds
static const Time TIME_UNDEFINED = -1;


static struct
{
    int started;
    Time startTime;
    Time prevFrameTime;
    Time elapsedFrameTime;
    Time framePeriod;
    unsigned long frameCount;
    double maxDeltaTime;
    double timePerMs;
} frameControler = {0};


static inline double timeToMs( Time time )
{
    return time / frameControler.timePerMs;
}

static inline Time msToTime( double ms )
{
    return ms * frameControler.timePerMs;
}

static Time getCurrentTime()
{

    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * (Time)1000000000 + t.tv_nsec;
}

// If fps <= 0, new frame will be ready right after the previous one is handled,
// i.e. there will be no fps limit.
// 
// The maxDeltaTime is the maximum time increment which can be correctly handled,
// in ms. If it's <= 0, there will be no increment limit.
//
// The maxDeltaTime is used because, if the frame takes too long, the game may
// change more than we can handle: e.g. some object may move too far, across the
// walls. To solve this, the long frame can be handled as multiple shorter frames,
// each <= maxDeltaTime. Or, if it's not required to sync the game time with the
// real time, the long frame can be simply truncated to maxDeltaTime. This is done
// in getElapsedFrameTime(), so that each long frame will be treated as a shorter
// one (the game will slow down at these moments). For more information, see
// https://gafferongames.com/post/fix_your_timestep/
void startFrameControler( int fps, double maxDeltaTime )
{
    frameControler.timePerMs = 1000000;
    frameControler.startTime = getCurrentTime();
    ensure(frameControler.startTime != TIME_UNDEFINED, "startFrameControler(): Can't get current time");
    frameControler.prevFrameTime = frameControler.startTime;
    frameControler.elapsedFrameTime = 0;
    frameControler.framePeriod = fps > 0 ? msToTime(1000.0 / fps) : 0;
    frameControler.frameCount = 0;
    frameControler.maxDeltaTime = maxDeltaTime;

    frameControler.started = 1;
}

void stopFrameControler()
{
    if (!frameControler.started) {
        return;
    }
}

void waitForNextFrame()
{
    const Time nextFrameTime = frameControler.prevFrameTime + frameControler.framePeriod;
    Time currentTime = getCurrentTime();

    while (currentTime < nextFrameTime) {
        if (nextFrameTime - currentTime > frameControler.timePerMs) {
            SDL_Delay(1);
        } else {
            // Just spin in the loop, because this can be more precise
            // than system delay
        }
        currentTime = getCurrentTime();
    }

    frameControler.elapsedFrameTime = frameControler.prevFrameTime ? currentTime - frameControler.prevFrameTime : 0;
    frameControler.prevFrameTime = currentTime;
    frameControler.frameCount += 1;
}



double getElapsedTime()
{
    return timeToMs(getCurrentTime() - frameControler.startTime);
}

double getCurrentFps()
{
    return frameControler.frameCount / (timeToMs(frameControler.prevFrameTime - frameControler.startTime) / 1000.0);
}

double getElapsedFrameTime()
{
    const double elapsedTime = timeToMs(frameControler.elapsedFrameTime);
    if (frameControler.maxDeltaTime > 0 && elapsedTime > frameControler.maxDeltaTime) {
        return frameControler.maxDeltaTime;
    }
    return elapsedTime;
}