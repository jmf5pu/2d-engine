#ifndef MAP_HELPERS_H
#define MAP_HELPERS_H

#include "engine/render.h"
#include "engine/physics.h"
#include "structs.h"

extern Map map;

// pickup sprites & anims
Sprite_Sheet sprite_sheet_m44_spinning;

Animation_Definition *adef_m44_spinning;

Animation *anim_m44_spinning;

void init_map(Map *map);
Pickup *get_pickup_from_body(Body *body);

#endif