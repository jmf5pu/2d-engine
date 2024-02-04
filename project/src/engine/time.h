#ifndef TIME_H
#define TIME_H

#include "types.h"

typedef struct time_state {
  f32 delta; // time between frames
  f32 now;   // current frame
  f32 last;  // last frame

  f32 frame_last;  // last time fps was calculated
  f32 frame_delay; // maximum amount of time a frame should take
  f32 frame_time;  // how long the current frame took

  u32 frame_rate;  // how many fps we are running at
  u32 frame_count; // used to calculate frame rate
} Time_State;

void time_update(void);
void time_update_late(void);
void time_init(u32 frame_rate);

#endif