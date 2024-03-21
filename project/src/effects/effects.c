#include "effects.h"
#include "../engine/hash_map.h"
#include "../player_helpers/player_helpers.h"

#define PLAYER_HEIGHT 22 // TODO: put this somewhere else
#define GRAVITY_VELOCITY -7

static Hash_Map *explosion_adef_map;

void init_effects(void)
{
    init_brass_animation_definitions();
    init_explosion_animation_definitions();
    init_explosion_adef_hashmap();
}

void create_muzzle_flash_entity(f32 angle, vec2 position, vec2 size, u8 collision_layer, u8 collision_mask, On_Hit on_hit, On_Hit_Static on_hit_static)
{
    Entity *entity = entity_create(position, size, (vec2){0, 0}, collision_layer, collision_mask, on_hit, on_hit_static);

    char *adef_key = calloc(50, sizeof(char));
    strcat(adef_key, "muzzle_flash_1_");

    char *direction = calloc(5, sizeof(char));

    get_direction_from_angle(angle, direction);

    strcat(adef_key, direction);
    strcat(adef_key, "\0");
    free(direction);

    Animation_Definition *adef = get(explosion_adef_map, adef_key);
    free(adef_key);

    entity->animation = animation_create(adef, false);
    entity->destroy_on_anim_completion = true;
}

void create_brass_entity(vec2 position, Animation_Definition *adef, i32 z_index)
{
    Entity *entity = entity_create(position, (vec2){3, 3}, (vec2){0, 0}, 0, 0, NULL, NULL);
    entity->animation = animation_create(adef, true);
    entity->animation->z_index = z_index;
    entity->movement_script = brass_movement;
}

void brass_movement(Entity *entity)
{
    const brass_bounce_distance = 10;

    entity->body->acceleration[1] = -25;

    if (entity->body->aabb.position[1] < entity->starting_position[1] - 0.6 * PLAYER_HEIGHT) {
        bool bounce_left = get_random_int_in_range(0, 1);
        entity->body->velocity[0] = bounce_left ? 100 : -100;
        entity->body->velocity[1] = 100;
    }

    if (entity->body->aabb.position[0] > entity->starting_position[0] + brass_bounce_distance ||
        entity->body->aabb.position[0] < entity->starting_position[0] - brass_bounce_distance) {
        entity->is_active = false; // entity will be destroyed next frame
    }
}

void init_explosion_animation_definitions(void)
{
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_0, "assets/wip/muzzle_flash_v3_0.png", 19, 19);
    adef_muzzle_flash_0 =
        animation_definition_create(&sprite_sheet_muzzle_flash_0, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_1, "assets/wip/muzzle_flash_v3_1.png", 19, 19);
    adef_muzzle_flash_1 =
        animation_definition_create(&sprite_sheet_muzzle_flash_1, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2, "assets/wip/muzzle_flash_v3_2.png", 19, 19);
    adef_muzzle_flash_2 =
        animation_definition_create(&sprite_sheet_muzzle_flash_2, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_3, "assets/wip/muzzle_flash_v3_3.png", 19, 19);
    adef_muzzle_flash_3 =
        animation_definition_create(&sprite_sheet_muzzle_flash_3, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_4, "assets/wip/muzzle_flash_v3_4.png", 19, 19);
    adef_muzzle_flash_4 =
        animation_definition_create(&sprite_sheet_muzzle_flash_4, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_5, "assets/wip/muzzle_flash_v3_5.png", 19, 19);
    adef_muzzle_flash_5 =
        animation_definition_create(&sprite_sheet_muzzle_flash_5, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_6, "assets/wip/muzzle_flash_v3_6.png", 19, 19);
    adef_muzzle_flash_6 =
        animation_definition_create(&sprite_sheet_muzzle_flash_6, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_7, "assets/wip/muzzle_flash_v3_7.png", 19, 19);
    adef_muzzle_flash_7 =
        animation_definition_create(&sprite_sheet_muzzle_flash_7, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_8, "assets/wip/muzzle_flash_v3_8.png", 19, 19);
    adef_muzzle_flash_8 =
        animation_definition_create(&sprite_sheet_muzzle_flash_8, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_9, "assets/wip/muzzle_flash_v3_9.png", 19, 19);
    adef_muzzle_flash_9 =
        animation_definition_create(&sprite_sheet_muzzle_flash_9, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_10, "assets/wip/muzzle_flash_v3_10.png", 19, 19);
    adef_muzzle_flash_10 =
        animation_definition_create(&sprite_sheet_muzzle_flash_10, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_11, "assets/wip/muzzle_flash_v3_11.png", 19, 19);
    adef_muzzle_flash_11 =
        animation_definition_create(&sprite_sheet_muzzle_flash_11, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_12, "assets/wip/muzzle_flash_v3_12.png", 19, 19);
    adef_muzzle_flash_12 =
        animation_definition_create(&sprite_sheet_muzzle_flash_12, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_13, "assets/wip/muzzle_flash_v3_13.png", 19, 19);
    adef_muzzle_flash_13 =
        animation_definition_create(&sprite_sheet_muzzle_flash_13, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_14, "assets/wip/muzzle_flash_v3_14.png", 19, 19);
    adef_muzzle_flash_14 =
        animation_definition_create(&sprite_sheet_muzzle_flash_14, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_15, "assets/wip/muzzle_flash_v3_15.png", 19, 19);
    adef_muzzle_flash_15 =
        animation_definition_create(&sprite_sheet_muzzle_flash_15, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
}

void init_explosion_adef_hashmap(void)
{
    explosion_adef_map = create_hash_map(EXPLOSION_COUNT * ANGLES);

    insert(explosion_adef_map, "muzzle_flash_1_0", adef_muzzle_flash_0);
    insert(explosion_adef_map, "muzzle_flash_1_1", adef_muzzle_flash_1);
    insert(explosion_adef_map, "muzzle_flash_1_2", adef_muzzle_flash_2);
    insert(explosion_adef_map, "muzzle_flash_1_3", adef_muzzle_flash_3);
    insert(explosion_adef_map, "muzzle_flash_1_4", adef_muzzle_flash_4);
    insert(explosion_adef_map, "muzzle_flash_1_5", adef_muzzle_flash_5);
    insert(explosion_adef_map, "muzzle_flash_1_6", adef_muzzle_flash_6);
    insert(explosion_adef_map, "muzzle_flash_1_7", adef_muzzle_flash_7);
    insert(explosion_adef_map, "muzzle_flash_1_8", adef_muzzle_flash_8);
    insert(explosion_adef_map, "muzzle_flash_1_9", adef_muzzle_flash_9);
    insert(explosion_adef_map, "muzzle_flash_1_10", adef_muzzle_flash_10);
    insert(explosion_adef_map, "muzzle_flash_1_11", adef_muzzle_flash_11);
    insert(explosion_adef_map, "muzzle_flash_1_12", adef_muzzle_flash_12);
    insert(explosion_adef_map, "muzzle_flash_1_13", adef_muzzle_flash_13);
    insert(explosion_adef_map, "muzzle_flash_1_14", adef_muzzle_flash_14);
    insert(explosion_adef_map, "muzzle_flash_1_15", adef_muzzle_flash_15);
}

void init_brass_animation_definitions(void)
{
    render_sprite_sheet_init(&sprite_sheet_brass_falling_1, "assets/wip/brass_falling_1.png", 3, 3);
    adef_brass_falling_1 = animation_definition_create(&sprite_sheet_brass_falling_1, (f32[]){0.06, 0.06, 0.06, 0.06}, (u8[]){0, 0, 0, 0}, (u8[]){0, 1, 2, 3}, 4);
}