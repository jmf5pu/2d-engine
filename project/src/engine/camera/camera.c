#include <linmath.h>
#include "../physics.h"
#include "../global.h"
#include "../physics/physics_internal.h"

static vec2 camera;

void camera_init(void)
{
    camera[0] = global.render.width * 0.5;
    camera[1] = global.render.height * 0.5;
}

void camera_update(vec2 shift)
{
    // updates camera based on the passed in vector which represents the SHIFT, not destination position
    camera[0] += shift[0]; // switch this to vec2_add?
    camera[1] += shift[1];

    // update all bodies' positions
    Body *body;
    Array_List *body_list = get_all_bodies();
    for (u32 i = 0; i < body_list->len; ++i)
    {
        body = array_list_get(body_list, i);
        body->aabb.position[0] += shift[0];
        body->aabb.position[1] += shift[1];
    }

    // update all static bodies' positions
    Static_Body *static_body;
    Array_List *static_body_list = get_all_static_bodies();
    for (u32 i = 0; i < static_body_list->len; ++i)
    {
        static_body = array_list_get(static_body_list, i);
        static_body->aabb.position[0] += shift[0];
        static_body->aabb.position[1] += shift[1];
    }
}