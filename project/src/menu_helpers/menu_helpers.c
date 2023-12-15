#include "menu_helpers.h"
#include "../engine/util.h"
#include <string.h>

void init_letter_hashmap(void)
{
    letter_anim_map = create_hash_map(LETTER_ANIM_COUNT);
    insert(letter_anim_map, "A", anim_A);
    insert(letter_anim_map, "B", anim_B);
    insert(letter_anim_map, "C", anim_C);
    insert(letter_anim_map, "D", anim_D);
    insert(letter_anim_map, "E", anim_E);
    insert(letter_anim_map, "F", anim_F);
    insert(letter_anim_map, "G", anim_G);
    insert(letter_anim_map, "H", anim_H);
    insert(letter_anim_map, "I", anim_I);
    insert(letter_anim_map, "J", anim_J);
    insert(letter_anim_map, "K", anim_K);
    insert(letter_anim_map, "L", anim_L);
    insert(letter_anim_map, "M", anim_M);
    insert(letter_anim_map, "N", anim_N);
    insert(letter_anim_map, "O", anim_O);
    insert(letter_anim_map, "P", anim_P);
    insert(letter_anim_map, "Q", anim_Q);
    insert(letter_anim_map, "R", anim_R);
    insert(letter_anim_map, "S", anim_S);
    insert(letter_anim_map, "T", anim_T);
    insert(letter_anim_map, "U", anim_U);
    insert(letter_anim_map, "V", anim_V);
    insert(letter_anim_map, "W", anim_W);
    insert(letter_anim_map, "X", anim_X);
    insert(letter_anim_map, "Y", anim_Y);
    insert(letter_anim_map, "Z", anim_Z);
}

