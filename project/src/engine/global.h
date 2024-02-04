#ifndef GLOBAL_H
#define GLOBAL_H

#include "config.h"
#include "input.h"
#include "render.h"
#include "time.h"

typedef struct global {
  Config_State config;
  Input_State input;
  Time_State time;
} Global;

extern Global global;

#endif