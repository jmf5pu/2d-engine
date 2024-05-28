#include "map_helpers.h"
#include "../collision_behavior/collision_behavior.h"
#include "../enemy_helpers/enemy_helpers.h"
#include "../engine./util.h"
#include "../engine/global.h"
#include "../player_helpers/player_helpers.h"
#include "../structs.h"
#include <stdlib.h>

Map map;

const u8 TELEPORTER_DIMENSIONS[] = {19, 19};
const u8 TELEPORTER_GLOW_DIMENSIONS[] = {15, 32};

const f32 TELEPORTER_ACTIVE_DURATIONS[] = {0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04};
const u8 TELEPORTER_ACTIVE_ROWS[] = {0, 0, 0, 0, 0, 0, 0, 0};
const u8 TELEPORTER_ACTIVE_COLS[] = {1, 2, 3, 4, 5, 6, 7, 8};

const f32 TELEPORTER_SPINNING_DURATIONS[] = {0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.08};
const u8 TELEPORTER_SPINNING_ROWS[] = {0, 0, 0, 0, 0, 0, 0, 0};
const u8 TELEPORTER_SPINNING_COLS[] = {1, 2, 3, 4, 5, 6, 7, 8};

const f32 TELEPORTER_GLOW_DURATIONS[] = {0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1};
const u8 TELEPORTER_GLOW_ROWS[] = {0, 0, 0, 0, 0, 0, 0, 0};
const u8 TELEPORTER_GLOW_COLS[] = {1, 2, 3, 4, 5, 6, 7, 8};

// set up map & props
void init_map(Map *map)
{
    init_map_assets();

    // we use these to track array length later on
    map->num_p1_spawns = 1;
    map->num_p2_spawns = 1;
    map->num_enemy_spawners = 1;
    map->max_enemies = 1; // max number of enemies that can be present at the same time
    map->num_dynamic_props = 2;

    init_map_props(map);

    // create spawn points
    vec2 *p1_spawn_point_array = malloc(sizeof(vec2) * map->num_p1_spawns);
    vec2 p1_spawn_1 = {75, 50};
    p1_spawn_point_array[0][0] = p1_spawn_1[0];
    p1_spawn_point_array[0][1] = p1_spawn_1[1];

    vec2 *p2_spawn_point_array = malloc(sizeof(vec2) * map->num_p2_spawns);
    vec2 p2_spawn_1 = {75, 25};
    p2_spawn_point_array[0][0] = p2_spawn_1[0];
    p2_spawn_point_array[0][1] = p2_spawn_1[1];

    TimeSpawner *enemy_spawner_array = malloc(sizeof(TimeSpawner) * map->num_enemy_spawners);
    TimeSpawner enemy_spawner_1 =
        (TimeSpawner){.is_active = true, .max_frames_seconds = 10 * FRAME_RATE, .wait_frames_remaining = 10 * FRAME_RATE, .position = {250, 100}, .spawn = spawn_zombie};
    enemy_spawner_array[0] = enemy_spawner_1;

    // Populate parent struct
    map->player_one_spawn_points = p1_spawn_point_array;
    map->player_two_spawn_points = p2_spawn_point_array;
    map->enemy_spawners = enemy_spawner_array;

    // initialize enemies arraylist
    init_enemies(sizeof(Zombie *), map->max_enemies);
}

// updates map attributes each frame
void update_map(Map *map)
{
    update_spawners(map);
    update_dynamic_props(map);
    update_current_enemies();
}

/// @brief Update state of all dynamic props associated with the map
/// @param map
void update_dynamic_props(Map *map)
{
    for (int i = 0; i < map->num_dynamic_props; i++) {
        DynamicProp *prop = map->dynamic_props[i];
        prop->update_state(prop->entity, &prop->state);
    }
}

/// @brief Update all enemy spawners associated with the map
/// @param map
void update_spawners(Map *map)
{
    for (int i = 0; i < map->num_enemy_spawners; i++) {
        if (map->enemy_spawners[i].is_active)
            update_spawner(&map->enemy_spawners[i]);
    }
}

void update_spawner(TimeSpawner *spawner)
{
    spawner->wait_frames_remaining--;
    if (spawner->wait_frames_remaining == 0) {
        spawner->wait_frames_remaining = spawner->max_frames_seconds;
        spawner->spawn(spawner->position);
    }
}

