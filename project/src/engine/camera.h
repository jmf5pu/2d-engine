#ifndef CAMERA_H
#define CAMERA_H

#define WINDOW_BUFFER 100 // how close the player can get to the window edge

#include <linmath.h>
#include "../structs.h"

extern vec4 camera_buffer; // Buffers: Left, Right, Bottom, Top (actual screen coords, NOT relative)
extern Camera main_cam;
extern Camera left_cam;
extern Camera right_cam;

void camera_init(void);
void shift_camera(Camera *camera, vec2 position);
void camera_update(Camera *camera, Player *player, Map *map);

#endif