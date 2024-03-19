#include "../engine/animation.h"
#include "../engine/entity.h"
#include "../engine/render.h"

Sprite_Sheet sprite_sheet_brass_falling_1;
Animation_Definition *adef_brass_falling_1;

void create_brass_entity(vec2 position, Animation_Definition *adef);
void brass_movement(Entity *entity);