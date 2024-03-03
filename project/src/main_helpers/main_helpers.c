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

    return (!entity->is_active || !entity->body->is_active) && !is_player && !is_pickup && !entity_is_crosshair(entity);
}

/// @brief Checks if an entity is a crosshair
/// @param entity
/// @return boolean representing if the entity is a crosshair
bool entity_is_crosshair(Entity *entity) { return SPLIT_SCREEN ? (entity == player_one->crosshair || entity == player_two->crosshair) : (entity == player_one->crosshair); }