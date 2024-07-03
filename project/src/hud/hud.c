#include "hud.h"
#include "../engine/util.h"
#include <float.h>
#include <math.h>

HUD *hud;

// extern from main.c
u32 texture_slots[BATCH_SIZE];
vec4 game_color;
SDL_Window *window;

f32 interact_bar_open_close_durations[] = {0.05, 0.05, 0.05, 0.05};
vec2 interact_bar_size = {16, 3};

// renders the heads up display (should be called once per frame)
void render_hud(void)
{
    vec2 player_one_interact_bar_position = {player_one->entity->body->aabb.position[0], player_one->entity->body->aabb.position[1] + 15};

    // render player one displays (health + ammo + crosshair)
    render_health(player_one, (vec2){23, 5});
    // render_ammo(window, texture_slots, player_one, (vec2){0.5 * DIGIT_WIDTH + DIGIT_WIDTH * 7 + ICON_SPACE, 0.5 * DIGIT_HEIGHT}, color);
    animation_render(player_one->crosshair->animation, window, player_one->crosshair->body->aabb.position, game_color, texture_slots);

    if (player_one->status == PLAYER_RELOADING || player_one->status == PLAYER_INTERACTING) {
        u16 interact_bar_frame_delay = player_one->status == PLAYER_RELOADING ? player_one->weapon->weapon_type->reload_frame_delay : player_one->interact_frame_delay;
        f32 opening_anim_frame_count = get_array_sum(interact_bar_open_close_durations, ARRAY_LENGTH(interact_bar_open_close_durations)) * FRAME_RATE;
        vec2_dup(player_one->interact_bar->body->aabb.position, player_one->entity->body->aabb.position);
        player_one->interact_bar->body->aabb.position[1] += 15;
        if (player_one->frames_on_status < opening_anim_frame_count) {
            animation_render(player_one->interact_bar->animation, window, player_one->interact_bar->body->aabb.position, game_color, texture_slots);
        }
        else if (player_one->frames_on_status >= opening_anim_frame_count) {
            if (player_one->frames_on_status == opening_anim_frame_count) {
                animation_destroy(player_one->interact_bar->animation);
                player_one->interact_bar->animation = NULL;
            }
            render_interact_bar_progress(
                player_one->interact_bar, (f32)(player_one->frames_on_status - opening_anim_frame_count) / (interact_bar_frame_delay - opening_anim_frame_count));
        }
        player_one->frames_on_status++;
    }

    // render player two displays if relevant
    if (SPLIT_SCREEN) {
        // vec2 player_two_interact_bar_position = {player_two->entity->body->aabb.position[0], player_two->entity->body->aabb.position[1] + 15};

        // // render_health(window, texture_slots, player_two, (vec2){render_width - 50, render_height - 50}, color);
        // // render_ammo(window, texture_slots, player_two, (vec2){render_width - 0.5 * DIGIT_WIDTH, 0.5 * DIGIT_HEIGHT}, color);
        // animation_render(player_two->crosshair->animation, window, player_two->crosshair->body->aabb.position, game_color, texture_slots);

        // // render viewport divider
        // render_sprite_sheet_frame(
        //     &sprite_sheet_divider, window, 0, 0, (vec2){render_width * 0.5, render_height * 0.5}, 0, false, RENDER_PHYSICS_BODIES ? SEMI_TRANSPARENT : game_color,
        //     texture_slots);

        // if (player_two->status == PLAYER_RELOADING) {
        //     render_interact_bar_progress(player_two_interact_bar_position, player_two->frames_on_status / player_two->weapon->reload_frame_delay);
        // }
    }
}

void render_health(Player *player, vec2 position)
{
    // render correct health meter sprite based off player's current health
    animation_render(anim_health_meter_0, window, position, game_color, texture_slots);
}

