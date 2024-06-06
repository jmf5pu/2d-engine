#include "effects.h"
#include "../engine/hash_map.h"
#include "../engine/util.h"
#include "../player_helpers/player_helpers.h"

#define GRAVITY_VELOCITY -7

static Hash_Map *explosion_adef_map;

const u8 BULLET_IMPACT_DIMENSIONS[] = {7, 7};

// extern variables from main
u32 texture_slots[BATCH_SIZE];
vec4 game_color;
SDL_Window *window;

void init_effects(void)
{
    init_brass_animation_definitions();
    init_bullet_impact_animation_definitions();
    init_explosion_animation_definitions();
    init_explosion_adef_hashmap();
    init_character_shadow_anim();
}

void create_muzzle_flash_entity(f32 angle, vec2 position, vec2 size, vec2 velocity, u8 collision_layer, u8 collision_mask, On_Hit on_hit, On_Hit_Static on_hit_static)
{
    Entity *entity = entity_create(position, size, velocity, collision_layer, collision_mask, on_hit, on_hit_static);

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

void create_bullet_impact_entity(vec2 position, Animation_Definition *adef)
{
    Entity *entity = entity_create(position, (vec2){BULLET_IMPACT_DIMENSIONS[0], BULLET_IMPACT_DIMENSIONS[1]}, (vec2){0, 0}, 0, 0, NULL, NULL);
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
    const f32 brass_bounce_distance = 10;
    const f32 bounce_x_magnitude = 100;
    const f32 bounce_y_magnitude = 100;

    entity->body->acceleration[1] = -25;

    if (entity->body->aabb.position[1] < entity->starting_position[1] - 0.6 * PLAYER_HEIGHT) {
        bool bounce_left = get_random_int_in_range(0, 1);
        entity->body->velocity[0] = bounce_left ? bounce_x_magnitude : -1 * bounce_x_magnitude;
        entity->body->velocity[1] = bounce_y_magnitude;
    }

    if (entity->body->aabb.position[0] > entity->starting_position[0] + brass_bounce_distance ||
        entity->body->aabb.position[0] < entity->starting_position[0] - brass_bounce_distance) {
        entity->is_active = false; // entity will be destroyed next frame
    }
}

void render_character_shadow(vec2 character_position, f32 character_sprite_height)
{
    vec2 shadow_position = {0, 0};
    vec2_add(shadow_position, character_position, (vec2){0, -0.5 * character_sprite_height});
    anim_character_shadow->z_index = 100;
    animation_render(anim_character_shadow, window, shadow_position, WHITE, texture_slots);
}

void init_bullet_impact_animation_definitions(void)
{
    render_sprite_sheet_init(&sprite_sheet_bullet_impact_0, "assets/wip/bullet_impact_0.png", BULLET_IMPACT_DIMENSIONS[0], BULLET_IMPACT_DIMENSIONS[1]);
    adef_bullet_impact_0 =
        animation_definition_create(&sprite_sheet_bullet_impact_0, (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
}

void init_explosion_animation_definitions(void)
{
    const u8 MUZZLE_FLASH_DIMENSIONS[] = {19, 19};
    const f32 MUZZLE_FLASH_DURATIONS[] = {0.005, 0.005, 0.005, 0.01, 0.01, 0.01};
    const u8 MUZZLE_FLASH_ROWS[] = {0, 0, 0, 0, 0, 0};
    const u8 MUZZLE_FLASH_COLS[] = {0, 1, 2, 3, 4, 5};

    u8 muzzle_flash_frame_count = ARRAY_LENGTH(MUZZLE_FLASH_COLS);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_0, "assets/wip/muzzle_flash_v3_0.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_0 =
        animation_definition_create(&sprite_sheet_muzzle_flash_0, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_1, "assets/wip/muzzle_flash_v3_1.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_1 =
        animation_definition_create(&sprite_sheet_muzzle_flash_1, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2, "assets/wip/muzzle_flash_v3_2.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_2 =
        animation_definition_create(&sprite_sheet_muzzle_flash_2, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_3, "assets/wip/muzzle_flash_v3_3.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_3 =
        animation_definition_create(&sprite_sheet_muzzle_flash_3, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_4, "assets/wip/muzzle_flash_v3_4.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_4 =
        animation_definition_create(&sprite_sheet_muzzle_flash_4, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_5, "assets/wip/muzzle_flash_v3_5.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_5 =
        animation_definition_create(&sprite_sheet_muzzle_flash_5, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_6, "assets/wip/muzzle_flash_v3_6.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_6 =
        animation_definition_create(&sprite_sheet_muzzle_flash_6, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_7, "assets/wip/muzzle_flash_v3_7.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_7 =
        animation_definition_create(&sprite_sheet_muzzle_flash_7, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_8, "assets/wip/muzzle_flash_v3_8.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_8 =
        animation_definition_create(&sprite_sheet_muzzle_flash_8, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_9, "assets/wip/muzzle_flash_v3_9.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_9 =
        animation_definition_create(&sprite_sheet_muzzle_flash_9, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_10, "assets/wip/muzzle_flash_v3_10.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_10 =
        animation_definition_create(&sprite_sheet_muzzle_flash_10, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_11, "assets/wip/muzzle_flash_v3_11.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_11 =
        animation_definition_create(&sprite_sheet_muzzle_flash_11, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_12, "assets/wip/muzzle_flash_v3_12.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_12 =
        animation_definition_create(&sprite_sheet_muzzle_flash_12, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_13, "assets/wip/muzzle_flash_v3_13.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_13 =
        animation_definition_create(&sprite_sheet_muzzle_flash_13, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_14, "assets/wip/muzzle_flash_v3_14.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_14 =
        animation_definition_create(&sprite_sheet_muzzle_flash_14, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_15, "assets/wip/muzzle_flash_v3_15.png", MUZZLE_FLASH_DIMENSIONS[0], MUZZLE_FLASH_DIMENSIONS[1]);
    adef_muzzle_flash_15 =
        animation_definition_create(&sprite_sheet_muzzle_flash_15, (f32 *)MUZZLE_FLASH_DURATIONS, (u8 *)MUZZLE_FLASH_ROWS, (u8 *)MUZZLE_FLASH_COLS, muzzle_flash_frame_count);
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

void init_character_shadow_anim(void)
{
    render_sprite_sheet_init(&sprite_sheet_character_shadow, "assets/wip/character_shadow.png", 16, 5);
    adef_character_shadow = animation_definition_create(&sprite_sheet_character_shadow, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_character_shadow = animation_create(adef_character_shadow, false);
}