#ifndef CAMERA_H
#define CAMERA_H

#define WINDOW_BUFFER 200 // how close the player can get to the window edge
#define ZOOM_DELTA 0.05 // how much render_scale_factor will change per frame when zooming in/out
#define CENTER_PLAYER_DELTA 15 // how many pixels the camera will shift per frame when centering the player (this is only used when the step is not computed elsewhere, i.e. no zoom change)

#include <linmath.h>
#include "../structs.h"

extern vec4 camera_buffer; // Buffers: Left, Right, Bottom, Top (actual screen coords, NOT relative)
extern Camera main_cam;
extern Camera left_cam;
extern Camera right_cam;

f32 vec2_get_distance(vec2 first, vec2 second);
void camera_init(void);
void shift_camera(Player * player, vec2 position);
void shift_camera_smooth(Player * player);
void camera_update(Player *player, Map *map);

#endif