// renders the ammo display digit and returns the updated value for calculating
// the next position
u16 render_ammo_digit(SDL_Window *window, u32 texture_slots[BATCH_SIZE], vec2 position, vec4 color, u16 value, f32 current_ammo_fraction)
{
    // get least significant digit and convert to string for use with anim
    // hashmap
    u16 digit = value % 10;
    char digit_str[2]; // 1 digit null terminated
    sprintf(digit_str, "%u", digit);

    char *digit_anim_name = calloc(50, sizeof(char));
    strcat(digit_anim_name, "anim_ammo_");
    strcat(digit_anim_name, digit_str);
    if (current_ammo_fraction <= AMMO_BLINKING_THRESHOLD)
        strcat(digit_anim_name, "_blinking");
    Animation *digit_anim = get(ammo_anim_map, digit_anim_name);
    animation_render(digit_anim, window, position, color, texture_slots);
    free(digit_anim_name);

    // remove the digit we just rendered and return
    return value / 10;
}

// Renders the ammo display. Renders the digits in each value from left to right
void render_ammo(SDL_Window *window, u32 texture_slots[BATCH_SIZE], Player *player, vec2 position, vec4 color)
{
    f32 current_ammo_fraction = (f32)player->weapon->capacity / player->weapon->weapon_type->capacity;

    u16 capacity = player->weapon->capacity;
    u16 reserve = player->weapon->reserve;

    // tracks how many digits of each attribute we have written
    u16 reserve_digits = 0;
    u16 capacity_digits = 0;

    // render the player's weapon's ammo icon before numbers if on left side
    // of the screen
    if (player->weapon->weapon_type->hud_ammo_icon && player->is_left_player) {
        animation_render(player->weapon->weapon_type->hud_ammo_icon, window, position, color, texture_slots);
        position[0] -= DIGIT_WIDTH + ICON_SPACE; // add a bit of space between
                                                 // icon and the numbers
    }
    // keep rendering digits for the capacity while there are digits left
    while (reserve > 0) {
        reserve = render_ammo_digit(
            window,
            texture_slots,
            position,
            color,
            reserve,
            1); // pass 1 as current_ammo_fraction so we
                // never render blinking digits for reserve
        position[0] -= DIGIT_WIDTH;
        reserve_digits++;
    }

    // add trailing 0's to get it up to 3 digits
    while (reserve_digits < 3) {
        animation_render(anim_ammo_0, window, position, color, texture_slots);
        position[0] -= DIGIT_WIDTH;
        reserve_digits++;
    }
    // add slash in between reserve and capacity
    animation_render(anim_forward_slash, window, position, color, texture_slots);
    position[0] -= DIGIT_WIDTH;
    // repeat logic for capacity attribute
    while (capacity > 0) {
        capacity = render_ammo_digit(window, texture_slots, position, color, capacity, current_ammo_fraction);
        position[0] -= DIGIT_WIDTH;
        capacity_digits++;
    }
    while (capacity_digits < 3) {
        // for capacity, make the trailing 0's blink when appropriate
        animation_render(current_ammo_fraction <= AMMO_BLINKING_THRESHOLD ? anim_ammo_0_blinking : anim_ammo_0, window, position, color, texture_slots);
        position[0] -= DIGIT_WIDTH;
        capacity_digits++;
    }

    // render the player's weapon's ammo icon after numbers if on right side
    // of the screen
    if (player->weapon->weapon_type->hud_ammo_icon && !player->is_left_player) {
        position[0] -= ICON_SPACE;
        animation_render(player->weapon->weapon_type->hud_ammo_icon, window, position, color, texture_slots);
        position[0] -= DIGIT_WIDTH; // add a bit of space between icon
                                    // and the numbers
    }
}

// frees the dynamic hud memory
void free_hud(void)
{
    if (hud)
        free(hud);
}

// initializes heads up display
void init_hud(SDL_Window *window)
{
    // init anims used by the hud
    init_health_anims();
    init_ammo_anims();
    init_ammo_anim_hashmap();
    init_interact_bar_adefs();
    render_sprite_sheet_init(&sprite_sheet_divider, "assets/wip/divider.png", 2, 1500);

    // initialize struct
    hud = malloc(sizeof(HUD));
    hud->window = window;

    // init right side of the hud (if there is a second player)
    if (SPLIT_SCREEN) {
    }
}

