#include "engine./util.h"
#include "engine/global.h"
#include "map_helpers.h"
#include "collision_behavior.h"
#include <stdlib.h>

Map map;

// set up map & props
void init_map(Map *map)
{
    // we use these to track array length later on
    map->num_pickups = 0;
    map->num_props = 1; // min of 1, background counts as a prop
    map->num_p1_spawns = 1;
    map->num_p2_spawns = 1;

    Sprite_Sheet *sprite_sheet_map_1_main_bg = malloc(sizeof(Sprite_Sheet));
    render_sprite_sheet_init(sprite_sheet_map_1_main_bg, "assets/shooting_range_map.png", 1215, 560);
    Sprite *map_1_main_bg = malloc(sizeof(Sprite));
    map_1_main_bg->sprite_sheet = sprite_sheet_map_1_main_bg;
    map_1_main_bg->row = 0;
    map_1_main_bg->column = 0;
    map_1_main_bg->position[0] = 607;
    map_1_main_bg->position[1] = 280;
    map_1_main_bg->half_size[0] = 607;
    map_1_main_bg->half_size[1] = 280;
    map_1_main_bg->z_index = -5;
    map_1_main_bg->is_flipped = false;
    map_1_main_bg->color[0] = 1;
    map_1_main_bg->color[1] = 1;
    map_1_main_bg->color[2] = 1;
    map_1_main_bg->color[3] = 1;
    Prop background_prop = (Prop){
        .sprite = map_1_main_bg,
        .layer_threshold = INT32_MIN, // this prop should ALWAYS render before (underneath) everything else
        .num_static_bodies = 4,
    };
    background_prop.static_bodies = malloc(background_prop.num_static_bodies * sizeof(Static_Body *));
    background_prop.static_bodies[0] = physics_static_body_create((vec2){607, 45}, (vec2){1230, 5}, COLLISION_LAYER_TERRAIN);  // bottom
    background_prop.static_bodies[1] = physics_static_body_create((vec2){607, 525}, (vec2){1230, 5}, COLLISION_LAYER_TERRAIN); // top
    background_prop.static_bodies[2] = physics_static_body_create((vec2){40, 280}, (vec2){5, 560}, COLLISION_LAYER_TERRAIN);   // left
    background_prop.static_bodies[3] = physics_static_body_create((vec2){1180, 280}, (vec2){5, 560}, COLLISION_LAYER_TERRAIN); // right

    /*
    Create props
    */
    Prop *prop_array = malloc(map->num_props * sizeof(Prop));
    if (!prop_array)
    {
        // Handle memory allocation error
        // ...
    }
    // populate prop array
    prop_array[0] = background_prop;

    /*
    Create pickups
    */
    Pickup *pickup_array = malloc(map->num_pickups * sizeof(Pickup));

    /*
    Create spawn points
    */
    vec2 *p1_spawn_point_array = malloc(sizeof(vec2) * map->num_p1_spawns);
    vec2 p1_spawn_1 = {100, 200};
    p1_spawn_point_array[0][0] = p1_spawn_1[0];
    p1_spawn_point_array[0][1] = p1_spawn_1[1];

    vec2 *p2_spawn_point_array = malloc(sizeof(vec2) * map->num_p2_spawns);
    vec2 p2_spawn_1 = {100, 100};
    p2_spawn_point_array[0][0] = p2_spawn_1[0];
    p2_spawn_point_array[0][1] = p2_spawn_1[1];

    /*
    Populate parent struct
    */
    map->pickups = pickup_array;
    map->props = prop_array;
    map->player_one_spawn_points = p1_spawn_point_array;
    map->player_two_spawn_points = p2_spawn_point_array;
}

// updates the status of a pickup, should be called once per frame for each pickup
void update_pickup_status(Pickup *pickup)
{
    // inactive to spawning
    if (pickup->status == PICKUP_INACTIVE && pickup->frames_on_status >= (pickup->spawn_delay * global.time.frame_rate))
    {

        pickup->status = PICKUP_SPAWNING;
        pickup->entity->body->is_active = true;
        pickup->frames_on_status = 0;
    }
    // spawning to active
    else if (pickup->status == PICKUP_SPAWNING && pickup->frames_on_status >= (pickup->spawn_time * global.time.frame_rate))
    {

        pickup->status = PICKUP_ACTIVE;
        pickup->frames_on_status = 0;
    }

    // active to inactive is handled in player_on_hit in collision_behavior.c

    pickup->frames_on_status++;
}

// updates pickup animations, should be called once per frame for each pickup
void update_pickup_animations(Pickup *pickup)
{
    if (pickup->status == PICKUP_SPAWNING)
    {
        pickup->entity->animation = pickup->animation_set->spawning;
    }
    else if (pickup->status == PICKUP_ACTIVE)
    {
        pickup->entity->animation = pickup->animation_set->active;
    }
}

// updates all pickup statuses and animations, should be called once per frame
void update_map(Map *map)
{
    for (int i = 0; i < map->num_pickups; i++)
    {
        update_pickup_status(&map->pickups[i]);
        update_pickup_animations(&map->pickups[i]);
    }
}

// frees all map attributes that used malloc to init
void free_map_attributes(Map *map)
{
    for (int i = 0; i < map->num_props; i++)
    {
        free(&map->props[i].sprite);
        for (int j = 0; j < map->props[i].num_static_bodies; j++)
        {
            free(map->props[i].static_bodies[j]);
        }
        free(&map->props[i]);
    }
    for (int i = 0; i < map->num_pickups; i++)
    {
        free(&map->pickups[i]);
    }

    free(map->props);
    free(map->pickups);
}

// returns the pickup associated with a physics body if it exists in the current map, returns NULL if not found
Pickup *get_pickup_from_body(Body *body)
{
    if (!map.pickups)
    {
        ERROR_EXIT("ERROR: Map not yet initialized or initialized incorrectly.\n")
    }

    for (int i = 0; i < map.num_pickups; i++)
    {
        if (map.pickups[i].entity->body == body)
        {
            return &map.pickups[i];
        }
    }

    return NULL;
}