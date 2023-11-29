#include "hud.h"

HUD *hud;

void init_health_anims(void)
{
    render_sprite_sheet_init(&sprite_sheet_health_cross_0, "assets/hud/health_cross_0.png", 100, 100);
    adef_health_cross_0 = animation_definition_create(
        &sprite_sheet_health_cross_0,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_0 = animation_create(adef_health_cross_0, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_1, "assets/hud/health_cross_1.png", 100, 100);
    adef_health_cross_1 = animation_definition_create(
        &sprite_sheet_health_cross_1,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_1 = animation_create(adef_health_cross_1, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_2, "assets/hud/health_cross_2.png", 100, 100);
    adef_health_cross_2 = animation_definition_create(
        &sprite_sheet_health_cross_2,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_2 = animation_create(adef_health_cross_2, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_3, "assets/hud/health_cross_3.png", 100, 100);
    adef_health_cross_3 = animation_definition_create(
        &sprite_sheet_health_cross_3,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_3 = animation_create(adef_health_cross_3, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_4, "assets/hud/health_cross_4.png", 100, 100);
    adef_health_cross_4 = animation_definition_create(
        &sprite_sheet_health_cross_4,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_4 = animation_create(adef_health_cross_4, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_5, "assets/hud/health_cross_5.png", 100, 100);
    adef_health_cross_5 = animation_definition_create(
        &sprite_sheet_health_cross_5,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_5 = animation_create(adef_health_cross_5, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_6, "assets/hud/health_cross_6.png", 100, 100);
    adef_health_cross_6 = animation_definition_create(
        &sprite_sheet_health_cross_6,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_6 = animation_create(adef_health_cross_6, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_7, "assets/hud/health_cross_7.png", 100, 100);
    adef_health_cross_7 = animation_definition_create(
        &sprite_sheet_health_cross_7,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_7 = animation_create(adef_health_cross_7, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_8, "assets/hud/health_cross_8.png", 100, 100);
    adef_health_cross_8 = animation_definition_create(
        &sprite_sheet_health_cross_8,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_8 = animation_create(adef_health_cross_8, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_9, "assets/hud/health_cross_9.png", 100, 100);
    adef_health_cross_9 = animation_definition_create(
        &sprite_sheet_health_cross_9,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_9 = animation_create(adef_health_cross_9, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_10, "assets/hud/health_cross_10.png", 100, 100);
    adef_health_cross_10 = animation_definition_create(
        &sprite_sheet_health_cross_10,
        (f32[]){0.5, 0.5},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    anim_health_cross_10 = animation_create(adef_health_cross_10, true);

    render_sprite_sheet_init(&sprite_sheet_health_cross_11, "assets/hud/health_cross_11.png", 100, 100);
    adef_health_cross_11 = animation_definition_create(
        &sprite_sheet_health_cross_11,
        (f32[]){0.5, 0.5},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    anim_health_cross_11 = animation_create(adef_health_cross_11, true);

    render_sprite_sheet_init(&sprite_sheet_health_cross_12, "assets/hud/health_cross_12.png", 100, 100);
    adef_health_cross_12 = animation_definition_create(
        &sprite_sheet_health_cross_12,
        (f32[]){0.5, 0.5},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    anim_health_cross_12 = animation_create(adef_health_cross_12, true);

    render_sprite_sheet_init(&sprite_sheet_health_cross_13, "assets/hud/health_cross_13.png", 100, 100);
    adef_health_cross_13 = animation_definition_create(
        &sprite_sheet_health_cross_13,
        (f32[]){0.5, 0.5},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    anim_health_cross_13 = animation_create(adef_health_cross_13, true);

    render_sprite_sheet_init(&sprite_sheet_health_cross_14, "assets/hud/health_cross_14.png", 100, 100);
    adef_health_cross_14 = animation_definition_create(
        &sprite_sheet_health_cross_14,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_14 = animation_create(adef_health_cross_14, false);
}

void init_ammo_anims(void)
{
    render_sprite_sheet_init(&sprite_sheet_ammo_0, "assets/hud/0.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_0 = animation_definition_create(
        &sprite_sheet_ammo_0,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_ammo_0 = animation_create(adef_ammo_0, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_1, "assets/hud/1.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_1 = animation_definition_create(
        &sprite_sheet_ammo_1,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_ammo_1 = animation_create(adef_ammo_1, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_2, "assets/hud/2.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_2 = animation_definition_create(
        &sprite_sheet_ammo_2,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_ammo_2 = animation_create(adef_ammo_2, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_3, "assets/hud/3.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_3 = animation_definition_create(
        &sprite_sheet_ammo_3,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_ammo_3 = animation_create(adef_ammo_3, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_4, "assets/hud/4.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_4 = animation_definition_create(
        &sprite_sheet_ammo_4,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_ammo_4 = animation_create(adef_ammo_4, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_5, "assets/hud/5.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_5 = animation_definition_create(
        &sprite_sheet_ammo_5,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_ammo_5 = animation_create(adef_ammo_5, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_6, "assets/hud/6.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_6 = animation_definition_create(
        &sprite_sheet_ammo_6,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_ammo_6 = animation_create(adef_ammo_6, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_7, "assets/hud/7.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_7 = animation_definition_create(
        &sprite_sheet_ammo_7,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_ammo_7 = animation_create(adef_ammo_7, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_8, "assets/hud/8.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_8 = animation_definition_create(
        &sprite_sheet_ammo_8,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_ammo_8 = animation_create(adef_ammo_8, false);

    render_sprite_sheet_init(&sprite_sheet_ammo_9, "assets/hud/9.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_ammo_9 = animation_definition_create(
        &sprite_sheet_ammo_9,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_ammo_9 = animation_create(adef_ammo_9, false);

    render_sprite_sheet_init(&sprite_sheet_forward_slash, "assets/hud/forward_slash.png", DIGIT_WIDTH, DIGIT_HEIGHT);
    adef_forward_slash = animation_definition_create(
        &sprite_sheet_forward_slash,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_forward_slash = animation_create(adef_forward_slash, false);
}

// initializes heads up display
void init_hud(SDL_Window *window)
{
    // init anims used by the hud
    init_health_anims();
    init_ammo_anims();

    // initialize struct
    hud = malloc(sizeof(HUD));
    hud->window = window;

    // init right side of the hud (if there is a second player)
    if (SPLIT_SCREEN)
    {
    }
}

void render_health(SDL_Window *window, u32 texture_slots[32], Player *player, vec2 position)
{
    i16 health = player->health;
    if (health == 100)
    {
        animation_render(anim_health_cross_0, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 93)
    {
        animation_render(anim_health_cross_1, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 86)
    {
        animation_render(anim_health_cross_2, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 79)
    {
        animation_render(anim_health_cross_3, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 72)
    {
        animation_render(anim_health_cross_4, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 65)
    {
        animation_render(anim_health_cross_5, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 58)
    {
        animation_render(anim_health_cross_6, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 51)
    {
        animation_render(anim_health_cross_7, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 44)
    {
        animation_render(anim_health_cross_8, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 37)
    {
        animation_render(anim_health_cross_9, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 30)
    {
        animation_render(anim_health_cross_10, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 23)
    {
        animation_render(anim_health_cross_11, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 16)
    {
        animation_render(anim_health_cross_12, window, position, 0, WHITE, texture_slots);
    }
    else if (health > 0)
    {
        animation_render(anim_health_cross_13, window, position, 0, WHITE, texture_slots);
    }
    else if (health <= 0)
    {
        animation_render(anim_health_cross_14, window, position, 0, WHITE, texture_slots);
    }
}

u16 render_ammo_digit(SDL_Window *window, u32 texture_slots[32], vec2 position, u16 value)
{
    u16 digit = value % 10;

    if (digit == 0)
        animation_render(anim_ammo_0, window, position, 0, WHITE, texture_slots);
    if (digit == 1)
        animation_render(anim_ammo_1, window, position, 1, WHITE, texture_slots);
    if (digit == 2)
        animation_render(anim_ammo_2, window, position, 2, WHITE, texture_slots);
    if (digit == 3)
        animation_render(anim_ammo_3, window, position, 3, WHITE, texture_slots);
    if (digit == 4)
        animation_render(anim_ammo_4, window, position, 4, WHITE, texture_slots);
    if (digit == 5)
        animation_render(anim_ammo_5, window, position, 5, WHITE, texture_slots);
    if (digit == 6)
        animation_render(anim_ammo_6, window, position, 6, WHITE, texture_slots);
    if (digit == 7)
        animation_render(anim_ammo_7, window, position, 7, WHITE, texture_slots);
    if (digit == 8)
        animation_render(anim_ammo_8, window, position, 8, WHITE, texture_slots);
    if (digit == 9)
        animation_render(anim_ammo_9, window, position, 9, WHITE, texture_slots);

    // remove the digit we just rendered and return
    return value / 10;
}

// Renders the ammo display. Renders the digits in each value from left to right
void render_ammo(SDL_Window *window, u32 texture_slots[32], Player *player, vec2 position)
{
    u16 capacity = player->weapon->capacity;
    u16 reserve = player->weapon->reserve;

    // tracks how many digits of each attribute we have written
    u16 reserve_digits = 0;
    u16 capacity_digits = 0;

    // render the player's weapon's ammo icon before numbers if on left side of the screen
    if (player->weapon->hud_ammo_icon && player->is_left_player)
    {
        animation_render(player->weapon->hud_ammo_icon, window, position, 0, WHITE, texture_slots);
        position[0] -= DIGIT_WIDTH + ICON_SPACE; // add a bit of space between icon and the numbers
    }

    // keep rendering digits for the capacity while there are digits left
    while (reserve > 0)
    {
        reserve = render_ammo_digit(window, texture_slots, position, reserve);
        position[0] -= DIGIT_WIDTH;
        reserve_digits++;
    }

    // add trailing 0's to get it up to 3 digits
    while (reserve_digits < 3)
    {
        animation_render(anim_ammo_0, window, position, 0, WHITE, texture_slots);
        position[0] -= DIGIT_WIDTH;
        reserve_digits++;
    }

    // add slash in between reserve and capacity
    animation_render(anim_forward_slash, window, position, 0, WHITE, texture_slots);
    position[0] -= DIGIT_WIDTH;

    // repeat logic for capacity attribute
    while (capacity > 0)
    {
        capacity = render_ammo_digit(window, texture_slots, position, capacity);
        position[0] -= DIGIT_WIDTH;
        capacity_digits++;
    }
    while (capacity_digits < 3)
    {
        animation_render(anim_ammo_0, window, position, 0, WHITE, texture_slots);
        position[0] -= DIGIT_WIDTH;
        capacity_digits++;
    }

    // render the player's weapon's ammo icon after numbers if on right side of the screen
    if (player->weapon->hud_ammo_icon && !player->is_left_player)
    {
        position[0] -= ICON_SPACE;
        animation_render(player->weapon->hud_ammo_icon, window, position, 0, WHITE, texture_slots);
        position[0] -= DIGIT_WIDTH; // add a bit of space between icon and the numbers
    }
}

// frees the dynamic hud memory
void free_hud(void)
{
    if (hud)
        free(hud);
}

// renders the heads up display (should be called once per frame)
void render_hud(SDL_Window *window, u32 texture_slots[32])
{
    // render player one displays (health + ammo)
    render_health(window, texture_slots, player_one, (vec2){50, (window_height * DEFAULT_RENDER_SCALE_FACTOR) - 50});
    render_ammo(window, texture_slots, player_one, (vec2){0.5 * DIGIT_WIDTH + DIGIT_WIDTH * 7 + ICON_SPACE, 0.5 * DIGIT_HEIGHT});
    if (player_one->crosshair->entity->is_active)
    {
        vec2 animation_position;
        animation_position[0] = player_one->crosshair->percentage_of_screen[0] * render_width;
        animation_position[1] = player_one->crosshair->percentage_of_screen[1] * render_height;
        if (SPLIT_SCREEN)
            animation_position[0] *= 0.5; // render width on the left side of the screen will be half the render width of the hud
        animation_render(player_one->crosshair->entity->animation, window, animation_position, 0, WHITE, texture_slots);
    }
    // render player two displays if relevant
    if (SPLIT_SCREEN)
    {
        render_health(window, texture_slots, player_two, (vec2){window_width - 50, window_height - 50});
        render_ammo(window, texture_slots, player_two, (vec2){window_width - 0.5 * DIGIT_WIDTH, 0.5 * DIGIT_HEIGHT});
        if (player_two->crosshair->entity->is_active)
        {
            animation_render(player_two->crosshair->entity->animation, window, (vec2){player_two->crosshair->percentage_of_screen[0] * 0.5 * render_width + 0.5 * render_width, player_two->crosshair->percentage_of_screen[1] * render_height}, 0, WHITE, texture_slots);
        }
    }
}