void init_letter_anims(void)
{
    render_sprite_sheet_init(&sprite_sheet_A, "assets/letters/A.png", 40, 50);
    adef_A = animation_definition_create(
        &sprite_sheet_A,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_A = animation_create(adef_A, false);

    render_sprite_sheet_init(&sprite_sheet_B, "assets/letters/B.png", 40, 50);
    adef_B = animation_definition_create(
        &sprite_sheet_B,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_B = animation_create(adef_B, false);

    render_sprite_sheet_init(&sprite_sheet_C, "assets/letters/C.png", 40, 50);
    adef_C = animation_definition_create(
        &sprite_sheet_C,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_C = animation_create(adef_C, false);

    render_sprite_sheet_init(&sprite_sheet_D, "assets/letters/D.png", 40, 50);
    adef_D = animation_definition_create(
        &sprite_sheet_D,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_D = animation_create(adef_D, false);

    render_sprite_sheet_init(&sprite_sheet_E, "assets/letters/E.png", 40, 50);
    adef_E = animation_definition_create(
        &sprite_sheet_E,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_E = animation_create(adef_E, false);

    render_sprite_sheet_init(&sprite_sheet_F, "assets/letters/F.png", 40, 50);
    adef_F = animation_definition_create(
        &sprite_sheet_F,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_F = animation_create(adef_F, false);

    render_sprite_sheet_init(&sprite_sheet_G, "assets/letters/G.png", 40, 50);
    adef_G = animation_definition_create(
        &sprite_sheet_G,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_G = animation_create(adef_G, false);

    render_sprite_sheet_init(&sprite_sheet_H, "assets/letters/H.png", 40, 50);
    adef_H = animation_definition_create(
        &sprite_sheet_H,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_H = animation_create(adef_H, false);

    render_sprite_sheet_init(&sprite_sheet_I, "assets/letters/I.png", 40, 50);
    adef_I = animation_definition_create(
        &sprite_sheet_I,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_I = animation_create(adef_I, false);

    render_sprite_sheet_init(&sprite_sheet_J, "assets/letters/J.png", 40, 50);
    adef_J = animation_definition_create(
        &sprite_sheet_J,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_J = animation_create(adef_J, false);

    render_sprite_sheet_init(&sprite_sheet_K, "assets/letters/K.png", 40, 50);
    adef_K = animation_definition_create(
        &sprite_sheet_K,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_K = animation_create(adef_K, false);

    render_sprite_sheet_init(&sprite_sheet_L, "assets/letters/L.png", 40, 50);
    adef_L = animation_definition_create(
        &sprite_sheet_L,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_L = animation_create(adef_L, false);

    render_sprite_sheet_init(&sprite_sheet_M, "assets/letters/M.png", 40, 50);
    adef_M = animation_definition_create(
        &sprite_sheet_M,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_M = animation_create(adef_M, false);

    render_sprite_sheet_init(&sprite_sheet_N, "assets/letters/N.png", 40, 50);
    adef_N = animation_definition_create(
        &sprite_sheet_N,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_N = animation_create(adef_N, false);

    render_sprite_sheet_init(&sprite_sheet_O, "assets/letters/O.png", 40, 50);
    adef_O = animation_definition_create(
        &sprite_sheet_O,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_O = animation_create(adef_O, false);

    render_sprite_sheet_init(&sprite_sheet_P, "assets/letters/P.png", 40, 50);
    adef_P = animation_definition_create(
        &sprite_sheet_P,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_P = animation_create(adef_P, false);

    render_sprite_sheet_init(&sprite_sheet_Q, "assets/letters/Q.png", 40, 50);
    adef_Q = animation_definition_create(
        &sprite_sheet_Q,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_Q = animation_create(adef_Q, false);

    render_sprite_sheet_init(&sprite_sheet_R, "assets/letters/R.png", 40, 50);
    adef_R = animation_definition_create(
        &sprite_sheet_R,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_R = animation_create(adef_R, false);

    render_sprite_sheet_init(&sprite_sheet_S, "assets/letters/S.png", 40, 50);
    adef_S = animation_definition_create(
        &sprite_sheet_S,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_S = animation_create(adef_S, false);

    render_sprite_sheet_init(&sprite_sheet_T, "assets/letters/T.png", 40, 50);
    adef_T = animation_definition_create(
        &sprite_sheet_T,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_T = animation_create(adef_T, false);
    render_sprite_sheet_init(&sprite_sheet_U, "assets/letters/U.png", 40, 50);
    adef_U = animation_definition_create(
        &sprite_sheet_U,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_U = animation_create(adef_U, false);

    render_sprite_sheet_init(&sprite_sheet_V, "assets/letters/V.png", 40, 50);
    adef_V = animation_definition_create(
        &sprite_sheet_V,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_V = animation_create(adef_V, false);

    render_sprite_sheet_init(&sprite_sheet_W, "assets/letters/W.png", 40, 50);
    adef_W = animation_definition_create(
        &sprite_sheet_W,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_W = animation_create(adef_W, false);

    render_sprite_sheet_init(&sprite_sheet_X, "assets/letters/X.png", 40, 50);
    adef_X = animation_definition_create(
        &sprite_sheet_X,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_X = animation_create(adef_X, false);

    render_sprite_sheet_init(&sprite_sheet_Y, "assets/letters/Y.png", 40, 50);
    adef_Y = animation_definition_create(
        &sprite_sheet_Y,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_Y = animation_create(adef_Y, false);

    render_sprite_sheet_init(&sprite_sheet_Z, "assets/letters/Z.png", 40, 50);
    adef_Z = animation_definition_create(
        &sprite_sheet_Z,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_Z = animation_create(adef_Z, false);
}

void init_menu_structs(void)
{
    // Allocate memory for Menu structure
    pause_menu = malloc(sizeof(Menu));

    // Initialize other fields
    pause_menu->items_count = 3;
    pause_menu->selected_item = 0;

    // Initialize each menu item
    snprintf(pause_menu->items[0], MENU_MAX_LINE_LENGTH, "TEST LINE ITEM ONE");
    snprintf(pause_menu->items[1], MENU_MAX_LINE_LENGTH, "SECOND MENU LINE ITEM");
    snprintf(pause_menu->items[2], MENU_MAX_LINE_LENGTH, "MENU LINE ITEM THREE");
}

void free_menus(void)
{
    free(pause_menu);
}

// initializes all menu-related assets at game start up
void init_menus(void)
{
    init_letter_anims();
    init_letter_hashmap();
    init_menu_structs();
}

// renders a line of text letter by letter starting at the specified positon on the screen
void render_text_line(SDL_Window *window, u32 texture_slots[32], char *text, vec2 starting_position)
{
    char *character = text;

    // loop through each character in the input string
    while (*character != '\0')
    {
        if (*character != ' ')
        {
            // render associated anim
            Animation *char_anim = get(letter_anim_map, (char[]){*character, '\0'});
            animation_render(char_anim, window, starting_position, 0, WHITE, texture_slots);
        }

        // update the starting position and go to next character
        vec2_add(starting_position, starting_position, (vec2){LETTER_WIDTH, 0});
        character++;
    }
}

void render_main_menu(void)
{
    return;
}

void render_game_mode_menu(void)
{
    return;
}

void render_map_select_menu(void)
{
    return;
}

void render_pause_menu(SDL_Window *window, u32 texture_slots[32])
{
    for (int i = 0; i < pause_menu->items_count; i++)
    {
        printf("i: %d\n", i);
        render_text_line(window, texture_slots, "SOME TEXT", (vec2){window_width / 2, window_height / 2});
    }
}