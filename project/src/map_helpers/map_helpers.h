#ifndef MAP_HELPERS_H
#define MAP_HELPERS_H

#include "../engine/physics.h"
#include "../engine/render.h"
#include "../structs.h"

extern Map map;

void init_map(Map *map);
void update_map(Map *map);
void free_map_attributes(Map *map);
Pickup *get_pickup_from_body(Body *body);
void update_all_positions(Map *map, vec2 shift, bool left_player_is_active);

#endif