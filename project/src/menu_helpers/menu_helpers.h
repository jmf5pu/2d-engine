#ifndef MENU_HELPERS_H
#define MENU_HELPERS_H

#include "../engine/animation.h"
#include "../engine/hash_map.h"
#include "../engine/input/input.h"
#include "../engine/render.h"
#include "../structs.h"

#define LETTER_ANIM_COUNT 26
#define LETTER_WIDTH 5
#define LETTER_HEIGHT 7
#define LETTER_SPACING 1
#define LINE_SPACING 2
#define SELECTED_ANIM_WIDTH 7
#define SELECTED_ANIM_HEIGHT 7
#define COLOR_DELTA 0.05

// used to determine when to render (or not render) whichS menus
enum Game_State {
    GS_MAIN_MENU,
    GS_GAME_MODE_MENU,
    GS_SURVIVAL_MENU,
    GS_PAUSE_MENU,
    GS_RUNNING,
    GS_EXITING,
};

// CAPITAL LETTERS
Sprite_Sheet sprite_sheet_A;
Sprite_Sheet sprite_sheet_B;
Sprite_Sheet sprite_sheet_C;
Sprite_Sheet sprite_sheet_D;
Sprite_Sheet sprite_sheet_E;
Sprite_Sheet sprite_sheet_F;
Sprite_Sheet sprite_sheet_G;
Sprite_Sheet sprite_sheet_H;
Sprite_Sheet sprite_sheet_I;
Sprite_Sheet sprite_sheet_J;
Sprite_Sheet sprite_sheet_K;
Sprite_Sheet sprite_sheet_L;
Sprite_Sheet sprite_sheet_M;
Sprite_Sheet sprite_sheet_N;
Sprite_Sheet sprite_sheet_O;
Sprite_Sheet sprite_sheet_P;
Sprite_Sheet sprite_sheet_Q;
Sprite_Sheet sprite_sheet_R;
Sprite_Sheet sprite_sheet_S;
Sprite_Sheet sprite_sheet_T;
Sprite_Sheet sprite_sheet_U;
Sprite_Sheet sprite_sheet_V;
Sprite_Sheet sprite_sheet_W;
Sprite_Sheet sprite_sheet_X;
Sprite_Sheet sprite_sheet_Y;
Sprite_Sheet sprite_sheet_Z;

Animation_Definition *adef_A;
Animation_Definition *adef_B;
Animation_Definition *adef_C;
Animation_Definition *adef_D;
Animation_Definition *adef_E;
Animation_Definition *adef_F;
Animation_Definition *adef_G;
Animation_Definition *adef_H;
Animation_Definition *adef_I;
Animation_Definition *adef_J;
Animation_Definition *adef_K;
Animation_Definition *adef_L;
Animation_Definition *adef_M;
Animation_Definition *adef_N;
Animation_Definition *adef_O;
Animation_Definition *adef_P;
Animation_Definition *adef_Q;
Animation_Definition *adef_R;
Animation_Definition *adef_S;
Animation_Definition *adef_T;
Animation_Definition *adef_U;
Animation_Definition *adef_V;
Animation_Definition *adef_W;
Animation_Definition *adef_X;
Animation_Definition *adef_Y;
Animation_Definition *adef_Z;

Animation *anim_A;
Animation *anim_B;
Animation *anim_C;
Animation *anim_D;
Animation *anim_E;
Animation *anim_F;
Animation *anim_G;
Animation *anim_H;
Animation *anim_I;
Animation *anim_J;
Animation *anim_K;
Animation *anim_L;
Animation *anim_M;
Animation *anim_N;
Animation *anim_O;
Animation *anim_P;
Animation *anim_Q;
Animation *anim_R;
Animation *anim_S;
Animation *anim_T;
Animation *anim_U;
Animation *anim_V;
Animation *anim_W;
Animation *anim_X;
Animation *anim_Y;
Animation *anim_Z;

Hash_Map *letter_anim_map;

// SELECTED ITEM INDICATORS
Sprite_Sheet sprite_sheet_selected_bracket_left;
Sprite_Sheet sprite_sheet_selected_bracket_right;

Animation_Definition *adef_selected_bracket_left;
Animation_Definition *adef_selected_bracket_right;

Animation *anim_selected_bracket_left;
Animation *anim_selected_bracket_right;

// MENUS
Menu *main_menu;
Menu *mode_menu;
Menu *survival_menu;
Menu *pause_menu;

extern int game_state;

void render_menu(Menu *menu);
void init_menus(void);
void reset_selector_anims(void);
void update_menu(Menu *menu, Input_State input);
void handle_main_menu_input(void);
void handle_mode_menu_input(void);
void handle_survival_menu_input(void);
void handle_pause_menu_input(void);
void update_game_color(vec4 game_color);
void free_menus(void);

#endif