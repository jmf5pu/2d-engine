#ifndef CAMERA_H
#define CAMERA_H

#define WINDOW_BUFFER 100 // how close the player can get to the window edge
#define CENTER_PLAYER_CAMERA_DELTA                                                                                                                                                 \
    25 // how many pixels the camera will move per frame (used when
       // centering player)

#include "../structs.h"
#include <linmath.h>

extern vec4 camera_buffer; // Buffers: Left, Right, Bottom, Top (actual screen
                           // coords, NOT relative)
extern Camera main_cam;
extern Camera left_cam;
extern Camera right_cam;

void camera_init(void);
void shift_camera(Player *player, vec2 position);
void shift_camera_smooth(Player *player, u32 delta);
void camera_update(Player *player, Map *map);

#endif