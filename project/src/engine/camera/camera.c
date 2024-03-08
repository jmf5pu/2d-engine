#include "../camera.h"
#include "../../structs.h"
#include "../global.h"
#include "../physics.h"
#include "../physics/physics_internal.h"
#include "../render.h"
#include <linmath.h>

Camera main_cam;
Camera left_cam;
Camera right_cam;

bool vec2_is_equal(vec2 first, vec2 second) { return first[0] == second[0] && first[1] == second[1]; }

static f32 window_buffer;

void camera_init(void)
{
    if (render_width < 1 || render_width > 10000) {
        printf("render width must be properly instantiated to initialize cameras\n");
    }

    window_buffer = 0.3 * render_height; // using render height here because render width is typically wider

    // create camera structs
    main_cam = (Camera){
        .position = {0, 0},
        .target_position = NULL,
        .buffer = {window_buffer, render_width - window_buffer, window_buffer, render_height - window_buffer},
    };

    // half way to the left of the screen, buffers the center instead of the
    // right side
    left_cam = (Camera){
        .position = {0, 0},
        .target_position = NULL,
        .buffer = {window_buffer, render_width - window_buffer, window_buffer, render_height - window_buffer},
    };

    // half way to the right of the screen, buffers the center instead of
    // the left side
    right_cam = (Camera){
        .position = {0, 0}, // essentially bump everything to the right by
                            // half the screen width right off the bat
        .target_position = NULL,
        .buffer = {window_buffer, render_width - window_buffer, window_buffer, render_height - window_buffer},
    };
}

/// @brief  updates camera based on the shift vector parameter
/// @param player target player
/// @param shift vec2 which represents the SHIFT, not destination position
void shift_camera(Player *player, vec2 shift)
{
    vec2_sub(player->camera->position, player->camera->position, shift);
    vec2_add(player->entity->body->aabb.position, player->entity->body->aabb.position, shift);
    vec2_add(player->crosshair->body->aabb.position, player->crosshair->body->aabb.position, shift);
}

/// @brief Shifts the camera gradually, frame by frame. Typically used when
/// centering the camera on an entity
/// @param player pointer to the active player
/// @param delta unsigned int representing the magnitude of the camera movement
/// per frame
void shift_camera_smooth(Player *player, u32 delta)
{
    f32 dx = player->camera->position[0] - player->camera->target_position[0][0];
    f32 dy = player->camera->position[1] - player->camera->target_position[0][1];
    if (sqrt(pow(dx, 2) + pow(dy, 2)) <= delta) {
        vec2_dup(player->camera->position, player->camera->target_position[0]);
        free(player->camera->target_position);
        player->camera->target_position = NULL;
        return;
    }
    f32 angle = fabs(
        (player->camera->target_position[0][0] > player->camera->position[0] && player->camera->target_position[0][1] > player->camera->position[1]) ||
                (player->camera->target_position[0][0] < player->camera->position[0] && player->camera->target_position[0][1] < player->camera->position[1])
            ? atan(dy / dx)
            : -1 * atan(dy / dx));
    vec2 xy_magnitudes;
    xy_magnitudes[0] = player->camera->target_position[0][0] >= player->camera->position[0] ? delta * cos(angle) : delta * cos(angle) * -1;
    xy_magnitudes[1] = player->camera->target_position[0][1] >= player->camera->position[1] ? delta * sin(angle) : delta * sin(angle) * -1;

    vec2_add(player->camera->position, player->camera->position, xy_magnitudes);
    vec2_sub(player->entity->body->aabb.position, player->entity->body->aabb.position, xy_magnitudes);
    vec2_sub(player->crosshair->body->aabb.position, player->crosshair->body->aabb.position, xy_magnitudes);
}

void camera_update(Player *player, Map *map)
{
    // update camera buffer
    player->camera->buffer[0] = window_buffer;
    player->camera->buffer[1] = render_width - window_buffer;
    player->camera->buffer[2] = window_buffer;
    player->camera->buffer[3] = render_height - window_buffer;

    // updates the camera based on the player's position
    float position_x = player->entity->body->aabb.position[0];
    float position_y = player->entity->body->aabb.position[1];

    // check if we have breached left buffer, if so, correct camera
    vec2 shift = {0, 0};
    if (position_x < player->camera->buffer[0]) {
        shift[0] = fabsf(position_x - player->camera->buffer[0]);
    }

    // check right buffer
    if (position_x > player->camera->buffer[1]) {
        shift[0] = -1 * fabsf(position_x - player->camera->buffer[1]);
    }

    // check bottom buffer
    if (position_y < player->camera->buffer[2]) {
        shift[1] = fabsf(position_y - player->camera->buffer[2]);
    }

    // check top buffer
    if (position_y > player->camera->buffer[3]) {
        shift[1] = -1 * fabsf(position_y - player->camera->buffer[3]);
    }
    if (player->camera->target_position) {
        shift_camera_smooth(player, CENTER_PLAYER_CAMERA_DELTA);
    }
    else {
        shift_camera(player, shift);
    }
}