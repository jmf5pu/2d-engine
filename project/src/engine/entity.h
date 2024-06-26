#ifndef ENTITY_H
#define ENTITY_H

#include "animation.h"
#include "physics.h"
#include "types.h"
#include <linmath.h>
#include <stdbool.h>

struct entity;

typedef void (*MovementScript)(struct entity *entity);
typedef struct entity {
    Body *body;
    Animation *animation;
    bool is_active;
    bool destroy_on_anim_completion;
    MovementScript movement_script;
    vec2 starting_position;
} Entity;

void entity_init(void);
Entity *entity_create(vec2 position, vec2 size, vec2 velocity, u8 collision_layer, u8 collision_mask, On_Hit on_hit, On_Hit_Static on_hit_static);
Entity *entity_get(usize id);
void entity_destroy(Entity *entity);
usize entity_count(void);
void free_all_entities_and_clear_array_list(void);

#endif