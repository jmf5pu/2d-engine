#include "hud.h"

HUD *hud;

void init_health_anims(void)
{
    render_sprite_sheet_init(&sprite_sheet_health_cross_0, "assets/health_cross_0.png", 100, 100);
    adef_health_cross_0 = animation_definition_create(
        &sprite_sheet_health_cross_0,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_0 = animation_create(adef_health_cross_0, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_1, "assets/health_cross_1.png", 100, 100);
    adef_health_cross_1 = animation_definition_create(
        &sprite_sheet_health_cross_1,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_1 = animation_create(adef_health_cross_1, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_2, "assets/health_cross_2.png", 100, 100);
    adef_health_cross_2 = animation_definition_create(
        &sprite_sheet_health_cross_2,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_2 = animation_create(adef_health_cross_2, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_3, "assets/health_cross_3.png", 100, 100);
    adef_health_cross_3 = animation_definition_create(
        &sprite_sheet_health_cross_3,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_3 = animation_create(adef_health_cross_3, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_4, "assets/health_cross_4.png", 100, 100);
    adef_health_cross_4 = animation_definition_create(
        &sprite_sheet_health_cross_4,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_4 = animation_create(adef_health_cross_4, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_5, "assets/health_cross_5.png", 100, 100);
    adef_health_cross_5 = animation_definition_create(
        &sprite_sheet_health_cross_5,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_5 = animation_create(adef_health_cross_5, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_6, "assets/health_cross_6.png", 100, 100);
    adef_health_cross_6 = animation_definition_create(
        &sprite_sheet_health_cross_6,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_6 = animation_create(adef_health_cross_6, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_7, "assets/health_cross_7.png", 100, 100);
    adef_health_cross_7 = animation_definition_create(
        &sprite_sheet_health_cross_7,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_7 = animation_create(adef_health_cross_7, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_8, "assets/health_cross_8.png", 100, 100);
    adef_health_cross_8 = animation_definition_create(
        &sprite_sheet_health_cross_8,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_8 = animation_create(adef_health_cross_8, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_9, "assets/health_cross_9.png", 100, 100);
    adef_health_cross_9 = animation_definition_create(
        &sprite_sheet_health_cross_9,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_9 = animation_create(adef_health_cross_9, false);

    render_sprite_sheet_init(&sprite_sheet_health_cross_10, "assets/health_cross_10.png", 100, 100);
    adef_health_cross_10 = animation_definition_create(
        &sprite_sheet_health_cross_10,
        (f32[]){0.5, 0.5},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    anim_health_cross_10 = animation_create(adef_health_cross_10, true);

    render_sprite_sheet_init(&sprite_sheet_health_cross_11, "assets/health_cross_11.png", 100, 100);
    adef_health_cross_11 = animation_definition_create(
        &sprite_sheet_health_cross_11,
        (f32[]){0.5, 0.5},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    anim_health_cross_11 = animation_create(adef_health_cross_11, true);

    render_sprite_sheet_init(&sprite_sheet_health_cross_12, "assets/health_cross_12.png", 100, 100);
    adef_health_cross_12 = animation_definition_create(
        &sprite_sheet_health_cross_12,
        (f32[]){0.5, 0.5},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    anim_health_cross_12 = animation_create(adef_health_cross_12, true);

    render_sprite_sheet_init(&sprite_sheet_health_cross_13, "assets/health_cross_13.png", 100, 100);
    adef_health_cross_13 = animation_definition_create(
        &sprite_sheet_health_cross_13,
        (f32[]){0.5, 0.5},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    anim_health_cross_13 = animation_create(adef_health_cross_13, true);

    render_sprite_sheet_init(&sprite_sheet_health_cross_14, "assets/health_cross_14.png", 100, 100);
    adef_health_cross_14 = animation_definition_create(
        &sprite_sheet_health_cross_14,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_health_cross_14 = animation_create(adef_health_cross_14, false);
}

// initializes heads up display
void init_hud(SDL_Window *window)
{
    // init anims used by the hud
    init_health_anims();

    // initialize struct
    hud = malloc(sizeof(HUD));
    hud->window = window;

    // init right side of the hud (if there is a second player)
    if (SPLIT_SCREEN)
    {
    }
}

// renders the heads up display (should be called once per frame)
// void render_hud()
// {
//     // render health displays
//     render_sprite_sheet_frame(prop.sprite->sprite_sheet, window, prop.sprite->row, prop.sprite->column, prop.sprite->position, z_index, prop.sprite->is_flipped, RENDER_PHYSICS_BODIES ? (vec4){0.9, 0.9, 0.9, 0.9} : prop.sprite->color, texture_slots);
// }

void render_health(SDL_Window *window, u32 texture_slots[32])
{
    i16 p1_health = player_one->health;
    if (p1_health == 100)
    {
        animation_render(anim_health_cross_0, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 93)
    {
        animation_render(anim_health_cross_1, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 86)
    {
        animation_render(anim_health_cross_2, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 79)
    {
        animation_render(anim_health_cross_3, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 72)
    {
        animation_render(anim_health_cross_4, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 65)
    {
        animation_render(anim_health_cross_5, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 58)
    {
        animation_render(anim_health_cross_6, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 51)
    {
        animation_render(anim_health_cross_7, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 44)
    {
        animation_render(anim_health_cross_8, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 37)
    {
        animation_render(anim_health_cross_9, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 30)
    {
        animation_render(anim_health_cross_10, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 23)
    {
        animation_render(anim_health_cross_11, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 16)
    {
        animation_render(anim_health_cross_12, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health > 0)
    {
        animation_render(anim_health_cross_13, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
    else if (p1_health <= 0)
    {
        animation_render(anim_health_cross_14, window, (vec2){50, window_height - 50}, 0, WHITE, texture_slots);
    }
}

// frees the dynamic hud memory
void free_hud(void)
{
    if (hud)
        free(hud);
}