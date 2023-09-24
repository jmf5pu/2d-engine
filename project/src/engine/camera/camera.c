#include <linmath.h>
#include "../camera.h"
#include "../physics.h"
#include "../global.h"
#include "../physics/physics_internal.h"
#include "../render.h"
#include "../../structs.h"

void shift_camera(Camera *camera, vec2 shift, Map *map)
{
    // updates camera based on the passed in vector which represents the SHIFT, not destination position
    camera->position[0] -= shift[0]; // switch this to vec2_add?
    camera->position[1] -= shift[1];
}

void camera_update(Camera *camera, Body *body_player, Map *map)
{
    // updates the camera based on the player's position
    float position_x = body_player->aabb.position[0];
    float position_y = body_player->aabb.position[1];

    // check if we have breached left buffer, if so, correct camera
    vec2 shift = {0, 0};
    if (position_x < camera->buffer[0])
    {
        shift[0] = fabsf(position_x - camera->buffer[0]);
        shift_camera(camera, shift, map);
    }

    // check right buffer
    if (position_x > camera->buffer[1])
    {
        shift[0] = -1 * fabsf(position_x - camera->buffer[1]);
        shift_camera(camera, shift, map);
    }

    // check bottom buffer
    if (position_y < camera->buffer[2])
    {
        shift[1] = fabsf(position_y - camera->buffer[2]);
        shift_camera(camera, shift, map);
    }

    // check top buffer
    if (position_y > camera->buffer[3])
    {
        shift[1] = -1 * fabsf(position_y - camera->buffer[3]);
        shift_camera(camera, shift, map);
    }

    body_player->aabb.position[0] += shift[0];
    body_player->aabb.position[1] += shift[1];
}