// frees all map attributes that used malloc to init
void free_map_attributes(Map *map)
{
    free(map->player_one_spawn_points);
    free(map->player_two_spawn_points);
    free(map->enemy_spawners);
    for (int i = 0; i < map->num_dynamic_props; i++) {
        free(map->dynamic_props[i]);
    }
    free(map->dynamic_props);
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

void init_map_assets(void)
{
    const u8 teleporter_num_frames = (u8)ARRAY_LENGTH(TELEPORTER_ACTIVE_COLS);
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

    render_sprite_sheet_init(&sprite_sheet_m16_pickup, "assets/wip/m16_pickup.png", 20, 9);
    adef_m16_pickup = animation_definition_create(&sprite_sheet_m16_pickup, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_pickup = animation_create(adef_m16_pickup, false);
    render_sprite_sheet_init(&sprite_sheet_glock_pickup, "assets/wip/glock_pickup.png", 7, 9);
    adef_glock_pickup = animation_definition_create(&sprite_sheet_glock_pickup, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_glock_pickup = animation_create(adef_glock_pickup, false);

    render_sprite_sheet_init(&sprite_sheet_teleporter_inactive, "assets/wip/teleporter_spinning.png", TELEPORTER_DIMENSIONS[0], TELEPORTER_DIMENSIONS[1]);
    adef_teleporter_inactive = animation_definition_create(&sprite_sheet_teleporter_inactive, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_teleporter_active, "assets/wip/teleporter_active.png", TELEPORTER_DIMENSIONS[0], TELEPORTER_DIMENSIONS[1]);
    adef_teleporter_active = animation_definition_create(
        &sprite_sheet_teleporter_active, (f32 *)TELEPORTER_ACTIVE_DURATIONS, (u8 *)TELEPORTER_ACTIVE_ROWS, (u8 *)TELEPORTER_ACTIVE_COLS, (u8)ARRAY_LENGTH(TELEPORTER_ACTIVE_COLS));
    render_sprite_sheet_init(&sprite_sheet_teleporter_spinning, "assets/wip/teleporter_spinning.png", TELEPORTER_DIMENSIONS[0], TELEPORTER_DIMENSIONS[1]);
    adef_teleporter_spinning = animation_definition_create(
        &sprite_sheet_teleporter_spinning,
        (f32 *)TELEPORTER_SPINNING_DURATIONS,
        (u8 *)TELEPORTER_SPINNING_ROWS,
        (u8 *)TELEPORTER_SPINNING_COLS,
        (u8)ARRAY_LENGTH(TELEPORTER_SPINNING_COLS));
    render_sprite_sheet_init(&sprite_sheet_teleporter_glow, "assets/wip/teleporter_glow.png", TELEPORTER_GLOW_DIMENSIONS[0], TELEPORTER_GLOW_DIMENSIONS[1]);
    adef_teleporter_glow = animation_definition_create(
        &sprite_sheet_teleporter_glow, (f32 *)TELEPORTER_GLOW_DURATIONS, (u8 *)TELEPORTER_GLOW_ROWS, (u8 *)TELEPORTER_GLOW_COLS, (u8)ARRAY_LENGTH(TELEPORTER_GLOW_COLS));
}

void init_map_props(Map *map)
{
    init_map_background_prop();
    init_metal_table_props();
    init_pickup_props();

    map->dynamic_props = malloc(sizeof(DynamicProp *) * map->num_dynamic_props);
    map->dynamic_props[0] = init_teleporter_prop();
    map->dynamic_props[1] = init_button_prop();
}

void init_map_background_prop(void)
{
    Entity *bunker_background = entity_create((vec2){163.5, 97.5}, (vec2){327, 195}, (vec2){0, 0}, 0, 0, NULL, NULL);
    bunker_background->animation = anim_bunker_background;
    physics_static_body_create((vec2){163.5, 10}, (vec2){327, 5},
                               COLLISION_LAYER_TERRAIN);                                     // bottom
    physics_static_body_create((vec2){163.5, 185}, (vec2){327, 5}, COLLISION_LAYER_TERRAIN); // top
    physics_static_body_create((vec2){5, 97.5}, (vec2){5, 195}, COLLISION_LAYER_TERRAIN);    // left
    physics_static_body_create((vec2){322, 97.5}, (vec2){5, 195},
                               COLLISION_LAYER_TERRAIN); // right
}

void init_metal_table_props(void)
{
    Entity *metal_table_1 = entity_create((vec2){21, 88}, (vec2){23, 48}, (vec2){0, 0}, 0, 0, NULL, NULL);
    metal_table_1->animation = anim_metal_table_vertical_1;
    Entity *metal_table_2 = entity_create((vec2){22, 45}, (vec2){23, 48}, (vec2){0, 0}, 0, 0, NULL, NULL);
    metal_table_2->animation = anim_metal_table_vertical_2;
    physics_static_body_create((vec2){22, 69}, (vec2){23, 96}, COLLISION_LAYER_TERRAIN);
}

DynamicProp *init_teleporter_prop(void)
{
    DynamicProp *teleporter = malloc(sizeof(DynamicProp));
    teleporter->entity = entity_create((vec2){150, 100}, (vec2){TELEPORTER_DIMENSIONS[0], TELEPORTER_DIMENSIONS[1]}, (vec2){0, 0}, 0, 0, NULL, NULL);
    teleporter->state.teleporter_state_enum = INACTIVE;
    teleporter->update_state = teleporter_update_state;
    teleporter->type = TELEPORTER;
    teleporter->entity->animation = animation_create(adef_teleporter_inactive, false);
    teleporter->entity->animation->z_index = -1;
    teleporter->entity->body->parent = teleporter;
    return teleporter;
}

DynamicProp *init_button_prop(void)
{
    DynamicProp *teleporter_button = malloc(sizeof(DynamicProp));
    teleporter_button->entity = entity_create((vec2){50, 50}, (vec2){12, 12}, (vec2){0, 0}, COLLISION_LAYER_BUTTON, COLLISION_LAYER_PLAYER, teleporter_button_on_hit, NULL);
    teleporter_button->state.button_state_enum = UNPRESSED;
    teleporter_button->update_state = teleporter_button_update_state;
    teleporter_button->type = TELEPORTER_BUTTON;
    teleporter_button->entity->body->parent = teleporter_button;
    // TODO: assign initial anim here, update z index
    return teleporter_button;
}

void init_pickup_props(void)
{
    Entity *m16_pickup = entity_create((vec2){27, 55}, (vec2){20, 9}, (vec2){0, 0}, COLLISION_LAYER_PICKUP, COLLISION_LAYER_PLAYER, m16_pickup_on_hit, NULL);
    m16_pickup->animation = anim_m16_pickup;
    Entity *glock_pickup = entity_create((vec2){35, 70}, (vec2){7, 9}, (vec2){0, 0}, COLLISION_LAYER_PICKUP, COLLISION_LAYER_PLAYER, glock_pickup_on_hit, NULL);
    glock_pickup->animation = anim_glock_pickup;
}