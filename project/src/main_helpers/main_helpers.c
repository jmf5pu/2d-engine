#include "main_helpers.h"
#include "../engine/animation.h"
#include "../engine/render.h"
#include "../engine/util.h"
#include "../player_helpers/player_helpers.h"
#include <stdlib.h>

extern bool should_quit;

/// @brief Polls for new SDL_Events and updates corresponding player input states. Called once per frame
/// @param
void poll_sdl_events_and_update_input_states(void)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            should_quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            // player one always takes priority for mouse/keyboard inputs
            if (player_one && player_one->input_state->controller_input_state->controller_id == -1)
                update_player_input_state_via_mouse_clicks(player_one, &event);
            else if (player_two && player_two->input_state->controller_input_state->controller_id == -1)
                update_player_input_state_via_mouse_clicks(player_two, &event);
        case SDL_JOYBUTTONDOWN:
        case SDL_JOYBUTTONUP:
            if (player_one && event.cbutton.which == player_one->input_state->controller_input_state->controller_id)
                update_player_input_state_via_controller(player_one, &event);
            if (player_two && event.cbutton.which == player_two->input_state->controller_input_state->controller_id)
                update_player_input_state_via_controller(player_two, &event);
            break;
        default:
            break;
        }
    }
}

/// @brief  indicates if the given entity should be destroyed. We destroy any entities that are inactive or have physics bodies that are inactive and aren't associated with
/// players, crosshairs, or pickups. Also, if the entity is marked to be destroyed on animation completion, check if the anim is completed and destroy if so.
/// @param entity
/// @param map
/// @return boolean representing if the entity should be destroyed on this frame
bool should_destroy_entity(Entity *entity, Map *map)
{
    bool anim_requesting_destroy = entity->destroy_on_anim_completion && entity->animation->current_frame_index == entity->animation->animation_definition->frame_count - 1;
    bool is_pickup = false;
    for (int i = 0; i < map->num_dynamic_props; i++) {
        if (entity == map->dynamic_props[i]->entity) {
            is_pickup = true;
            break;
        }
    }
    bool is_inactive = !entity->is_active || !entity->body->is_active;
    return (anim_requesting_destroy || is_inactive) && !is_pickup && !entity_is_player_interact_bar_or_crosshair(entity);
}

/// @brief Checks if an entity is a crosshair
/// @param entity
/// @return boolean representing if the entity is a crosshair
bool entity_is_player_interact_bar_or_crosshair(Entity *entity)
{
    bool is_player = SPLIT_SCREEN ? entity == player_one->entity || entity == player_two->entity : entity == player_one->entity;
    bool is_crosshair = SPLIT_SCREEN ? entity == player_one->crosshair || entity == player_two->crosshair : entity == player_one->crosshair;
    bool is_interact_bar = SPLIT_SCREEN ? (entity == player_one->interact_bar || entity == player_two->interact_bar) : entity == player_one->interact_bar;
    return is_player || is_crosshair || is_interact_bar;
}

void render_all_non_player_entities_with_animations(SDL_Window *window, u32 texture_slots[BATCH_SIZE], vec4 color)
{
    for (int j = (int)entity_count() - 1; j >= 0; --j) {
        Entity *entity = entity_get(j);

        // skip inactive entities, entities that are players or crosshairs or entities with no animation
        if (!entity->animation || !entity->is_active || !entity->body->is_active || entity_is_player_interact_bar_or_crosshair(entity)) {
            continue;
        }

        // render the entity's animation
        animation_render(entity->animation, window, entity->body->aabb.position, color, texture_slots);
    }
}

/// @brief check all entities and destroy entities that need to be destroyed. Called each tick/frame
/// @param map
void destroy_all_marked_entities(Map *map)
{
    for (int i = (int)entity_count() - 1; i >= 0; --i) {
        Entity *entity = entity_get(i);
        if (should_destroy_entity(entity, map))
            entity_destroy(entity);
    }
}

/// @brief For all entities with a pre-defined movement script, run it. Called each tick/frame
/// @param
void update_entity_movements(void)
{
    for (int i = 0; i < entity_count(); i++) {
        Entity *entity = entity_get(i);
        if (entity->movement_script)
            entity->movement_script(entity);
    }
}

/// @brief get the x and y components of a "vector" (magnitude + angle). result is stored in the last parameter
/// @param magnitude
/// @param angle
/// @param components_result
void get_xy_components_from_vector(f32 magnitude, f32 angle, vec2 components_result)
{
    components_result[0] = magnitude * cos(angle);
    components_result[1] = magnitude * sin(angle);
}

/// @brief returns a random int within the provided range (inclusive)
/// @param min
/// @param max
/// @return random int
int get_random_int_in_range(int min, int max) { return min + rand() % (max - min + 1); }

/// @brief renders all physics bodies (both static + nonstatic)
/// @param
void render_physics_bodies(void)
{
    Array_List *non_static_bodies = get_all_bodies();
    for (int j = 0; j < non_static_bodies->len; j++) {
        Body *body = array_list_get(non_static_bodies, j);
        render_aabb(&body->aabb, WHITE);
    }

    Array_List *static_bodies = get_all_static_bodies();
    for (int j = 0; j < static_bodies->len; j++) {
        Body *static_body = array_list_get(static_bodies, j);
        render_aabb(&static_body->aabb, RED);
    }
}

/// @brief checks if the contents of 2 vec4's are equal
/// @param first
/// @param second
/// @return
bool vec4_is_equal(vec4 first, vec4 second) { return first[0] == second[0] && first[1] == second[1] && first[2] == second[2] && first[3] == second[3]; }

// returns TRUE if the first RGB value is less than the second for each value in
// RGB, otherwise returns false

/// @brief Returns true if the first RGB value is less than the second for each value in RGB, otherwise returns false
/// @param first
/// @param second
/// @return
bool vec4_color_cmp(vec4 first, vec4 second) { return first[0] < second[0] && first[1] < second[1] && first[2] < second[2]; }