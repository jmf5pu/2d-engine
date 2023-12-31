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

/// @brief Checks if the values of 2 vec2 structs are equivalent
/// @param first the first vec2
/// @param second the second vec2 
/// @param check_to_hundredths_place specifies if we should truncate float values to the hundreth place between doing the comparison
/// @return bool representing if the vec2 structs have equal values
bool vec2_is_equal(vec2 first, vec2 second, bool check_to_hundredths_place){
    if(check_to_hundredths_place){
        return (int)first[0]*100.0 / 100.0 == (int)second[0]*100.0 / 100.0 && (int)first[1]*100.0 / 100.0 == (int)second[1]*100.0 / 100.0;
    }
    return first[0] == second[0] && first[1] == second[1];
}

/// @brief returns the distance between two vec2s representing x/y coordinates in the form of a 32 bit float
/// @param first the first vec2 xy coordinate
/// @param second the second vec2 xy coordinate
/// @return the distance between the parameters 
f32 vec2_get_distance(vec2 first, vec2 second){
    return sqrt(pow(first[0] - second[0], 2) + pow(first[1] - second[1], 2));
}

void camera_init(void)
{
    // create camera structs
    main_cam = (Camera){
        .position = {0, 0},
        .target_position = NULL,
        .buffer = {WINDOW_BUFFER, render_width - WINDOW_BUFFER, WINDOW_BUFFER, render_height - WINDOW_BUFFER},
    };

    // half way to the left of the screen, buffers the center instead of the right side
    left_cam = (Camera){
        .position = {0, 0},
        .target_position = NULL,
        .buffer = {WINDOW_BUFFER, render_width - WINDOW_BUFFER, WINDOW_BUFFER, render_height - WINDOW_BUFFER},
    };

    // half way to the right of the screen, buffers the center instead of the left side
    right_cam = (Camera){
        .position = {0, 0}, // essentially bump everything to the right by half the screen width right off the bat
        .target_position = NULL,
        .buffer = {WINDOW_BUFFER, render_width - WINDOW_BUFFER, WINDOW_BUFFER, render_height - WINDOW_BUFFER},
    };
}


void shift_camera(Player * player, vec2 shift)
{
    // updates camera based on the passed in vector which represents the SHIFT, not destination position
    vec2_sub(player->camera->position, player->camera->position, shift);
    vec2_add(player->entity->body->aabb.position, player->entity->body->aabb.position, shift);
    vec2_add(player->crosshair->entity->body->aabb.position, player->crosshair->entity->body->aabb.position, shift);
}

/// @brief Shifts the camera gradually, frame by frame. Typically used when centering the camera on an entity
/// @param player pointer to the active player
/// @param delta unsigned int representing the magnitude of the camera movement per frame
void shift_camera_smooth(Player * player){
    f32 step = player->camera->target_position_step;
    f32 dx = player->camera->position[0] - player->camera->target_position[0][0];
    f32 dy = player->camera->position[1] - player->camera->target_position[0][1];
    f32 distance = vec2_get_distance(player->camera->position, player->camera->target_position[0]);
    if(distance <= player->camera->target_position_step){
        step = distance;
    }
    f32 angle = fabs((player->camera->target_position[0][0] > player->camera->position[0] && player->camera->target_position[0][1] > player->camera->position[1]) || (player->camera->target_position[0][0] < player->camera->position[0] && player->camera->target_position[0][1] < player->camera->position[1]) ? atan(dy / dx) : -1 * atan(dy / dx));
    vec2 xy_magnitudes;
    xy_magnitudes[0] = player->camera->target_position[0][0] >= player->camera->position[0] ? step * cos(angle) : step * cos(angle) * -1;
    xy_magnitudes[1] = player->camera->target_position[0][1] >= player->camera->position[1] ? step * sin(angle) : step * sin(angle) * -1;

    vec2_add(player->camera->position, player->camera->position, xy_magnitudes);
    vec2_sub(player->entity->body->aabb.position, player->entity->body->aabb.position, xy_magnitudes);
    vec2_sub(player->crosshair->entity->body->aabb.position, player->crosshair->entity->body->aabb.position, xy_magnitudes);
    if(vec2_is_equal(player->camera->position, player->camera->target_position[0], true)){
        free(player->camera->target_position);
        player->camera->target_position = NULL;
    }
}

void camera_update(Player *player, Map *map)
{
    // update camera buffer
    player->camera->buffer[0] = WINDOW_BUFFER;
    player->camera->buffer[1] = render_width - WINDOW_BUFFER;
    player->camera->buffer[2] = WINDOW_BUFFER;
    player->camera->buffer[3] = render_height - WINDOW_BUFFER;

    // updates the camera based on the player's position
    float position_x = player->entity->body->aabb.position[0];
    float position_y = player->entity->body->aabb.position[1];

    // check if we have breached left buffer, if so, correct camera
    vec2 shift = {0, 0};
    if (position_x < player->camera->buffer[0])
    {
        shift[0] = fabsf(position_x - player->camera->buffer[0]);
    }

    // check right buffer
    if (position_x > player->camera->buffer[1])
    {
        shift[0] = -1 * fabsf(position_x - player->camera->buffer[1]);
    }

    // check bottom buffer
    if (position_y < player->camera->buffer[2])
    {
        shift[1] = fabsf(position_y - player->camera->buffer[2]);
    }

    // check top buffer
    if (position_y > player->camera->buffer[3])
    {
        shift[1] = -1 * fabsf(position_y - player->camera->buffer[3]);
    }
    if(player->camera->target_position && player->camera->target_position_step){
        shift_camera_smooth(player);
    }
    else{
        shift_camera(player, shift);
    }
}