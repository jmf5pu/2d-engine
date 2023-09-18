#ifndef CAMERA_H
#define CAMERA_H

#include <linmath.h>
#include "../structs.h"

void camera_init();
void shift_camera(vec2 position, Map *map);
void camera_update(Body *body_player, Map *map, int buffer);

#endif