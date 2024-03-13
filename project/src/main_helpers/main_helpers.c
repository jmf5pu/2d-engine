#include "main_helpers.h"
#include "../engine/animation.h"
#include "../engine/render.h"
#include "../player_helpers/player_helpers.h"

/// @brief  indicates if the given entity should be destroyed. We destroy any entities that are inactive or have physics bodies that are inactive and aren't associated with
/// players, crosshairs, or pickups. Also, if the entity is marked to be destroyed on animation completion, check if the anim is completed and destroy if so.
/// @param entity
/// @param map
/// @return boolean representing if the entity should be destroyed on this frame
bool should_destroy_entity(Entity *entity, Map *map)
{
    bool anim_requesting_destroy = entity->destroy_on_anim_completion && entity->animation->current_frame_index == entity->animation->animation_definition->frame_count - 1;
    bool is_player = SPLIT_SCREEN ? (entity == player_one->entity || entity == player_two->entity) : (entity == player_one->entity);
    bool is_pickup = false;

    for (int k = 0; k < map->num_pickups; k++) {
        if (entity == map->pickups[k].entity)
            is_pickup = true;
    }

    return (anim_requesting_destroy || !entity->is_active || !entity->body->is_active) && !is_player && !is_pickup && !entity_is_player_or_crosshair(entity);
}

/// @brief Checks if an entity is a crosshair
/// @param entity
/// @return boolean representing if the entity is a crosshair
bool entity_is_player_or_crosshair(Entity *entity)
{
    bool is_player = SPLIT_SCREEN ? entity == player_one->entity || entity == player_two->entity : entity == player_one->entity;
    bool is_crosshair = SPLIT_SCREEN ? entity == player_one->crosshair || entity == player_two->crosshair : entity == player_one->crosshair;
    return is_player || is_crosshair;
}

/// @brief Renders the player and player weapon animations. Called each frame. Rendering order depends on the player's direction (crosshair_angle)
/// @param player active player
/// @param window
/// @param texture_slots
/// @param color
void render_player_anims(Player *player, SDL_Window *window, u32 texture_slots[32], vec4 color)
{
    vec2 weapon_position = {0, 0};
    get_character_weapon_position(player, weapon_position);

    if (player) {
        // player is facing up, render weapon "under" player
        if (player->crosshair_angle > M_PI / 4 && player->crosshair_angle < 3 * M_PI / 4) {
            animation_render(player->weapon->character_anim, window, weapon_position, 0, color, texture_slots);
            animation_render(player->entity->animation, window, player->entity->body->aabb.position, 0, color, texture_slots);
        }
        else {
            animation_render(player->entity->animation, window, player->entity->body->aabb.position, 0, color, texture_slots);
            animation_render(player->weapon->character_anim, window, weapon_position, 0, color, texture_slots);
        }
    }
    else
        printf("player must be defined to update corresponding anims");
}

/// @brief Calculates the weapon sprite's position using the player's crosshair angle
/// @param player
/// @param weapon_position
void get_character_weapon_position(Player *player, vec2 weapon_position)
{
    vec2_dup(weapon_position, player->entity->body->aabb.position);
    vec2 offset = {0, 0};
    get_xy_components_from_vector(CHARACTER_WEAPON_OFFSET, player->crosshair_angle, offset);
    vec2_add(weapon_position, weapon_position, offset);
}

/// @brief check all entities and destroy entities that need to be destroyed. Called each tick
/// @param map
void destroy_all_marked_entities(Map *map)
{
    for (int i = (int)entity_count() - 1; i >= 0; --i) {
        Entity *entity = entity_get(i);
        if (should_destroy_entity(entity, map))
            entity_destroy(entity);
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