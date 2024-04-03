#include "map_helpers.h"
#include "../collision_behavior/collision_behavior.h"
#include "../enemy_helpers/enemy_helpers.h"
#include "../engine./util.h"
#include "../engine/global.h"
#include "../player_helpers/player_helpers.h"
#include <stdlib.h>

Map map;

void init_map_assets(void)
{
    render_sprite_sheet_init(&sprite_sheet_bunker_background, "assets/wip/bunker_map.png", 327, 195);
    adef_bunker_background = animation_definition_create(&sprite_sheet_bunker_background, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bunker_background = animation_create(adef_bunker_background, false);
    anim_bunker_background->z_index = INT32_MIN;

    render_sprite_sheet_init(&sprite_sheet_metal_table_vertical_1, "assets/wip/metal_table_vertical_1.png", 23, 48);
    adef_metal_table_vertical_1 = animation_definition_create(&sprite_sheet_metal_table_vertical_1, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_metal_table_vertical_1 = animation_create(adef_metal_table_vertical_1, false);
    anim_metal_table_vertical_1->z_index = -5;

    render_sprite_sheet_init(&sprite_sheet_metal_table_vertical_2, "assets/wip/metal_table_vertical_2.png", 23, 48);
    adef_metal_table_vertical_2 = animation_definition_create(&sprite_sheet_metal_table_vertical_2, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_metal_table_vertical_2 = animation_create(adef_metal_table_vertical_2, false);
    anim_metal_table_vertical_2->z_index = anim_metal_table_vertical_1->z_index + 1;
}

// set up map & props
void init_map(Map *map)
{
    init_map_assets();

    // we use these to track array length later on
    map->num_pickups = 0;
    map->num_p1_spawns = 1;
    map->num_p2_spawns = 1;
    map->num_enemy_spawns = 1;
    map->max_enemies = 1;         // max number of enemies that can be present at the same time
    map->enemy_spawn_delay = 120; // in frames
    map->frames_since_last_spawn = 0;

    Entity *bunker_background = entity_create((vec2){163.5, 97.5}, (vec2){327, 195}, (vec2){0, 0}, 0, 0, NULL, NULL);
    bunker_background->animation = anim_bunker_background;
    physics_static_body_create((vec2){163.5, 10}, (vec2){327, 5},
                               COLLISION_LAYER_TERRAIN);                                     // bottom
    physics_static_body_create((vec2){163.5, 185}, (vec2){327, 5}, COLLISION_LAYER_TERRAIN); // top
    physics_static_body_create((vec2){5, 97.5}, (vec2){5, 195}, COLLISION_LAYER_TERRAIN);    // left
    physics_static_body_create((vec2){322, 97.5}, (vec2){5, 195},
                               COLLISION_LAYER_TERRAIN); // right

    Entity *metal_table_1 = entity_create((vec2){21, 88}, (vec2){23, 48}, (vec2){0, 0}, 0, 0, NULL, NULL);
    metal_table_1->animation = anim_metal_table_vertical_1;
    Entity *metal_table_2 = entity_create((vec2){22, 45}, (vec2){23, 48}, (vec2){0, 0}, 0, 0, NULL, NULL);
    metal_table_2->animation = anim_metal_table_vertical_2;
    physics_static_body_create((vec2){22, 69}, (vec2){23, 96}, COLLISION_LAYER_TERRAIN);

    // Animation *anim_metal_table = malloc(sizeof(Sprite_Sheet));
    // render_sprite_sheet_init(sprite_sheet_metal_table_vertical_1, "assets/wip/metal_table_vertical_1.png", 23, 48);
    // Sprite *sprite_metal_table_vertical_1 = malloc(sizeof(Sprite));

    /*
    Create pickups
    */
    Pickup *pickup_array = malloc(map->num_pickups * sizeof(Pickup));

    /*
    Create spawn points
    */
    vec2 *p1_spawn_point_array = malloc(sizeof(vec2) * map->num_p1_spawns);
    vec2 p1_spawn_1 = {75, 50};
    p1_spawn_point_array[0][0] = p1_spawn_1[0];
    p1_spawn_point_array[0][1] = p1_spawn_1[1];

    vec2 *p2_spawn_point_array = malloc(sizeof(vec2) * map->num_p2_spawns);
    vec2 p2_spawn_1 = {75, 25};
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
    map->player_one_spawn_points = p1_spawn_point_array;
    map->player_two_spawn_points = p2_spawn_point_array;
    map->enemy_spawn_points = enemy_spawn_point_array;

    /*
    initialize enemies arraylist
    */
    init_enemies(sizeof(Zombie *), map->max_enemies);
}

// updates the status of a pickup, should be called once per frame for each
// pickup
void update_pickup_status(Pickup *pickup)
{
    // inactive to spawning
    if (pickup->status == PICKUP_INACTIVE && pickup->frames_on_status >= (pickup->spawn_delay * global.time.frame_rate)) {

        pickup->status = PICKUP_SPAWNING;
        pickup->entity->body->is_active = true;
        pickup->frames_on_status = 0;
    }
    // spawning to active
    else if (pickup->status == PICKUP_SPAWNING && pickup->frames_on_status >= (pickup->spawn_time * global.time.frame_rate)) {

        pickup->status = PICKUP_ACTIVE;
        pickup->frames_on_status = 0;
    }

    // active to inactive is handled in player_on_hit in
    // collision_behavior.c

    pickup->frames_on_status++;
}

// updates pickup animations, should be called once per frame for each pickup
void update_pickup_animations(Pickup *pickup)
{
    if (pickup->status == PICKUP_SPAWNING) {
        pickup->entity->animation = pickup->animation_set->spawning;
    }
    else if (pickup->status == PICKUP_ACTIVE) {
        pickup->entity->animation = pickup->animation_set->active;
    }
}

// update the enemy spawns (spawn enemies if needed) TODO: potentially move this
// to a struct attribute, will vary from map to map
void update_enemy_spawns(Map *map)
{
    if (get_all_enemies()->len < map->max_enemies && map->frames_since_last_spawn >= map->enemy_spawn_delay) {
        create_enemy(map->enemy_spawn_points[0], (vec2){70, 70});
        map->frames_since_last_spawn = 0;
    }
    map->frames_since_last_spawn++;
}

// updates map attributes each frame
void update_map(Map *map)
{
    // update the pickups
    for (int i = 0; i < map->num_pickups; i++) {
        update_pickup_status(&map->pickups[i]);
        update_pickup_animations(&map->pickups[i]);
    }

    // update the enemies (generate if needed)
    if (map->num_enemy_spawns > 0) {
        update_enemy_spawns(map);
    }
    update_current_enemies();
}

// frees all map attributes that used malloc to init
void free_map_attributes(Map *map)
{
    free(map->pickups);
    free(map->player_one_spawn_points);
    free(map->player_two_spawn_points);
}

// returns the pickup associated with a physics body if it exists in the current
// map, returns NULL if not found
Pickup *get_pickup_from_body(Body *body)
{
    if (!map.pickups) {
        ERROR_EXIT("ERROR: Map not yet initialized or initialized "
                   "incorrectly.\n")
    }

    for (int i = 0; i < map.num_pickups; i++) {
        if (map.pickups[i].entity->body == body) {
            return &map.pickups[i];
        }
    }

    return NULL;
}

/// @brief Moves all static bodies and bodies ( and therefore entities ) by the shift parameter. Used for camera movements.
/// @param map
/// @param shift
/// @param left_player_is_active
void update_all_positions(Map *map, vec2 shift, bool left_player_is_active)
{
    // update all bodies' positions (includes pickups, players, etc)
    Body *body;
    Array_List *body_list = get_all_bodies();
    for (u32 i = 0; i < body_list->len; ++i) {
        body = array_list_get(body_list, i);

        // shift all bodies EXCEPT the active player and crosshairs
        bool is_active_player_body = (body == player_one->entity->body && left_player_is_active) || (SPLIT_SCREEN && body == player_two->entity->body && !left_player_is_active);
        bool is_crosshair = SPLIT_SCREEN ? (body == player_one->crosshair->body || body == player_two->crosshair->body) : body == player_one->crosshair->body;
        if (!is_active_player_body && !is_crosshair) {
            vec2_add(body->aabb.position, body->aabb.position, shift);
        }
    }

    // update all static bodies' positions
    Static_Body *static_body;
    Array_List *static_body_list = get_all_static_bodies();
    for (u32 i = 0; i < static_body_list->len; ++i) {
        static_body = array_list_get(static_body_list, i);
        vec2_add(static_body->aabb.position, static_body->aabb.position, shift);
    }

    // spawn points are relative, no need to shift them
}