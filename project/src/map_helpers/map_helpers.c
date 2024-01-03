#include <stdlib.h>
#include "map_helpers.h"
#include "../engine./util.h"
#include "../engine/global.h"
#include "../enemy_helpers/enemy_helpers.h"
#include "../player_helpers/player_helpers.h"
#include "../collision_behavior/collision_behavior.h"

Map map;

// set up map & props
void init_map(Map *map)
{
    // we use these to track array length later on
    map->num_pickups = 0;
    map->num_props = 1; // min of 1, background counts as a prop
    map->num_p1_spawns = 1;
    map->num_p2_spawns = 1;
    map->num_enemy_spawns = 1;
    map->max_enemies = 1;         // max number of enemies that can be present at the same time
    map->enemy_spawn_delay = 120; // in frames
    map->frames_since_last_spawn = 0;

    Sprite_Sheet *sprite_sheet_map_1_main_bg = malloc(sizeof(Sprite_Sheet));
    render_sprite_sheet_init(sprite_sheet_map_1_main_bg, "assets/wip/shooting_range_map.png", 1199, 560);
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

    vec2 *enemy_spawn_point_array = malloc(sizeof(vec2) * map->num_enemy_spawns);
    vec2 enemy_spawn_1 = {1100, 280};
    enemy_spawn_point_array[0][0] = enemy_spawn_1[0];
    enemy_spawn_point_array[0][1] = enemy_spawn_1[1];

    /*
    Populate parent struct
    */
    map->pickups = pickup_array;
    map->props = prop_array;
    map->player_one_spawn_points = p1_spawn_point_array;
    map->player_two_spawn_points = p2_spawn_point_array;
    map->enemy_spawn_points = enemy_spawn_point_array;

    /*
    initialize enemies arraylist
    */
    init_enemies(sizeof(Zombie *), map->max_enemies);
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

// update the enemy spawns (spawn enemies if needed) TODO: potentially move this to a struct attribute, will vary from map to map
void update_enemy_spawns(Map *map)
{
    if (get_all_enemies()->len < map->max_enemies && map->frames_since_last_spawn >= map->enemy_spawn_delay)
    {
        create_enemy(map->enemy_spawn_points[0], (vec2){70, 70});
        map->frames_since_last_spawn = 0;
    }
    map->frames_since_last_spawn++;
}

// updates map attributes each frame
void update_map(Map *map)
{
    // update the pickups
    for (int i = 0; i < map->num_pickups; i++)
    {
        update_pickup_status(&map->pickups[i]);
        update_pickup_animations(&map->pickups[i]);
    }

    // update the enemies (generate if needed)
    if (map->num_enemy_spawns > 0)
    {
        update_enemy_spawns(map);
    }
    update_current_enemies();
}

// frees all map attributes that used malloc to init
void free_map_attributes(Map *map)
{
    for (int i = 0; i < map->num_props; i++)
    {
        free(map->props[i].sprite);
        for (int j = 0; j < map->props[i].num_static_bodies; j++)
        {
            free(map->props[i].static_bodies[j]);
        }
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

// moves all sprites in the particular vec2 direction. Used for camera movement
void update_all_positions(Map *map, vec2 shift, bool left_player_is_active)
{
    // update all bodies' positions (includes pickups, players, etc)
    Body *body;
    Array_List *body_list = get_all_bodies();
    for (u32 i = 0; i < body_list->len; ++i)
    {
        body = array_list_get(body_list, i);

        // shift all bodies EXCEPT the active player and crosshairs
        bool is_active_player_body = (body == player_one->entity->body && left_player_is_active) || (SPLIT_SCREEN && body == player_two->entity->body && !left_player_is_active);
        bool is_crosshair = SPLIT_SCREEN ? (body == player_one->crosshair->entity->body || body == player_two->crosshair->entity->body) : body == player_one->crosshair->entity->body;
        if (!is_active_player_body && !is_crosshair)
        {
            body->aabb.position[0] += shift[0];
            body->aabb.position[1] += shift[1];
        }
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

    // update positions of all props on the map
    for (int i = 0; i < map->num_props; i++)
    {
        Prop prop = map->props[i];
        prop.sprite->position[0] += shift[0];
        prop.sprite->position[1] += shift[1];
    }

    // spawn points are relative, no need to shift them
}