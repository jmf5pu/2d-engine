#include "../array_list.h"
#include "../entity.h"
#include "../physics.h"
#include "../animation.h"

static Array_List *entity_list;

void entity_init(void)
{
    entity_list = array_list_create(sizeof(Entity), 0);
}

usize entity_create(vec2 position, vec2 size, vec2 velocity, u8 collision_layer, u8 collision_mask, On_Hit on_hit, On_Hit_Static on_hit_static)
{
    Entity entity = {
        .body_id = physics_body_create(position, size, velocity, collision_layer, collision_mask, on_hit, on_hit_static),
        .animation_id = (usize)-1, // largest usize value, indicates there is no animation associated
        .is_active = true,
    };

    return array_list_append(entity_list, &entity);
}

Entity *entity_get(usize id)
{
    return array_list_get(entity_list, id);
}

// decrements length of entity list, marks as inactive, then destroys body, animation, and self respectively
void entity_destroy(usize id)
{
    Entity *entity = entity_get(id);
    entity->is_active = false;
    physics_body_destroy(entity->body_id);
    animation_destroy(entity->animation_id);
    array_list_remove(entity_list, id, "Destroying entity");
}

usize entity_count()
{
    return entity_list->len;
}