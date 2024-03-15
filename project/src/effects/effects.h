#include "../animation.h"
#include "../engine/entity.h"
#include "../render.h"

typedef void (*UpdateEntityVelocity)(Entity *entity);

Sprite_Sheet sprite_sheet_brass_falling_1;
Animation_Definition *adef_brass_falling_1;

typedef struct entity_with_movement {
    Entity *entity;
    UpdateEntityVelocity *update_entity_velocity;
} Entity_With_Movement;