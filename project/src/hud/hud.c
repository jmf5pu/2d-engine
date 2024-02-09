#include "hud.h"
#include <float.h>

HUD *hud;

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
    render_sprite_sheet_init(&sprite_sheet_health_cross_0, "assets/hud/health_cross_0.png", 100, 100);
    adef_health_cross_0 = animation_definition_create(&sprite_sheet_health_cross_0, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_health_cross_0 = animation_create(adef_health_cross_0, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_1, "assets/hud/health_cross_1.png", 100, 100);
    adef_health_cross_1 = animation_definition_create(&sprite_sheet_health_cross_1, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_health_cross_1 = animation_create(adef_health_cross_1, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_2, "assets/hud/health_cross_2.png", 100, 100);
    adef_health_cross_2 = animation_definition_create(&sprite_sheet_health_cross_2, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_health_cross_2 = animation_create(adef_health_cross_2, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_3, "assets/hud/health_cross_3.png", 100, 100);
    adef_health_cross_3 = animation_definition_create(&sprite_sheet_health_cross_3, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_health_cross_3 = animation_create(adef_health_cross_3, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_4, "assets/hud/health_cross_4.png", 100, 100);
    adef_health_cross_4 = animation_definition_create(&sprite_sheet_health_cross_4, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_health_cross_4 = animation_create(adef_health_cross_4, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_5, "assets/hud/health_cross_5.png", 100, 100);
    adef_health_cross_5 = animation_definition_create(&sprite_sheet_health_cross_5, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_health_cross_5 = animation_create(adef_health_cross_5, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_6, "assets/hud/health_cross_6.png", 100, 100);
    adef_health_cross_6 = animation_definition_create(&sprite_sheet_health_cross_6, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_health_cross_6 = animation_create(adef_health_cross_6, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_7, "assets/hud/health_cross_7.png", 100, 100);
    adef_health_cross_7 = animation_definition_create(&sprite_sheet_health_cross_7, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_health_cross_7 = animation_create(adef_health_cross_7, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_8, "assets/hud/health_cross_8.png", 100, 100);
    adef_health_cross_8 = animation_definition_create(&sprite_sheet_health_cross_8, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_health_cross_8 = animation_create(adef_health_cross_8, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_9, "assets/hud/health_cross_9.png", 100, 100);
    adef_health_cross_9 = animation_definition_create(&sprite_sheet_health_cross_9, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_health_cross_9 = animation_create(adef_health_cross_9, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_10, "assets/hud/health_cross_10.png", 100, 100);
    adef_health_cross_10 = animation_definition_create(&sprite_sheet_health_cross_10, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_health_cross_10 = animation_create(adef_health_cross_10, true);

    render_sprite_sheet_init(&sprite_sheet_health_cross_11, "assets/hud/health_cross_11.png", 100, 100);
    adef_health_cross_11 = animation_definition_create(&sprite_sheet_health_cross_11, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_health_cross_11 = animation_create(adef_health_cross_11, true);

    render_sprite_sheet_init(&sprite_sheet_health_cross_12, "assets/hud/health_cross_12.png", 100, 100);
    adef_health_cross_12 = animation_definition_create(&sprite_sheet_health_cross_12, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_health_cross_12 = animation_create(adef_health_cross_12, true);

    render_sprite_sheet_init(&sprite_sheet_health_cross_13, "assets/hud/health_cross_13.png", 100, 100);
    adef_health_cross_13 = animation_definition_create(&sprite_sheet_health_cross_13, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_health_cross_13 = animation_create(adef_health_cross_13, true);

    render_sprite_sheet_init(&sprite_sheet_health_cross_14, "assets/hud/health_cross_14.png", 100, 100);
    adef_health_cross_14 = animation_definition_create(&sprite_sheet_health_cross_14, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_health_cross_14 = animation_create(adef_health_cross_14, false);
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
    adef_ammo_0_blinking = animation_definition_create(&sprite_sheet_ammo_0_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_ammo_0_blinking = animation_create(adef_ammo_0_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_1_blinking, "assets/hud/1_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_1_blinking = animation_definition_create(&sprite_sheet_ammo_1_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_ammo_1_blinking = animation_create(adef_ammo_1_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_2_blinking, "assets/hud/2_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_2_blinking = animation_definition_create(&sprite_sheet_ammo_2_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_ammo_2_blinking = animation_create(adef_ammo_2_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_3_blinking, "assets/hud/3_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_3_blinking = animation_definition_create(&sprite_sheet_ammo_3_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_ammo_3_blinking = animation_create(adef_ammo_3_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_4_blinking, "assets/hud/4_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_4_blinking = animation_definition_create(&sprite_sheet_ammo_4_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_ammo_4_blinking = animation_create(adef_ammo_4_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_5_blinking, "assets/hud/5_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_5_blinking = animation_definition_create(&sprite_sheet_ammo_5_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_ammo_5_blinking = animation_create(adef_ammo_5_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_6_blinking, "assets/hud/6_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_6_blinking = animation_definition_create(&sprite_sheet_ammo_6_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_ammo_6_blinking = animation_create(adef_ammo_6_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_7_blinking, "assets/hud/7_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_7_blinking = animation_definition_create(&sprite_sheet_ammo_7_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_ammo_7_blinking = animation_create(adef_ammo_7_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_8_blinking, "assets/hud/8_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_8_blinking = animation_definition_create(&sprite_sheet_ammo_8_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_ammo_8_blinking = animation_create(adef_ammo_8_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_ammo_9_blinking, "assets/hud/9_blinking.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_9_blinking = animation_definition_create(&sprite_sheet_ammo_9_blinking, (f32[]){0.5, 0.5}, (u8[]){0, 0}, (u8[]){1, 2}, 2);
    anim_ammo_9_blinking = animation_create(adef_ammo_9_blinking, true);

    render_sprite_sheet_init(&sprite_sheet_forward_slash, "assets/hud/forward_slash.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_forward_slash = animation_definition_create(&sprite_sheet_forward_slash, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_forward_slash = animation_create(adef_forward_slash, false);
}

void render_health(SDL_Window *window, u32 texture_slots[32], Player *player, vec2 position, vec4 color)
{
    i16 health = player->health;
    if (health == 100) {
        animation_render(anim_health_cross_0, window, position, 0, color, texture_slots);
    }
    else if (health > 93) {
        animation_render(anim_health_cross_1, window, position, 0, color, texture_slots);
    }
    else if (health > 86) {
        animation_render(anim_health_cross_2, window, position, 0, color, texture_slots);
    }
    else if (health > 79) {
        animation_render(anim_health_cross_3, window, position, 0, color, texture_slots);
    }
    else if (health > 72) {
        animation_render(anim_health_cross_4, window, position, 0, color, texture_slots);
    }
    else if (health > 65) {
        animation_render(anim_health_cross_5, window, position, 0, color, texture_slots);
    }
    else if (health > 58) {
        animation_render(anim_health_cross_6, window, position, 0, color, texture_slots);
    }
    else if (health > 51) {
        animation_render(anim_health_cross_7, window, position, 0, color, texture_slots);
    }
    else if (health > 44) {
        animation_render(anim_health_cross_8, window, position, 0, color, texture_slots);
    }
    else if (health > 37) {
        animation_render(anim_health_cross_9, window, position, 0, color, texture_slots);
    }
    else if (health > 30) {
        animation_render(anim_health_cross_10, window, position, 0, color, texture_slots);
    }
    else if (health > 23) {
        animation_render(anim_health_cross_11, window, position, 0, color, texture_slots);
    }
    else if (health > 16) {
        animation_render(anim_health_cross_12, window, position, 0, color, texture_slots);
    }
    else if (health > 0) {
        animation_render(anim_health_cross_13, window, position, 0, color, texture_slots);
    }
    else if (health <= 0) {
        animation_render(anim_health_cross_14, window, position, 0, color, texture_slots);
    }
}

// renders the ammo display digit and returns the updated value for calculating
// the next position
u16 render_ammo_digit(SDL_Window *window, u32 texture_slots[32], vec2 position, vec4 color, u16 value, f32 current_ammo_fraction)
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
    animation_render(digit_anim, window, position, 0, color, texture_slots);
    free(digit_anim_name);

    // remove the digit we just rendered and return
    return value / 10;
}

// Renders the ammo display. Renders the digits in each value from left to right
void render_ammo(SDL_Window *window, u32 texture_slots[32], Player *player, vec2 position, vec4 color)
{
    f32 current_ammo_fraction = (f32)player->weapon->capacity / player->weapon->max_capacity;

    u16 capacity = player->weapon->capacity;
    u16 reserve = player->weapon->reserve;

    // tracks how many digits of each attribute we have written
    u16 reserve_digits = 0;
    u16 capacity_digits = 0;

    // render the player's weapon's ammo icon before numbers if on left side
    // of the screen
    if (player->weapon->hud_ammo_icon && player->is_left_player) {
        animation_render(player->weapon->hud_ammo_icon, window, position, 0, color, texture_slots);
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
        animation_render(anim_ammo_0, window, position, 0, color, texture_slots);
        position[0] -= DIGIT_WIDTH;
        reserve_digits++;
    }
    // add slash in between reserve and capacity
    animation_render(anim_forward_slash, window, position, 0, color, texture_slots);
    position[0] -= DIGIT_WIDTH;
    // repeat logic for capacity attribute
    while (capacity > 0) {
        capacity = render_ammo_digit(window, texture_slots, position, color, capacity, current_ammo_fraction);
        position[0] -= DIGIT_WIDTH;
        capacity_digits++;
    }
    while (capacity_digits < 3) {
        // for capacity, make the trailing 0's blink when appropriate
        animation_render(current_ammo_fraction <= AMMO_BLINKING_THRESHOLD ? anim_ammo_0_blinking : anim_ammo_0, window, position, 0, color, texture_slots);
        position[0] -= DIGIT_WIDTH;
        capacity_digits++;
    }

    // render the player's weapon's ammo icon after numbers if on right side
    // of the screen
    if (player->weapon->hud_ammo_icon && !player->is_left_player) {
        position[0] -= ICON_SPACE;
        animation_render(player->weapon->hud_ammo_icon, window, position, 0, color, texture_slots);
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
    render_sprite_sheet_init(&sprite_sheet_divider, "assets/hud/divider.png", 10, 1500);

    // initialize struct
    hud = malloc(sizeof(HUD));
    hud->window = window;

    // init right side of the hud (if there is a second player)
    if (SPLIT_SCREEN) {
    }
}

// renders the heads up display (should be called once per frame)
void render_hud(SDL_Window *window, u32 texture_slots[32], vec4 color)
{
    // render the player crosshairs (if active)
    if (player_one->crosshair->entity->is_active) {
        vec2 animation_position;
        f32 x_pos = SPLIT_SCREEN ? player_one->crosshair->percentage_of_screen[0] * render_width * 0.5 : player_one->crosshair->percentage_of_screen[0] * render_width;
        f32 y_pos = player_one->crosshair->percentage_of_screen[1] * render_height;
        f32 crosshair_buffer = CROSSHAIR_SIZE * 0.5;
        if (x_pos > (SPLIT_SCREEN ? render_width * 0.5 - crosshair_buffer : render_width - crosshair_buffer))
            x_pos = (SPLIT_SCREEN ? render_width * 0.5 - crosshair_buffer : render_width - crosshair_buffer);
        if (x_pos < crosshair_buffer)
            x_pos = crosshair_buffer;
        animation_position[0] = x_pos;
        if (y_pos > render_height - crosshair_buffer)
            y_pos = render_height - crosshair_buffer;
        if (y_pos < crosshair_buffer)
            y_pos = crosshair_buffer;
        animation_position[1] = y_pos;
        animation_render(player_one->crosshair->entity->animation, window, animation_position, 0, color, texture_slots);
    }

    // render player one displays (health + ammo)
    render_health(window, texture_slots, player_one, (vec2){50, (window_height * DEFAULT_RENDER_SCALE_FACTOR) - 50}, color);
    render_ammo(window, texture_slots, player_one, (vec2){0.5 * DIGIT_WIDTH + DIGIT_WIDTH * 7 + ICON_SPACE, 0.5 * DIGIT_HEIGHT}, color);

    // render player two displays if relevant
    if (SPLIT_SCREEN) {
        // render player two's displays
        if (player_two->crosshair->entity->is_active) {
            vec2 animation_position;
            f32 x_pos = player_two->crosshair->percentage_of_screen[0] * render_width * 0.5 + render_width * 0.5;
            f32 y_pos = player_two->crosshair->percentage_of_screen[1] * render_height;
            f32 crosshair_buffer = CROSSHAIR_SIZE * 0.5;
            if (x_pos > render_width - crosshair_buffer)
                x_pos = render_width - crosshair_buffer;
            if (x_pos < render_width * 0.5 + crosshair_buffer)
                x_pos = render_width * 0.5 + crosshair_buffer;
            animation_position[0] = x_pos;
            if (y_pos > render_height - crosshair_buffer)
                y_pos = render_height - crosshair_buffer;
            if (y_pos < crosshair_buffer)
                y_pos = crosshair_buffer;
            animation_position[1] = y_pos;
            animation_render(player_two->crosshair->entity->animation, window, animation_position, 0, color, texture_slots);
        }
        render_health(window, texture_slots, player_two, (vec2){window_width - 50, window_height - 50}, color);
        render_ammo(window, texture_slots, player_two, (vec2){window_width - 0.5 * DIGIT_WIDTH, 0.5 * DIGIT_HEIGHT}, color);

        // render viewport divider
        render_sprite_sheet_frame(
            &sprite_sheet_divider, window, 0, 0, (vec2){render_width * 0.5, render_height * 0.5}, 0, false, RENDER_PHYSICS_BODIES ? SEMI_TRANSPARENT : color, texture_slots);
    }
}
