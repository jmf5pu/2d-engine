#ifndef MAP_HELPERS_H
#define MAP_HELPERS_H

#include "engine/render.h"
#include "structs.h"

// pickup sprites & anims
Sprite_Sheet sprite_sheet_m44_spinning;

Animation_Definition *adef_m44_spinning;

Animation *anim_m44_spinning;

void init_map(Map *map);

#endif