#include "effects.h"

#define PLAYER_HEIGHT 22 // TODO: put this somewhere else
#define GRAVITY_VELOCITY -7

void init_effect_adefs(void)
{
    render_sprite_sheet_init(&sprite_sheet_brass_falling_1, "assets/wip/brass_falling_1.png", 3, 3);
    adef_brass_falling_1 = animation_definition_create(&sprite_sheet_brass_falling_1, (f32[]){0.06, 0.06, 0.06, 0.06}, (u8[]){0, 0, 0, 0}, (u8[]){0, 1, 2, 3}, 4);
}

void init_effects(void) { init_effect_adefs(); }

void create_brass_entity(vec2 position, Animation_Definition *adef)
{
    Entity *entity = entity_create(position, (vec2){3, 3}, (vec2){0, 0}, 0, 0, NULL, NULL);
    entity->animation = animation_create(adef, true);
    entity->movement_script = brass_movement;
}

void brass_movement(Entity *entity)
{
    const brass_bounce_distance = 10;
    entity->body->acceleration[1] = -25;
    if (entity->body->aabb.position[1] < entity->starting_position[1] - PLAYER_HEIGHT) {
        bool bounce_left = get_random_int_in_range(0, 1);
        entity->body->velocity[0] = bounce_left ? 100 : -100;
        entity->body->velocity[1] = 100;
    }
    if (entity->body->aabb.position[0] > entity->starting_position[0] + brass_bounce_distance ||
        entity->body->aabb.position[0] < entity->starting_position[0] - brass_bounce_distance) {
        entity->is_active = false; // entity will be destroyed next frame
    }
}