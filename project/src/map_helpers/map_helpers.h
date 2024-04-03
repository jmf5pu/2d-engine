#ifndef MAP_HELPERS_H
#define MAP_HELPERS_H

#include "../engine/physics.h"
#include "../engine/render.h"
#include "../structs.h"

typedef struct map {
    // these indicate the lengths of their respective arrays
    usize num_pickups;
    usize num_p1_spawns;
    usize num_p2_spawns;
    usize num_enemy_spawns;
    usize max_enemies;

    // used when calculating when to spawn enemies
    i32 enemy_spawn_delay;
    i32 frames_since_last_spawn;

    Pickup *pickups;               // start of pickups array
    vec2 *player_one_spawn_points; // player one's spawn points
    vec2 *player_two_spawn_points; // player two's spawn points
    vec2 *enemy_spawn_points;
} Map;

extern Map map;

Sprite_Sheet sprite_sheet_bunker_background;
Animation_Definition *adef_bunker_background;
Animation *anim_bunker_background;

Sprite_Sheet sprite_sheet_metal_table_vertical_1;
Animation_Definition *adef_metal_table_vertical_1;
Animation *anim_metal_table_vertical_1;

Sprite_Sheet sprite_sheet_metal_table_vertical_2;
Animation_Definition *adef_metal_table_vertical_2;
Animation *anim_metal_table_vertical_2;

void init_map(Map *map);
void update_map(Map *map);
void free_map_attributes(Map *map);
Pickup *get_pickup_from_body(Body *body);
void update_all_positions(Map *map, vec2 shift, bool left_player_is_active);

#endif