#ifndef FRAME_CONTROL_H
#define FRAME_CONTROL_H

void frame_control_start(int fps, double max_delta_time);
void frame_control_stop(void);
void frame_control_wait_for_next_frame(void);
double frame_control_get_elapsed_frame_time(void); // milliseconds
double frame_control_get_elapsed_time(void); // milliseconds
double frame_control_get_current_fps(void);

#endif /* FRAME_CONTROL_H */

