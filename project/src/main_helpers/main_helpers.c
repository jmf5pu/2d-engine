#include "main_helpers.h"
#include "../engine/render.h"
#include "../player_helpers/player_helpers.h"

/// @brief  indicates if the given entity should be destroyed. We destroy any entities that are inactive or have physics bodies that are inactive and aren't associated with
/// players, crosshairs, or pickups
/// @param entity
/// @param map
/// @return boolean representing if the entity should be destroyed on this frame
bool should_destroy_entity(Entity *entity, Map *map)
{
    bool is_player = SPLIT_SCREEN ? (entity == player_one->entity || entity == player_two->entity) : (entity == player_one->entity);

    bool is_pickup = false;
    for (int k = 0; k < map->num_pickups; k++) {
        if (entity == map->pickups[k].entity)
            is_pickup = true;
    }

    return (!entity->is_active || !entity->body->is_active) && !is_player && !is_pickup && !entity_is_player_or_crosshair(entity);
}

/// @brief Checks if an entity is a crosshair
/// @param entity
/// @return boolean representing if the entity is a crosshair
bool entity_is_player_or_crosshair(Entity *entity) { 
    bool is_player = SPLIT_SCREEN ? entity == player_one->entity || entity == player_two->entity : entity == player_one->entity;
    bool is_crosshair = SPLIT_SCREEN ? entity == player_one->crosshair || entity == player_two->crosshair : entity == player_one->crosshair; 
    return is_player || is_crosshair;
}

void render_player_anims(Player * player, SDL_Window *window, u32 texture_slots[32], vec4 color){
    // player is facing up, render weapon "under" player
    if(player->crosshair_angle > M_PI / 4 && player->crosshair_angle < 3 * M_PI / 4){
        animation_render(player->weapon->character_anim, window, player->entity->body->aabb.position, 0, color, texture_slots);
        animation_render(player->entity->animation, window, player->entity->body->aabb.position, 0, color, texture_slots);
    }
    else{
        animation_render(player->entity->animation, window, player->entity->body->aabb.position, 0, color, texture_slots);
        animation_render(player->weapon->character_anim, window, player->entity->body->aabb.position, 0, color, texture_slots);
    }
}