#include "frame_control.h"
#include "helpers.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>

typedef long long time_ns; // Nanoseconds
static const time_ns TIME_UNDEFINED = -1;

static struct {
    int started;
    time_ns start_time;
    time_ns prev_frame_time;
    time_ns elapsed_frame_time;
    time_ns frame_period;
    unsigned long frame_count;
    double max_delta_time;
    double time_per_ms;
} frame_controller = {0};

static inline double time_to_ms(time_ns time) {
    return time / frame_controller.time_per_ms;
}

static inline time_ns ms_to_time(double ms) {
    return ms * frame_controller.time_per_ms;
}

static time_ns get_current_time() {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * (time_ns)1000000000 + t.tv_nsec;
}

void frame_control_start(int fps, double max_delta_time) {
    frame_controller.time_per_ms = 1000000;
    frame_controller.start_time = get_current_time();
    ensure_condition(frame_controller.start_time != TIME_UNDEFINED, "frame_control_start: Can't get current time");
    frame_controller.prev_frame_time = frame_controller.start_time;
    frame_controller.elapsed_frame_time = 0;
    frame_controller.frame_period = fps > 0 ? ms_to_time(1000.0 / fps) : 0;
    frame_controller.frame_count = 0;
    frame_controller.max_delta_time = max_delta_time;
    frame_controller.started = 1;
}

void frame_control_stop() {
    if (!frame_controller.started) {
        return;
    }
    frame_controller.started = 0; // ensure_ to mark the controller as stopped.
}

void frame_control_wait_for_next_frame() {
    const time_ns next_frame_time = frame_controller.prev_frame_time + frame_controller.frame_period;
    time_ns current_time = get_current_time();

    while (current_time < next_frame_time) {
        if (next_frame_time - current_time > frame_controller.time_per_ms) {
            SDL_Delay(1); // Sleep for 1ms to reduce CPU usage
        } else {
            // Spin-wait for precise timing
        }
        current_time = get_current_time();
    }

    frame_controller.elapsed_frame_time = frame_controller.prev_frame_time ? current_time - frame_controller.prev_frame_time : 0;
    frame_controller.prev_frame_time = current_time;
    frame_controller.frame_count++;
}

double frame_control_get_elapsed_time() {
    return time_to_ms(get_current_time() - frame_controller.start_time);
}

double frame_control_get_current_fps() {
    return frame_controller.frame_count / (time_to_ms(frame_controller.prev_frame_time - frame_controller.start_time) / 1000.0);
}

double frame_control_get_elapsed_frame_time() {
    const double elapsed_time = time_to_ms(frame_controller.elapsed_frame_time);
    if (frame_controller.max_delta_time > 0 && elapsed_time > frame_controller.max_delta_time) {
        return frame_controller.max_delta_time;
    }
    return elapsed_time;
}
