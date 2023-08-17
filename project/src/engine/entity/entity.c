#include "../array_list.h"
#include "../entity.h"
#include "../physics.h"
#include "../animation.h"
#include "../util.h"

static Array_List *entity_list;

void entity_init(void)
{
    entity_list = array_list_create(sizeof(struct Entity *), 0);
}

Entity *entity_create(vec2 position, vec2 size, vec2 velocity, u8 collision_layer, u8 collision_mask, On_Hit on_hit, On_Hit_Static on_hit_static)
{
    Entity *entity = (Entity *)malloc(sizeof(Entity)); // Allocate memory for Entity

    if (entity == NULL)
    {
        // Handle memory allocation error
        ERROR_EXIT("Memory allocation failed\n");
    }
    entity->body = physics_body_create(position, size, velocity, collision_layer, collision_mask, on_hit, on_hit_static);
    printf("created physics body %p\n", entity->body);
    entity->animation_id = (usize)-1;
    entity->is_active = true;

    printf("address created %p\n", entity);

    if (array_list_append(entity_list, entity) == (usize)-1)
    {
        free(entity); // Clean up allocated memory in case of failure
        ERROR_EXIT("Could not append body to list\n");
    }
    printf("address returned %p\n", entity);

    return entity;
}

Entity *entity_get(usize id)
{
    return array_list_get(entity_list, id, "entity_get");
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
    ERROR_RETURN((usize)-1, "Could not find the specified entity in the Array_List\n");
}

// decrements length of entity list, marks as inactive, then destroys body, animation, and self respectively
void entity_destroy(Entity *entity)
{
    usize id = entity_get_id(entity);
    entity->body->is_active = false; // physics bodies for inactive entities should be inactive
    entity->is_active = false;       // probably not even necessary, remove later
    // physics_body_destroy(entity->body_id);
    // animation_destroy(entity->animation_id); TODO: probably not needed
    array_list_remove(entity_list, id, "Destroying entity");
}

usize entity_count()
{
    return entity_list->len;
}