#ifndef CAMERA_H
#define CAMERA_H

#include <linmath.h>
#include "../structs.h"

typedef struct camera
{
    vec2 position;
    int buffer;
} Camera;

void shift_camera(Camera *camera, vec2 position, Map *map);
void camera_update(Camera *camera, Body *body_player, Map *map);

#endif