/// @brief Ensures that the players crosshair is only rendered on their side of the screen and stays within the bounds of the window
/// @param player the active player
void fix_crosshair_position(Player *player)
{
    f32 crosshair_buffer = CROSSHAIR_SIZE * 0.5;
    f32 x_lower_bound = player->is_left_player ? crosshair_buffer : render_width + crosshair_buffer;
    f32 x_upper_bound = SPLIT_SCREEN && !player->is_left_player ? 2 * render_width - crosshair_buffer : render_width - crosshair_buffer;

    if (player->crosshair->body->aabb.position[0] > x_upper_bound)
        player->crosshair->body->aabb.position[0] = x_upper_bound;
    if (player->crosshair->body->aabb.position[0] < x_lower_bound)
        player->crosshair->body->aabb.position[0] = x_lower_bound;
    if (player->crosshair->body->aabb.position[1] > render_height - crosshair_buffer)
        player->crosshair->body->aabb.position[1] = render_height - crosshair_buffer;
    if (player->crosshair->body->aabb.position[1] < crosshair_buffer)
        player->crosshair->body->aabb.position[1] = crosshair_buffer;
}

void init_interact_bar_adefs(void)
{
    render_sprite_sheet_init(&sprite_sheet_interact_bar_open, "assets/wip/interact_bar_open.png", 16, 3);
    adef_interact_bar_open = animation_definition_create(&sprite_sheet_interact_bar_open, interact_bar_open_close_durations, (u8[]){0, 0, 0, 0}, (u8[]){0, 1, 2, 3}, 4);
    render_sprite_sheet_init(&sprite_sheet_interact_bar_close, "assets/wip/interact_bar_close.png", 16, 3);
    adef_interact_bar_close = animation_definition_create(&sprite_sheet_interact_bar_close, interact_bar_open_close_durations, (u8[]){0, 0, 0, 0}, (u8[]){0, 1, 2, 3}, 4);
    render_sprite_sheet_init(&sprite_sheet_interact_bar, "assets/wip/interact_bar.png", 16, 3);
    adef_interact_bar = animation_definition_create(
        &sprite_sheet_interact_bar,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13},
        14);
}

void render_interact_bar_progress(Entity *entity, f32 percentage)
{
    const interact_bar_frame_count = 14;
    f32 frame_column = MAX(floor(percentage * interact_bar_frame_count), 0);
    render_sprite_sheet_frame(&sprite_sheet_interact_bar, window, 0, frame_column, entity->body->aabb.position, 100, false, game_color, texture_slots);
}

void init_ammo_anim_hashmap(void)
{
    ammo_anim_map = create_hash_map(AMMO_ANIM_COUNT);
    insert(ammo_anim_map, "anim_ammo_0", anim_ammo_0);
    insert(ammo_anim_map, "anim_ammo_1", anim_ammo_1);
    insert(ammo_anim_map, "anim_ammo_2", anim_ammo_2);
    insert(ammo_anim_map, "anim_ammo_3", anim_ammo_3);
    insert(ammo_anim_map, "anim_ammo_4", anim_ammo_4);
    insert(ammo_anim_map, "anim_ammo_5", anim_ammo_5);
    insert(ammo_anim_map, "anim_ammo_6", anim_ammo_6);
    insert(ammo_anim_map, "anim_ammo_7", anim_ammo_7);
    insert(ammo_anim_map, "anim_ammo_8", anim_ammo_8);
    insert(ammo_anim_map, "anim_ammo_9", anim_ammo_9);
    insert(ammo_anim_map, "anim_ammo_0_blinking", anim_ammo_0_blinking);
    insert(ammo_anim_map, "anim_ammo_1_blinking", anim_ammo_1_blinking);
    insert(ammo_anim_map, "anim_ammo_2_blinking", anim_ammo_2_blinking);
    insert(ammo_anim_map, "anim_ammo_3_blinking", anim_ammo_3_blinking);
    insert(ammo_anim_map, "anim_ammo_4_blinking", anim_ammo_4_blinking);
    insert(ammo_anim_map, "anim_ammo_5_blinking", anim_ammo_5_blinking);
    insert(ammo_anim_map, "anim_ammo_6_blinking", anim_ammo_6_blinking);
    insert(ammo_anim_map, "anim_ammo_7_blinking", anim_ammo_7_blinking);
    insert(ammo_anim_map, "anim_ammo_8_blinking", anim_ammo_8_blinking);
    insert(ammo_anim_map, "anim_ammo_9_blinking", anim_ammo_9_blinking);
}

