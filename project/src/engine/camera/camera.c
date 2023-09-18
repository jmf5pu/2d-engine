#include <linmath.h>
#include "../physics.h"
#include "../global.h"
#include "../physics/physics_internal.h"
#include "../render.h"
#include "../../structs.h"

static vec2 camera;

void camera_init()
{
    camera[0] = WINDOW_WIDTH * 0.5;
    camera[1] = WINDOW_HEIGHT * 0.5;
}

void shift_camera(vec2 shift, Map *map)
{
    // updates camera based on the passed in vector which represents the SHIFT, not destination position
    camera[0] += shift[0]; // switch this to vec2_add?
    camera[1] += shift[1];

    // update all bodies' positions
    Body *body;
    Array_List *body_list = get_all_bodies();
    for (u32 i = 0; i < body_list->len; ++i)
    {
        body = array_list_get(body_list, i, "in camera update\n");
        body->aabb.position[0] += shift[0];
        body->aabb.position[1] += shift[1];
    }

    // update all static bodies' positions
    Static_Body *static_body;
    Array_List *static_body_list = get_all_static_bodies();
    for (u32 i = 0; i < static_body_list->len; ++i)
    {
        static_body = array_list_get(static_body_list, i, "in camera update\n");
        static_body->aabb.position[0] += shift[0];
        static_body->aabb.position[1] += shift[1];
    }

    // update positions of all props on the map
    for (int i = 0; i < map->num_props; i++)
    {
        Prop prop = map->props[i];
        prop.sprite->position[0] += shift[0];
        prop.sprite->position[1] += shift[1];
    }
}

void camera_update(Body *body_player, Map *map, int buffer)
{
    // updates the camera based on the player's position
    float position_x = body_player->aabb.position[0];
    float position_y = body_player->aabb.position[1];

    // check if we have breached left buffer, if so, correct camera
    if (position_x - buffer <= 0)
    {
        shift_camera((vec2){fabsf(position_x - buffer), 0}, map);
    }

    // check right buffer
    if (position_x + buffer >= WINDOW_WIDTH)
    {
        shift_camera((vec2){(-1 * fabsf(position_x - (WINDOW_WIDTH - buffer))), 0}, map);
    }

    // check top buffer
    if (position_y + buffer >= WINDOW_HEIGHT)
    {
        shift_camera((vec2){0, -1 * fabsf(position_y - (WINDOW_HEIGHT - buffer))}, map);
    }

    // check bottom buffer
    if (position_y - buffer <= 0)
    {
        shift_camera((vec2){0, fabsf(position_y - buffer)}, map);
    }
}