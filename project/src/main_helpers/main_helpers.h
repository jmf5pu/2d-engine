#ifndef MAIN_HELPERS_H
#define MAIN_HELPERS_H

#include "../player_helpers/player_structs.h"
#include "../structs.h"
#include <SDL2/SDL.h>
#include <linmath.h>
#include <stdbool.h>

#define CHARACTER_WEAPON_OFFSET 2

bool should_destroy_entity(Entity *entity, Map *map);
bool entity_is_player_or_crosshair(Entity *entity);
void render_player_anims(Player *player, SDL_Window *window, u32 texture_slots[32], vec4 color);
void destroy_all_marked_entities(Map *map);
void get_xy_components_from_vector(f32 magnitude, f32 angle, vec2 components_result);

#endif