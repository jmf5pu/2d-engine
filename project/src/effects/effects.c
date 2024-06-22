#include "effects.h"
#include "../engine/hash_map.h"
#include "../engine/util.h"
#include "../main_helpers/main_helpers.h"
#include "../player_helpers/player_helpers.h"

#define GRAVITY_VELOCITY -7

static Hash_Map *explosion_adef_map;
static Hash_Map *blood_splatter_adef_map;

const u8 BULLET_IMPACT_DIMENSIONS_SMALL[] = {5, 5};
const u8 BULLET_IMPACT_DIMENSIONS_MEDIUM[] = {7, 7};

// extern variables from main
u32 texture_slots[BATCH_SIZE];
vec4 game_color;
SDL_Window *window;

void init_effects(void)
{
    // init animations and animation definitions
    init_brass_animation_definitions();
    init_bullet_animation_definitions();
    init_explosion_animation_definitions();
    init_blood_splatter_animation_definitions();
    init_character_shadow_anim();

    // init hashmaps
    init_explosion_adef_hashmap();
    init_blood_splatter_adef_hashmap();
}

void create_muzzle_flash_entity(
    char *muzzle_flash_id, f32 angle, vec2 position, vec2 size, vec2 velocity, u8 collision_layer, u8 collision_mask, On_Hit on_hit, On_Hit_Static on_hit_static)
{
    Entity *entity = entity_create(position, size, velocity, collision_layer, collision_mask, on_hit, on_hit_static);

    char *adef_key = calloc(50, sizeof(char));
    strcat(adef_key, "muzzle_flash_");
    strcat(adef_key, muzzle_flash_id);
    strcat(adef_key, "_");

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

void create_player_muzzle_flash_effect(Player *player)
{
    vec2 muzzle_flash_position = {0, 0};
    vec2 muzzle_flash_offset = {0, 0};
    get_xy_components_from_vector(MUZZLE_FLASH_DISTANCE_FROM_PLAYER, player->crosshair_angle, muzzle_flash_offset);
    vec2_add(muzzle_flash_offset, muzzle_flash_offset, (vec2){0, CHARACTER_ARMS_Y_OFFSET_FROM_CENTER});
    vec2_add(muzzle_flash_position, player->relative_position, muzzle_flash_offset);
    create_muzzle_flash_entity(
        player->weapon->weapon_type->muzzle_flash_id, player->crosshair_angle, muzzle_flash_position, (vec2){15, 15}, player->entity->body->velocity, 0, 0, NULL, NULL);
}
void create_bullet_impact_entity(vec2 position, Animation_Definition *adef)
{
    Entity *entity = entity_create(position, (vec2){BULLET_IMPACT_DIMENSIONS_MEDIUM[0], BULLET_IMPACT_DIMENSIONS_MEDIUM[1]}, (vec2){0, 0}, 0, 0, NULL, NULL);
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

/// @brief helper to get the z_index of brass entities based on player direction. If the player is facing up, we want to render the brass underneath the player sprite
/// @param angle player to crosshair angle
/// @return z index for the brass entity (1 or -1)
static i32 get_player_brass_z_index(f32 angle)
{
    bool player_facing_up = angle > M_PI / 4 && angle < 3 * M_PI / 4;
    return player_facing_up ? -1 : 1;
}

void create_player_brass_effect(Player *player, Animation_Definition *brass_adef)
{
    vec2 brass_position = {0, 0};
    vec2_dup(brass_position, player->relative_position);
    vec2 brass_offset = {0, 0};
    get_xy_components_from_vector(BRASS_EJECT_DISTANCE_FROM_PLAYER, player->crosshair_angle, brass_offset);
    vec2_add(brass_position, brass_position, brass_offset);
    vec2_add(brass_position, brass_position, (vec2){0, CHARACTER_ARMS_Y_OFFSET_FROM_CENTER});

    create_brass_entity(brass_position, brass_adef, get_player_brass_z_index(player->crosshair_angle));
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

/// @brief Get a blood splatter adef by randomly selecting one that matches the provided prefix
/// @param adef_prefix
/// @return
Animation_Definition *get_blood_splatter_adef(char *adef_prefix)
{
    char *adef_key = calloc(50, sizeof(char));
    strcat(adef_key, "blood_splatter_");
    int rand_int = get_random_int_in_range(1, BLOOD_SPLATTER_COUNT);
    char rand_int_str[4]; // capped at 999
    sprintf(rand_int_str, "%d", rand_int);
    strcat(adef_key, rand_int_str);
    strcat(adef_key, "\0");
    Animation_Definition *adef = get(blood_splatter_adef_map, adef_key);
    free(adef_key);
    return adef;
}

void init_bullet_animation_definitions(void)
{
    render_sprite_sheet_init(&sprite_sheet_bullet_small, "assets/wip/bullet_small.png", 2, 2);
    adef_bullet_small = animation_definition_create(&sprite_sheet_bullet_small, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_bullet_medium, "assets/wip/bullet_medium.png", 4, 4);
    adef_bullet_medium = animation_definition_create(&sprite_sheet_bullet_medium, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_bullet_impact_small, "assets/wip/bullet_impact_small.png", BULLET_IMPACT_DIMENSIONS_SMALL[0], BULLET_IMPACT_DIMENSIONS_SMALL[1]);
    adef_bullet_impact_small =
        animation_definition_create(&sprite_sheet_bullet_impact_small, (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
    render_sprite_sheet_init(&sprite_sheet_bullet_impact_medium, "assets/wip/bullet_impact_medium.png", BULLET_IMPACT_DIMENSIONS_MEDIUM[0], BULLET_IMPACT_DIMENSIONS_MEDIUM[1]);
    adef_bullet_impact_medium =
        animation_definition_create(&sprite_sheet_bullet_impact_medium, (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
}

void init_explosion_animation_definitions(void)
{
    const u8 MUZZLE_FLASH_1_DIMENSIONS[] = {19, 19};
    const f32 MUZZLE_FLASH_1_DURATIONS[] = {0.005, 0.005, 0.005, 0.005, 0.01, 0.01};
    const u8 MUZZLE_FLASH_1_ROWS[] = {0, 0, 0, 0, 0, 0};
    const u8 MUZZLE_FLASH_1_COLS[] = {0, 1, 2, 3, 4, 5};
    u8 muzzle_flash_1_frame_count = ARRAY_LENGTH(MUZZLE_FLASH_1_COLS);

    const u8 MUZZLE_FLASH_2_DIMENSIONS[] = {24, 24};
    const f32 MUZZLE_FLASH_2_DURATIONS[] = {0.05, 0.05, 0.1, 0.1};
    const u8 MUZZLE_FLASH_2_ROWS[] = {0, 0, 0, 0};
    const u8 MUZZLE_FLASH_2_COLS[] = {0, 1, 2, 3};
    u8 muzzle_flash_2_frame_count = ARRAY_LENGTH(MUZZLE_FLASH_2_COLS);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_0, "assets/wip/muzzle_flash_v3_0.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_0 = animation_definition_create(
        &sprite_sheet_muzzle_flash_0, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_1, "assets/wip/muzzle_flash_v3_1.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_1 = animation_definition_create(
        &sprite_sheet_muzzle_flash_1, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2, "assets/wip/muzzle_flash_v3_2.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_2 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_3, "assets/wip/muzzle_flash_v3_3.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_3 = animation_definition_create(
        &sprite_sheet_muzzle_flash_3, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_4, "assets/wip/muzzle_flash_v3_4.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_4 = animation_definition_create(
        &sprite_sheet_muzzle_flash_4, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_5, "assets/wip/muzzle_flash_v3_5.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_5 = animation_definition_create(
        &sprite_sheet_muzzle_flash_5, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_6, "assets/wip/muzzle_flash_v3_6.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_6 = animation_definition_create(
        &sprite_sheet_muzzle_flash_6, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_7, "assets/wip/muzzle_flash_v3_7.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_7 = animation_definition_create(
        &sprite_sheet_muzzle_flash_7, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_8, "assets/wip/muzzle_flash_v3_8.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_8 = animation_definition_create(
        &sprite_sheet_muzzle_flash_8, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_9, "assets/wip/muzzle_flash_v3_9.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_9 = animation_definition_create(
        &sprite_sheet_muzzle_flash_9, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_10, "assets/wip/muzzle_flash_v3_10.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_10 = animation_definition_create(
        &sprite_sheet_muzzle_flash_10, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_11, "assets/wip/muzzle_flash_v3_11.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_11 = animation_definition_create(
        &sprite_sheet_muzzle_flash_11, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_12, "assets/wip/muzzle_flash_v3_12.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_12 = animation_definition_create(
        &sprite_sheet_muzzle_flash_12, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_13, "assets/wip/muzzle_flash_v3_13.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_13 = animation_definition_create(
        &sprite_sheet_muzzle_flash_13, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_14, "assets/wip/muzzle_flash_v3_14.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_14 = animation_definition_create(
        &sprite_sheet_muzzle_flash_14, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_15, "assets/wip/muzzle_flash_v3_15.png", MUZZLE_FLASH_1_DIMENSIONS[0], MUZZLE_FLASH_1_DIMENSIONS[1]);
    adef_muzzle_flash_15 = animation_definition_create(
        &sprite_sheet_muzzle_flash_15, (f32 *)MUZZLE_FLASH_1_DURATIONS, (u8 *)MUZZLE_FLASH_1_ROWS, (u8 *)MUZZLE_FLASH_1_COLS, muzzle_flash_1_frame_count);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_0, "assets/wip/muzzle_flash_2_0.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_0 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_0, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_1, "assets/wip/muzzle_flash_2_1.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_1 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_1, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_2, "assets/wip/muzzle_flash_2_2.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_2 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_2, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_3, "assets/wip/muzzle_flash_2_3.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_3 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_3, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_4, "assets/wip/muzzle_flash_2_4.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_4 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_4, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_5, "assets/wip/muzzle_flash_2_5.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_5 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_5, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_6, "assets/wip/muzzle_flash_2_6.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_6 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_6, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_7, "assets/wip/muzzle_flash_2_7.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_7 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_7, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_8, "assets/wip/muzzle_flash_2_8.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_8 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_8, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_9, "assets/wip/muzzle_flash_2_9.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_9 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_9, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_10, "assets/wip/muzzle_flash_2_10.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_10 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_10, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_11, "assets/wip/muzzle_flash_2_11.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_11 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_11, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_12, "assets/wip/muzzle_flash_2_12.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_12 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_12, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_13, "assets/wip/muzzle_flash_2_13.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_13 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_13, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_14, "assets/wip/muzzle_flash_2_14.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_14 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_14, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2_15, "assets/wip/muzzle_flash_2_15.png", MUZZLE_FLASH_2_DIMENSIONS[0], MUZZLE_FLASH_2_DIMENSIONS[1]);
    adef_muzzle_flash_2_15 = animation_definition_create(
        &sprite_sheet_muzzle_flash_2_15, (f32 *)MUZZLE_FLASH_2_DURATIONS, (u8 *)MUZZLE_FLASH_2_ROWS, (u8 *)MUZZLE_FLASH_2_COLS, muzzle_flash_2_frame_count);
}

void init_explosion_adef_hashmap(void)
{
    explosion_adef_map = create_hash_map(EXPLOSION_COUNT * ANGLES);

    insert(explosion_adef_map, "muzzle_flash_1_0", adef_muzzle_flash_0); // TODO: update these to adef_muzzle_flash_1_0 ... etc
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
    insert(explosion_adef_map, "muzzle_flash_2_0", adef_muzzle_flash_2_0);
    insert(explosion_adef_map, "muzzle_flash_2_1", adef_muzzle_flash_2_1);
    insert(explosion_adef_map, "muzzle_flash_2_2", adef_muzzle_flash_2_2);
    insert(explosion_adef_map, "muzzle_flash_2_3", adef_muzzle_flash_2_3);
    insert(explosion_adef_map, "muzzle_flash_2_4", adef_muzzle_flash_2_4);
    insert(explosion_adef_map, "muzzle_flash_2_5", adef_muzzle_flash_2_5);
    insert(explosion_adef_map, "muzzle_flash_2_6", adef_muzzle_flash_2_6);
    insert(explosion_adef_map, "muzzle_flash_2_7", adef_muzzle_flash_2_7);
    insert(explosion_adef_map, "muzzle_flash_2_8", adef_muzzle_flash_2_8);
    insert(explosion_adef_map, "muzzle_flash_2_9", adef_muzzle_flash_2_9);
    insert(explosion_adef_map, "muzzle_flash_2_10", adef_muzzle_flash_2_10);
    insert(explosion_adef_map, "muzzle_flash_2_11", adef_muzzle_flash_2_11);
    insert(explosion_adef_map, "muzzle_flash_2_12", adef_muzzle_flash_2_12);
    insert(explosion_adef_map, "muzzle_flash_2_13", adef_muzzle_flash_2_13);
    insert(explosion_adef_map, "muzzle_flash_2_14", adef_muzzle_flash_2_14);
    insert(explosion_adef_map, "muzzle_flash_2_15", adef_muzzle_flash_2_15);
}

void init_blood_splatter_adef_hashmap(void)
{
    blood_splatter_adef_map = create_hash_map(BLOOD_SPLATTER_COUNT);
    insert(blood_splatter_adef_map, "blood_splatter_1", adef_blood_splatter_1);
    insert(blood_splatter_adef_map, "blood_splatter_2", adef_blood_splatter_2);
}

void init_brass_animation_definitions(void)
{
    render_sprite_sheet_init(&sprite_sheet_brass_falling_1, "assets/wip/brass_falling_1.png", 3, 3);
    adef_brass_falling_1 = animation_definition_create(&sprite_sheet_brass_falling_1, (f32[]){0.06, 0.06, 0.06, 0.06}, (u8[]){0, 0, 0, 0}, (u8[]){0, 1, 2, 3}, 4);
    render_sprite_sheet_init(&sprite_sheet_shotgun_shell_falling_1, "assets/wip/shotgun_shell_falling_1.png", 3, 3);
    adef_shotgun_shell_falling_1 = animation_definition_create(
        &sprite_sheet_shotgun_shell_falling_1, (f32[]){0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06, 0.06}, (u8[]){0, 0, 0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5, 6, 7}, 8);
}

void init_character_shadow_anim(void)
{
    render_sprite_sheet_init(&sprite_sheet_character_shadow, "assets/wip/character_shadow.png", 16, 5);
    adef_character_shadow = animation_definition_create(&sprite_sheet_character_shadow, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_character_shadow = animation_create(adef_character_shadow, false);
}

void init_blood_splatter_animation_definitions(void)
{
    render_sprite_sheet_init(&sprite_sheet_blood_splatter_1, "assets/wip/blood_splatter_1.png", 13, 13);
    adef_blood_splatter_1 = animation_definition_create(&sprite_sheet_blood_splatter_1, (f32[]){0.05, 0.05, 0.05, 0.05, 0.05}, (u8[]){0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4}, 5);
    render_sprite_sheet_init(&sprite_sheet_blood_splatter_2, "assets/wip/blood_splatter_2.png", 13, 13);
    adef_blood_splatter_2 = animation_definition_create(&sprite_sheet_blood_splatter_2, (f32[]){0.05, 0.05, 0.05, 0.05, 0.05}, (u8[]){0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4}, 5);
}