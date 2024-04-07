#ifndef MAP_HELPERS_H
#define MAP_HELPERS_H

#include "../engine/physics.h"
#include "../engine/render.h"
#include "../structs.h"

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

Sprite_Sheet sprite_sheet_m16_pickup;
Animation_Definition *adef_m16_pickup;
Animation *anim_m16_pickup;

Sprite_Sheet sprite_sheet_glock_pickup;
Animation_Definition *adef_glock_pickup;
Animation *anim_glock_pickup;

void init_map(Map *map);
void update_map(Map *map);
void free_map_attributes(Map *map);
void update_all_positions(Map *map, vec2 shift, bool left_player_is_active);

#endif