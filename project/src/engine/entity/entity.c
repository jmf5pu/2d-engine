#include "../array_list.h"
#include "../entity.h"
#include "../physics.h"
#include "../animation.h"
#include "../util.h"

static Array_List *entity_list;

void entity_init(void)
{
    entity_list = array_list_create(sizeof(Entity), 0);
}

usize entity_create(vec2 position, vec2 size, vec2 velocity, u8 collision_layer, u8 collision_mask, On_Hit on_hit, On_Hit_Static on_hit_static)
{
    Entity entity = {
        .body_id = physics_body_create(position, size, velocity, collision_layer, collision_mask, on_hit, on_hit_static),
        .animation_id = (u64)-1, // largest usize value, indicates there is no animation associated
        .is_active = true,
    };

    return array_list_append(entity_list, &entity);
}

Entity *entity_get(usize id)
{
    return array_list_get(entity_list, id, "entity_get");
}

// decrements length of entity list, marks as inactive, then destroys body, animation, and self respectively
void entity_destroy(usize id)
{
    printf("deleting id %d\n", id);
    Entity *entity = entity_get(id);
    // entity->is_active = false;
    physics_body_destroy(entity->body_id);
    // animation_destroy(entity->animation_id); TODO: probably not needed
    array_list_remove(entity_list, id, "Destroying entity");
}

u64 entity_count()
{
    return entity_list->len;
}

usize entity_get_id(Entity *target_entity)
{
    printf("target_entity address: %p\n", target_entity);
    for (usize i = 0; i < entity_list->len; ++i)
    {
        printf("comparing address: %p\n", entity_get(i));
        if (entity_get(i) == target_entity)
        {
            return i;
        }
    }
    ERROR_RETURN(NULL, "Could not find the specified entity in the Array_List\n");
}