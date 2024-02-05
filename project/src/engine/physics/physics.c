#include "../physics.h"
#include "../array_list.h"
#include "../global.h"
#include "../util.h"
#include "physics_internal.h"
#include <linmath.h>

static Physics_State_Internal state;

static u32 iterations = 60;
static f32 tick_rate;

// returns all bodies
Array_List *get_all_bodies(void) { return state.body_list; }

// returns all static bodies
Array_List *get_all_static_bodies(void) { return state.static_body_list; }

void physics_init(void)
{
    state.body_list = array_list_create(sizeof(struct Body *), 0);
    state.static_body_list = array_list_create(sizeof(struct Static_Body *), 0);

    state.gravity = 0;
    state.terminal_velocity = -7000;

    tick_rate = 1.f / iterations;
}

static void update_sweep_result(
    Hit *result,
    usize other_id,
    AABB a,
    AABB b,
    vec2 velocity,
    u8 a_collision_mask,
    u8 b_collision_layer) // TODO: bug here
{
    if ((a_collision_mask & b_collision_layer) == 0) {
        return;
    }
    AABB sum_aabb = b;
    vec2_add(sum_aabb.half_size, sum_aabb.half_size, a.half_size);

    Hit hit = ray_intersect_aabb(a.position, velocity, sum_aabb);
    if (hit.is_hit) {
        if (hit.time < result->time) {
            // if hit is sooner than currently stored time, assign
            // hit
            *result = hit;
        }
        else if (hit.time == result->time) {
            // if it is at the same time, solve highest velocity
            // axis first
            if (fabsf(velocity[0]) > fabsf(velocity[1]) && hit.normal[0] != 0) {
                *result = hit;
            }
            else if (
                fabsf(velocity[1]) > fabsf(velocity[0]) && hit.normal[1] != 0) {
                *result = hit;
            }
        }
        result->other_id = other_id;
    }
}

static Hit sweep_static_bodies(Body *body, vec2 velocity) // TODO: bug here
{
    Hit result = {.time = 0xBEEF}; // time set to some large value

    for (u32 i = 0; i < state.static_body_list->len; ++i) {
        Static_Body *static_body = physics_static_body_get(i);
        update_sweep_result(
            &result,
            i,
            body->aabb,
            static_body->aabb,
            velocity,
            body->collision_mask,
            static_body->collision_layer);
    }
    return result;
}

static Hit sweep_bodies(Body *body, vec2 velocity)
{
    Hit result = {.time = 0xBEEF}; // time set to some large value

    for (u32 i = 0; i < state.body_list->len; ++i) {
        Body *other = physics_body_get(i);

        if (body == other) {
            continue;
        }

        update_sweep_result(
            &result,
            i,
            body->aabb,
            other->aabb,
            velocity,
            body->collision_mask,
            other->collision_layer);
    }
    return result;
}

static void sweep_response(Body *body, vec2 velocity)
{
    Hit hit = sweep_static_bodies(body, velocity);
    Hit hit_moving = sweep_bodies(body, velocity);
    if (hit_moving.is_hit) {
        if (body->on_hit != NULL) {
            body->on_hit(
                body, physics_body_get(hit_moving.other_id), hit_moving);
        }
    }

    if (hit.is_hit) {
        // check with axis collided, update that
        body->aabb.position[0] = hit.position[0];
        body->aabb.position[1] = hit.position[1];
        if (hit.normal[0] != 0) {
            body->aabb.position[1] += velocity[1];
            body->velocity[0] = 0;
        }
        else if (hit.normal[1] != 0) {
            body->aabb.position[0] += velocity[0];
            body->velocity[1] = 0;
        }

        if (body->on_hit_static != NULL) {
            body->on_hit_static(
                body, physics_static_body_get(hit.other_id), hit);
        }
    }
    else {
        // no hit? Then update position on both axes
        vec2_add(body->aabb.position, body->aabb.position, velocity);
    }
}

static void stationary_response(Body *body)
{
    for (u32 i = 0; i < state.static_body_list->len; ++i) {
        Static_Body *static_body = physics_static_body_get(i);
        if ((static_body->collision_layer & body->collision_mask) == 0) {
            continue;
        }
        AABB aabb = aabb_minkowski_difference(static_body->aabb, body->aabb);
        vec2 min, max;
        aabb_min_max(min, max, aabb);

        if (min[0] <= 0 && max[0] >= 0 && min[1] <= 0 && max[1] >= 0) {
            vec2 penetration_vector;
            aabb_penetration_vector(penetration_vector, aabb);

            vec2_add(
                body->aabb.position, body->aabb.position, penetration_vector);
        }
    }
}

void physics_update(void)
{
    Body *body;

    for (u32 i = 0; i < state.body_list->len; ++i) {
        body = array_list_get(state.body_list, i);

        // update velocity based on acceleration
        body->velocity[0] += body->acceleration[0];
        body->velocity[1] += body->acceleration[1];

        vec2 scaled_velocity;
        vec2_scale(
            scaled_velocity, body->velocity, global.time.delta * tick_rate);

        for (u32 j = 0; j < iterations; ++j) {
            sweep_response(body, scaled_velocity);
            stationary_response(body);
        }
    }
}

