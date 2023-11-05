#include <linmath.h>
#include "../camera.h"
#include "../physics.h"
#include "../global.h"
#include "../physics/physics_internal.h"
#include "../render.h"
#include "../../structs.h"

Camera main_cam;
Camera left_cam;
Camera right_cam;

void camera_init(void)
{
    // create camera structs
    main_cam = (Camera){
        .position = {0, 0},
        .buffer = {WINDOW_BUFFER, render_width - WINDOW_BUFFER, WINDOW_BUFFER, render_height - WINDOW_BUFFER},
    };

    // half way to the left of the screen, buffers the center instead of the right side
    left_cam = (Camera){
        .position = {0, 0},
        .buffer = {WINDOW_BUFFER, render_width - WINDOW_BUFFER, WINDOW_BUFFER, render_height - WINDOW_BUFFER},
    };

    // half way to the right of the screen, buffers the center instead of the left side
    right_cam = (Camera){
        .position = {render_width, 0}, // essentially bump everything to the right by half the screen width right off the bat
        .buffer = {WINDOW_BUFFER, render_width - WINDOW_BUFFER, WINDOW_BUFFER, render_height - WINDOW_BUFFER},
    };
}

void shift_camera(Camera *camera, vec2 shift)
{
    // updates camera based on the passed in vector which represents the SHIFT, not destination position
    camera->position[0] -= shift[0]; // switch this to vec2_add?
    camera->position[1] -= shift[1];
}

void camera_update(Camera *camera, Player *player, Map *map)
{
    // update camera buffer
    camera->buffer[0] = WINDOW_BUFFER;
    camera->buffer[1] = render_width - WINDOW_BUFFER;
    camera->buffer[2] = WINDOW_BUFFER;
    camera->buffer[3] = render_height - WINDOW_BUFFER;

    // updates the camera based on the player's position
    float position_x = player->entity->body->aabb.position[0];
    float position_y = player->entity->body->aabb.position[1];

    // check if we have breached left buffer, if so, correct camera
    vec2 shift = {0, 0};
    if (position_x < camera->buffer[0])
    {
        shift[0] = fabsf(position_x - camera->buffer[0]);
    }

    // check right buffer
    if (position_x > camera->buffer[1])
    {
        shift[0] = -1 * fabsf(position_x - camera->buffer[1]);
    }

    // check bottom buffer
    if (position_y < camera->buffer[2])
    {
        shift[1] = fabsf(position_y - camera->buffer[2]);
    }

    // check top buffer
    if (position_y > camera->buffer[3])
    {
        shift[1] = -1 * fabsf(position_y - camera->buffer[3]);
    }

    shift_camera(camera, shift);

    player->entity->body->aabb.position[0] += shift[0];
    player->entity->body->aabb.position[1] += shift[1];
}