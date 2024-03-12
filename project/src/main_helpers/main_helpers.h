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
void get_character_weapon_position(Player *player, vec2 *weapon_position);
void create_muzzle_flash_entity(vec2 position, vec2 size, u8 collision_layer, u8 collision_mask, On_Hit on_hit, On_Hit_Static on_hit_static);
void destroy_all_marked_entities(Map *map);

#endif