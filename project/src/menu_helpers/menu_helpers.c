#include "menu_helpers.h"
#include "../engine/util.h"
#include "../main_helpers/main_helpers.h"
#include <string.h>

int game_state;

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

void init_menu_anims(void)
{
    // CAPITAL LETTERS
    render_sprite_sheet_init(&sprite_sheet_A, "assets/letters/A.png", 40, 50);
    adef_A = animation_definition_create(&sprite_sheet_A, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_A = animation_create(adef_A, false);

    render_sprite_sheet_init(&sprite_sheet_B, "assets/letters/B.png", 40, 50);
    adef_B = animation_definition_create(&sprite_sheet_B, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_B = animation_create(adef_B, false);

    render_sprite_sheet_init(&sprite_sheet_C, "assets/letters/C.png", 40, 50);
    adef_C = animation_definition_create(&sprite_sheet_C, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_C = animation_create(adef_C, false);

    render_sprite_sheet_init(&sprite_sheet_D, "assets/letters/D.png", 40, 50);
    adef_D = animation_definition_create(&sprite_sheet_D, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_D = animation_create(adef_D, false);

    render_sprite_sheet_init(&sprite_sheet_E, "assets/letters/E.png", 40, 50);
    adef_E = animation_definition_create(&sprite_sheet_E, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_E = animation_create(adef_E, false);

    render_sprite_sheet_init(&sprite_sheet_F, "assets/letters/F.png", 40, 50);
    adef_F = animation_definition_create(&sprite_sheet_F, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_F = animation_create(adef_F, false);

    render_sprite_sheet_init(&sprite_sheet_G, "assets/letters/G.png", 40, 50);
    adef_G = animation_definition_create(&sprite_sheet_G, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_G = animation_create(adef_G, false);

    render_sprite_sheet_init(&sprite_sheet_H, "assets/letters/H.png", 40, 50);
    adef_H = animation_definition_create(&sprite_sheet_H, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_H = animation_create(adef_H, false);

    render_sprite_sheet_init(&sprite_sheet_I, "assets/letters/I.png", 40, 50);
    adef_I = animation_definition_create(&sprite_sheet_I, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_I = animation_create(adef_I, false);

    render_sprite_sheet_init(&sprite_sheet_J, "assets/letters/J.png", 40, 50);
    adef_J = animation_definition_create(&sprite_sheet_J, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_J = animation_create(adef_J, false);

    render_sprite_sheet_init(&sprite_sheet_K, "assets/letters/K.png", 40, 50);
    adef_K = animation_definition_create(&sprite_sheet_K, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_K = animation_create(adef_K, false);

    render_sprite_sheet_init(&sprite_sheet_L, "assets/letters/L.png", 40, 50);
    adef_L = animation_definition_create(&sprite_sheet_L, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_L = animation_create(adef_L, false);

    render_sprite_sheet_init(&sprite_sheet_M, "assets/letters/M.png", 40, 50);
    adef_M = animation_definition_create(&sprite_sheet_M, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_M = animation_create(adef_M, false);

    render_sprite_sheet_init(&sprite_sheet_N, "assets/letters/N.png", 40, 50);
    adef_N = animation_definition_create(&sprite_sheet_N, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_N = animation_create(adef_N, false);

    render_sprite_sheet_init(&sprite_sheet_O, "assets/letters/O.png", 40, 50);
    adef_O = animation_definition_create(&sprite_sheet_O, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_O = animation_create(adef_O, false);

    render_sprite_sheet_init(&sprite_sheet_P, "assets/letters/P.png", 40, 50);
    adef_P = animation_definition_create(&sprite_sheet_P, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_P = animation_create(adef_P, false);

    render_sprite_sheet_init(&sprite_sheet_Q, "assets/letters/Q.png", 40, 50);
    adef_Q = animation_definition_create(&sprite_sheet_Q, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_Q = animation_create(adef_Q, false);

    render_sprite_sheet_init(&sprite_sheet_R, "assets/letters/R.png", 40, 50);
    adef_R = animation_definition_create(&sprite_sheet_R, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_R = animation_create(adef_R, false);

    render_sprite_sheet_init(&sprite_sheet_S, "assets/letters/S.png", 40, 50);
    adef_S = animation_definition_create(&sprite_sheet_S, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_S = animation_create(adef_S, false);

    render_sprite_sheet_init(&sprite_sheet_T, "assets/letters/T.png", 40, 50);
    adef_T = animation_definition_create(&sprite_sheet_T, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_T = animation_create(adef_T, false);
    render_sprite_sheet_init(&sprite_sheet_U, "assets/letters/U.png", 40, 50);
    adef_U = animation_definition_create(&sprite_sheet_U, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_U = animation_create(adef_U, false);

    render_sprite_sheet_init(&sprite_sheet_V, "assets/letters/V.png", 40, 50);
    adef_V = animation_definition_create(&sprite_sheet_V, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_V = animation_create(adef_V, false);

    render_sprite_sheet_init(&sprite_sheet_W, "assets/letters/W.png", 40, 50);
    adef_W = animation_definition_create(&sprite_sheet_W, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_W = animation_create(adef_W, false);

    render_sprite_sheet_init(&sprite_sheet_X, "assets/letters/X.png", 40, 50);
    adef_X = animation_definition_create(&sprite_sheet_X, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_X = animation_create(adef_X, false);

    render_sprite_sheet_init(&sprite_sheet_Y, "assets/letters/Y.png", 40, 50);
    adef_Y = animation_definition_create(&sprite_sheet_Y, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_Y = animation_create(adef_Y, false);

    render_sprite_sheet_init(&sprite_sheet_Z, "assets/letters/Z.png", 40, 50);
    adef_Z = animation_definition_create(&sprite_sheet_Z, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_Z = animation_create(adef_Z, false);

    // SELECTED ITEM INDICATORS
    render_sprite_sheet_init(&sprite_sheet_selected_bracket_left, "assets/menus/selected_bracket_left.png", 62, 62);
    adef_selected_bracket_left = animation_definition_create(
        &sprite_sheet_selected_bracket_left,
        (f32[]){0.005, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        11);
    anim_selected_bracket_left = animation_create(adef_selected_bracket_left, false);
    anim_selected_bracket_left->is_active = false;

    render_sprite_sheet_init(&sprite_sheet_selected_bracket_right, "assets/menus/selected_bracket_right.png", 62, 62);
    adef_selected_bracket_right = animation_definition_create(
        &sprite_sheet_selected_bracket_right,
        (f32[]){0.005, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005, 0.005},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        11);
    anim_selected_bracket_right = animation_create(adef_selected_bracket_right, false);
    anim_selected_bracket_right->is_active = false;
}

void free_menus(void) { free(pause_menu); }

// renders a line of text letter by letter starting at the specified positon on
// the screen
void render_text_line(SDL_Window *window, u32 texture_slots[32], char *text, vec2 starting_position)
{
    char *character = text;

    // loop through each character in the input string
    while (*character != '\0') {
        if (*character != ' ') {
            // render associated anim
            Animation *char_anim = get(letter_anim_map, (char[]){*character, '\0'});
            animation_render(char_anim, window, starting_position, WHITE, texture_slots);
        }

        // update the starting position and go to next character
        vec2_add(starting_position, starting_position, (vec2){LETTER_WIDTH, 0});
        character++;
    }
    // back track by half a character to leave the "cursor" at the exact end
    // of the last letter animation
    vec2_add(starting_position, starting_position, (vec2){LETTER_WIDTH * -0.5, 0});
}

void reset_selector_anims(void)
{
    anim_selected_bracket_left->current_frame_index = 0;
    anim_selected_bracket_right->current_frame_index = 0;
    anim_selected_bracket_left->is_active = false;
    anim_selected_bracket_right->is_active = false;
}

void render_menu_item(SDL_Window *window, u32 texture_slots[32], char *text, vec2 starting_position, bool is_selected)
{
    // if selected render left bracket anim
    if (is_selected)
        animation_render(anim_selected_bracket_left, window, starting_position, WHITE, texture_slots);

    // render the item's text
    vec2_add(starting_position, starting_position, (vec2){(SELECTED_ANIM_WIDTH * 0.5) + (LETTER_WIDTH * 0.5), 0});
    render_text_line(window, texture_slots, text, starting_position);

    // if selected render left bracket anim
    if (is_selected) {
        vec2_add(starting_position, starting_position, (vec2){(SELECTED_ANIM_WIDTH * 0.5), 0});
        animation_render(anim_selected_bracket_right, window, starting_position, WHITE, texture_slots);
    }
}

void update_menu(Menu *menu, Input_State input)
{
    if (input.down == KS_PRESSED && menu->selected_item < menu->items_count - 1) {
        reset_selector_anims();
        menu->selected_item++;
    }
    else if (input.up == KS_PRESSED && menu->selected_item > 0) {
        reset_selector_anims();
        menu->selected_item--;
    }
    else if (input.use == KS_PRESSED) {
        menu->input_handler();
    }
}

void render_main_menu(SDL_Window *window, u32 texture_slots[32])
{
    for (int i = 0; i < main_menu->items_count; i++) {
        render_menu_item(
            window,
            texture_slots,
            main_menu->items[i],
            (vec2){SELECTED_ANIM_WIDTH * 0.5, render_height - SELECTED_ANIM_HEIGHT * 0.5 - i * SELECTED_ANIM_HEIGHT},
            main_menu->selected_item == i);
    }
}

void handle_main_menu_input(void)
{
    switch (main_menu->selected_item) {
    case 0:
        game_state = GS_GAME_MODE_MENU;
        break;
    case 1:
        game_state = GS_EXITING;
        break;
    default:
        ERROR_EXIT("Got unexpected case on pause menu: %d\n", main_menu->selected_item);
    }
}

void render_mode_menu(SDL_Window *window, u32 texture_slots[32])
{
    for (int i = 0; i < mode_menu->items_count; i++) {
        render_menu_item(
            window,
            texture_slots,
            mode_menu->items[i],
            (vec2){SELECTED_ANIM_WIDTH * 0.5, render_height - SELECTED_ANIM_HEIGHT * 0.5 - i * SELECTED_ANIM_HEIGHT},
            mode_menu->selected_item == i);
    }
}

void handle_mode_menu_input(void)
{
    switch (mode_menu->selected_item) {
    case 0:
        game_state = GS_RUNNING;
        break;
    case 1:
        game_state = GS_SURVIVAL_MENU;
        break;
    default:
        ERROR_EXIT("Got unexpected case on pause menu: %d\n", mode_menu->selected_item);
    }
}

void render_survival_menu(SDL_Window *window, u32 texture_slots[32])
{
    for (int i = 0; i < survival_menu->items_count; i++) {
        render_menu_item(
            window,
            texture_slots,
            survival_menu->items[i],
            (vec2){SELECTED_ANIM_WIDTH * 0.5, render_height - SELECTED_ANIM_HEIGHT * 0.5 - i * SELECTED_ANIM_HEIGHT},
            survival_menu->selected_item == i);
    }
}

void handle_survival_menu_input(void)
{
    switch (survival_menu->selected_item) {
    case 0:
        game_state = GS_RUNNING;
        break;
    default:
        ERROR_EXIT("Got unexpected case on pause menu: %d\n", survival_menu->selected_item);
    }
}

void render_pause_menu(SDL_Window *window, u32 texture_slots[32])
{
    for (int i = 0; i < pause_menu->items_count; i++) {
        render_menu_item(
            window,
            texture_slots,
            pause_menu->items[i],
            (vec2){SELECTED_ANIM_WIDTH * 0.5, render_height - SELECTED_ANIM_HEIGHT * 0.5 - i * SELECTED_ANIM_HEIGHT},
            pause_menu->selected_item == i);
    }
}

void handle_pause_menu_input(void)
{
    switch (pause_menu->selected_item) {
    case 0:
        game_state = GS_RUNNING;
        break;
    case 1:
        game_state = GS_MAIN_MENU;
        break;
    default:
        ERROR_EXIT("Got unexpected case on pause menu: %d\n", pause_menu->selected_item);
    }
}

/// @brief Smoothly transitions the game's color between WHITE and GREYED_OUT
/// when the game state switches between GS_PAUSE_MENU and GS_RUNNING
/// @param game_color the game's current color
void update_game_color(vec4 game_color)
{
    if (game_state == GS_RUNNING) {
        if (vec4_color_cmp(game_color,
                           WHITE)) { // game color RGB is less than WHITE
            vec4_add(game_color, game_color, (vec4){COLOR_DELTA, COLOR_DELTA, COLOR_DELTA, 0});
        }
        else if (!vec4_is_equal(
                     game_color,
                     WHITE)) { // game color RGB is somehow greater than
                               // WHITE
            vec4_dup(game_color, WHITE);
        }
    }
    if (game_state == GS_PAUSE_MENU) {
        if (vec4_color_cmp(
                GREYED_OUT,
                game_color)) { // game color RGB is greater than
                               // GREYED_OUT
            vec4_add(game_color, game_color, (vec4){-COLOR_DELTA, -COLOR_DELTA, -COLOR_DELTA, 0});
        }
        else if (!vec4_is_equal(
                     game_color,
                     GREYED_OUT)) { // game color RGB is somehow
                                    // less than GREYED_OUT
            vec4_dup(game_color, GREYED_OUT);
        }
    }
}

/// @brief Initializes all menu structures used by the game
/// @param
void init_menu_structs(void)
{
    // MAIN MENU
    main_menu = malloc(sizeof(Menu));
    main_menu->input_handler = handle_main_menu_input;
    main_menu->items_count = 2;
    main_menu->selected_item = 0;
    snprintf(main_menu->items[0], MENU_MAX_LINE_LENGTH, "START");
    snprintf(main_menu->items[1], MENU_MAX_LINE_LENGTH, "EXIT");

    // MODE SELECT MENU
    mode_menu = malloc(sizeof(Menu));
    mode_menu->input_handler = handle_mode_menu_input;
    mode_menu->items_count = 2;
    mode_menu->selected_item = 0;
    snprintf(mode_menu->items[0], MENU_MAX_LINE_LENGTH, "CAMPAIGN");
    snprintf(mode_menu->items[1], MENU_MAX_LINE_LENGTH, "SURVIVAL");

    // SURVIVAL MENU
    survival_menu = malloc(sizeof(Menu));
    survival_menu->input_handler = handle_survival_menu_input;
    survival_menu->items_count = 1;
    survival_menu->selected_item = 0;
    snprintf(survival_menu->items[0], MENU_MAX_LINE_LENGTH, "DEMO");

    // PAUSE MENU
    pause_menu = malloc(sizeof(Menu));
    pause_menu->input_handler = handle_pause_menu_input;
    pause_menu->items_count = 2;
    pause_menu->selected_item = 0;
    snprintf(pause_menu->items[0], MENU_MAX_LINE_LENGTH, "RESUME");
    snprintf(pause_menu->items[1], MENU_MAX_LINE_LENGTH, "EXIT TO MAIN MENU");
}

/// @brief Wrapper method for all menu-related initialization methods
/// @param
void init_menus(void)
{
    init_menu_anims();
    init_letter_hashmap();
    init_menu_structs();
}