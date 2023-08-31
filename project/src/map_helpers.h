#ifndef MAP_HELPERS_H
#define MAP_HELPERS_H

#include "engine/render.h"
#include "engine/physics.h"
#include "structs.h"

extern Map map;

void init_map(Map *map);
Pickup *get_pickup_from_body(Body *body);

#endif