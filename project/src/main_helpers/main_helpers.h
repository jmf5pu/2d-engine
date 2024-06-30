#ifndef MAIN_HELPERS_H
#define MAIN_HELPERS_H

#include "../map_helpers/map_helpers.h"
#include "../structs.h"
#include <SDL2/SDL.h>
#include <linmath.h>
#include <stdbool.h>

void poll_sdl_events_and_update_input_states(void);
bool should_destroy_entity(Entity *entity, Map *map);
bool entity_is_player_interact_bar_or_crosshair(Entity *entity);
void render_all_non_player_entities_with_animations(SDL_Window *window, u32 texture_slots[BATCH_SIZE], vec4 color);
void destroy_all_marked_entities(Map *map);
void get_xy_components_from_vector(f32 magnitude, f32 angle, vec2 components_result);
void render_physics_bodies(void);
bool vec4_is_equal(vec4 first, vec4 second);
bool vec4_color_cmp(vec4 first, vec4 second);
int get_random_int_in_range(int min, int max);

#endif