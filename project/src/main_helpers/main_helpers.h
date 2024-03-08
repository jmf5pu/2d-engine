#ifndef MAIN_HELPERS_H
#define MAIN_HELPERS_H

#include "../structs.h"
#include <stdbool.h>

bool should_destroy_entity(Entity *entity, Map *map);
bool entity_is_player_or_crosshair(Entity *entity);

#endif