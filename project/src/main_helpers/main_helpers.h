#ifndef MAIN_HELPERS_H
#define MAIN_HELPERS_H

#include "../structs.h"
#include "../player_helpers/player_structs.h"
#include <stdbool.h>
#include <linmath.h>
#include <SDL2/SDL.h>

bool should_destroy_entity(Entity *entity, Map *map);
bool entity_is_player_or_crosshair(Entity *entity);
void render_player_anims(Player * player, SDL_Window *window, u32 texture_slots[32], vec4 color);

#endif