void init_health_anims(void)
{
    render_sprite_sheet_init(&sprite_sheet_health_meter_0, "assets/wip/health_meter_med.png", 44, 8);
    adef_health_meter_0 = animation_definition_create(&sprite_sheet_health_meter_0, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_health_meter_0 = animation_create(adef_health_meter_0, false);
}

void init_ammo_anims(void)
{
    render_sprite_sheet_init(&sprite_sheet_ammo_0, "assets/hud/0.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_0 = animation_definition_create(&sprite_sheet_ammo_0, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_ammo_0 = animation_create(adef_ammo_0, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_1, "assets/hud/1.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_1 = animation_definition_create(&sprite_sheet_ammo_1, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_ammo_1 = animation_create(adef_ammo_1, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_2, "assets/hud/2.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_2 = animation_definition_create(&sprite_sheet_ammo_2, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_ammo_2 = animation_create(adef_ammo_2, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_3, "assets/hud/3.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_3 = animation_definition_create(&sprite_sheet_ammo_3, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_ammo_3 = animation_create(adef_ammo_3, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_4, "assets/hud/4.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_4 = animation_definition_create(&sprite_sheet_ammo_4, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_ammo_4 = animation_create(adef_ammo_4, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_5, "assets/hud/5.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_5 = animation_definition_create(&sprite_sheet_ammo_5, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_ammo_5 = animation_create(adef_ammo_5, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_6, "assets/hud/6.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_6 = animation_definition_create(&sprite_sheet_ammo_6, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_ammo_6 = animation_create(adef_ammo_6, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_7, "assets/hud/7.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_7 = animation_definition_create(&sprite_sheet_ammo_7, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_ammo_7 = animation_create(adef_ammo_7, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_8, "assets/hud/8.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_8 = animation_definition_create(&sprite_sheet_ammo_8, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_ammo_8 = animation_create(adef_ammo_8, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_9, "assets/hud/9.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_9 = animation_definition_create(&sprite_sheet_ammo_9, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_ammo_9 = animation_create(adef_ammo_9, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_0_blinking, "assets/hud/0_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_0_blinking = animation_definition_create(&sprite_sheet_ammo_0_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    anim_ammo_0_blinking = animation_create(adef_ammo_0_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_1_blinking, "assets/hud/1_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_1_blinking = animation_definition_create(&sprite_sheet_ammo_1_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    anim_ammo_1_blinking = animation_create(adef_ammo_1_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_2_blinking, "assets/hud/2_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_2_blinking = animation_definition_create(&sprite_sheet_ammo_2_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    anim_ammo_2_blinking = animation_create(adef_ammo_2_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_3_blinking, "assets/hud/3_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_3_blinking = animation_definition_create(&sprite_sheet_ammo_3_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    anim_ammo_3_blinking = animation_create(adef_ammo_3_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_4_blinking, "assets/hud/4_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_4_blinking = animation_definition_create(&sprite_sheet_ammo_4_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    anim_ammo_4_blinking = animation_create(adef_ammo_4_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_5_blinking, "assets/hud/5_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_5_blinking = animation_definition_create(&sprite_sheet_ammo_5_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    anim_ammo_5_blinking = animation_create(adef_ammo_5_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_6_blinking, "assets/hud/6_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_6_blinking = animation_definition_create(&sprite_sheet_ammo_6_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    anim_ammo_6_blinking = animation_create(adef_ammo_6_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_7_blinking, "assets/hud/7_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_7_blinking = animation_definition_create(&sprite_sheet_ammo_7_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    anim_ammo_7_blinking = animation_create(adef_ammo_7_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_8_blinking, "assets/hud/8_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_8_blinking = animation_definition_create(&sprite_sheet_ammo_8_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    anim_ammo_8_blinking = animation_create(adef_ammo_8_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_9_blinking, "assets/hud/9_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_9_blinking = animation_definition_create(&sprite_sheet_ammo_9_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    anim_ammo_9_blinking = animation_create(adef_ammo_9_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_forward_slash, "assets/hud/forward_slash.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_forward_slash = animation_definition_create(&sprite_sheet_forward_slash, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_forward_slash = animation_create(adef_forward_slash, false);
}