Body *physics_body_create(
    vec2 position,
    vec2 size,
    vec2 velocity,
    u8 collision_layer,
    u8 collision_mask,
    On_Hit on_hit,
    On_Hit_Static on_hit_static)
{
    Body *body =
        (Body *)malloc(sizeof(Body)); // Allocate memory for the Body struct

    if (body == NULL) {
        ERROR_EXIT("Memory allocation failed\n");
    }

    body->aabb.position[0] = position[0];
    body->aabb.position[1] = position[1];
    body->aabb.half_size[0] = size[0] * 0.5;
    body->aabb.half_size[1] = size[1] * 0.5;

    body->velocity[0] = velocity[0];
    body->velocity[1] = velocity[1];
    body->acceleration[0] = 0;
    body->acceleration[1] = 0;

    body->collision_layer = collision_layer;
    body->collision_mask = collision_mask;

    body->on_hit = on_hit;
    body->on_hit_static = on_hit_static;

    body->is_active = true;

    if (array_list_append(state.body_list, body) == (usize)-1) {
        free(body); // Clean up allocated memory in case of failure
        ERROR_EXIT("Could not append body to list\n");
    }
    return body;
}

usize physics_body_count() { return state.body_list->len; }

Body *physics_body_get(usize index)
{
    return array_list_get(state.body_list, index);
}

usize physics_body_get_id(Body *target_body)
{
    for (usize i = 0; i < state.body_list->len; ++i) {
        if (physics_body_get(i) == target_body) {
            return i;
        }
    }
    ERROR_EXIT(
        "ERROR: Could not find the specified entity in the Array_List\n");
}

void physics_body_destroy(Body *body)
{
    usize id = physics_body_get_id(body);
    array_list_remove(state.body_list, id);
    free(body);
}

Static_Body *
physics_static_body_create(vec2 position, vec2 size, u8 collision_layer)
{
    Static_Body *static_body = (Static_Body *)malloc(
        sizeof(Static_Body)); // Allocate memory for the Static_Body

    if (static_body == NULL) {
        ERROR_EXIT("Memory allocation failed\n");
    }

    static_body->aabb.position[0] = position[0];
    static_body->aabb.position[1] = position[1];
    static_body->aabb.half_size[0] = size[0] * 0.5;
    static_body->aabb.half_size[1] = size[1] * 0.5;

    static_body->collision_layer = collision_layer;

    if (array_list_append(state.static_body_list, static_body) == (usize)-1) {
        free(static_body); // Clean up allocated memory in case of
                           // failure
        ERROR_EXIT("Could not append body to list\n");
    }

    return static_body;
}

Static_Body *physics_static_body_get(usize index)
{
    return array_list_get(state.static_body_list, index);
}

// gets the minimium and maximum position of the aabb
void aabb_min_max(vec2 min, vec2 max, AABB aabb)
{
    vec2_sub(min, aabb.position, aabb.half_size);
    vec2_add(max, aabb.position, aabb.half_size);
}

// bounds check using min/max
bool physics_point_intersect_aabb(vec2 point, AABB aabb)
{
    vec2 min, max;
    aabb_min_max(min, max, aabb);
    return point[0] >= min[0] && point[0] <= max[0] && point[1] >= min[1] &&
           point[1] <= max[1];
}

// gets minkowski difference of the two boxes, gets min and max of result
// then checks if the origin is inside
bool physics_aabb_intersect_aabb(AABB a, AABB b)
{
    vec2 min, max;
    aabb_min_max(min, max, aabb_minkowski_difference(a, b));
    bool contains_origin =
        (min[0] <= 0 && max[0] >= 0 && min[1] <= 0 && max[1] >= 0);
    return contains_origin;
}

// subtract the positions of the boxes, then add the sizes together
AABB aabb_minkowski_difference(AABB a, AABB b)
{
    AABB result;
    vec2_sub(result.position, a.position, b.position);
    vec2_add(result.half_size, a.half_size, b.half_size);
    return result;
}

// calculate the smallest vector that will separate the box
void aabb_penetration_vector(vec2 r, AABB aabb)
{
    vec2 min, max;
    aabb_min_max(min, max, aabb);

    f32 min_dist = fabsf(min[0]);
    r[0] = min[0];
    r[1] = 0;

    if (fabsf(max[0]) < min_dist) {
        min_dist = fabsf(max[0]);
        r[0] = max[0];
    }

    if (fabsf(min[1]) < min_dist) {
        min_dist = fabsf(min[1]);
        r[0] = 0;
        r[1] = min[1];
    }

    if (fabsf(max[1]) < min_dist) {
        r[0] = 0;
        r[1] = max[1];
    }
}

Hit ray_intersect_aabb(vec2 pos, vec2 magnitude, AABB aabb)
{
    Hit hit = {0};
    vec2 min, max;
    aabb_min_max(min, max, aabb);

    f32 last_entry = -INFINITY;
    f32 first_exit = INFINITY;

    for (u8 i = 0; i < 2; ++i) {
        if (magnitude[i] != 0) {
            f32 t1 = (min[i] - pos[i]) / magnitude[i];
            f32 t2 = (max[i] - pos[i]) / magnitude[i];

            last_entry = fmaxf(last_entry, fminf(t1, t2));
            first_exit = fminf(first_exit, fmaxf(t1, t2));
        }
        else if (pos[i] <= min[i] || pos[i] >= max[i]) {
            return hit;
        }
    }

    if (first_exit > last_entry && first_exit > 0 && last_entry < 1) {
        hit.position[0] = pos[0] + magnitude[0] * last_entry;
        hit.position[1] = pos[1] + magnitude[1] * last_entry;

        hit.is_hit = true;
        hit.time = last_entry;

        f32 dx = hit.position[0] - aabb.position[0];
        f32 dy = hit.position[1] - aabb.position[1];
        f32 px = aabb.half_size[0] - fabsf(dx);
        f32 py = aabb.half_size[1] - fabsf(dy);

        // gives -1 when hit is on the left, 1 when on right (sin)
        if (px < py) {
            hit.normal[0] = (dx > 0) - (dx < 0);
        }
        else {
            hit.normal[1] = (dy > 0) - (dy < 0);
        }
    }

    return hit;
}