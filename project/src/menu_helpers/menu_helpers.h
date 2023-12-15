#ifndef MENU_HELPERS_H
#define MENU_HELPERS_H

#include "../engine/render.h"
#include "../engine/hash_map.h"
#include "../engine/animation.h"
#include "../structs.h"

#define LETTER_ANIM_COUNT 26
#define LETTER_WIDTH 40
#define LETTER_HEIGHT 50

Hash_Map * letter_anim_map;

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

Animation_Definition * adef_A;
Animation_Definition * adef_B;
Animation_Definition * adef_C;
Animation_Definition * adef_D;
Animation_Definition * adef_E;
Animation_Definition * adef_F;
Animation_Definition * adef_G;
Animation_Definition * adef_H;
Animation_Definition * adef_I;
Animation_Definition * adef_J;
Animation_Definition * adef_K;
Animation_Definition * adef_L;
Animation_Definition * adef_M;
Animation_Definition * adef_N;
Animation_Definition * adef_O;
Animation_Definition * adef_P;
Animation_Definition * adef_Q;
Animation_Definition * adef_R;
Animation_Definition * adef_S;
Animation_Definition * adef_T;
Animation_Definition * adef_U;
Animation_Definition * adef_V;
Animation_Definition * adef_W;
Animation_Definition * adef_X;
Animation_Definition * adef_Y;
Animation_Definition * adef_Z;

Animation * anim_A;
Animation * anim_B;
Animation * anim_C;
Animation * anim_D;
Animation * anim_E;
Animation * anim_F;
Animation * anim_G;
Animation * anim_H;
Animation * anim_I;
Animation * anim_J;
Animation * anim_K;
Animation * anim_L;
Animation * anim_M;
Animation * anim_N;
Animation * anim_O;
Animation * anim_P;
Animation * anim_Q;
Animation * anim_R;
Animation * anim_S;
Animation * anim_T;
Animation * anim_U;
Animation * anim_V;
Animation * anim_W;
Animation * anim_X;
Animation * anim_Y;
Animation * anim_Z;

Menu * pause_menu;

void init_menus(void);
void render_main_menu(void);
void render_game_mode_menu(void);
void render_map_select_menu(void);
void render_pause_menu(SDL_Window *window, u32 texture_slots[32]);
void free_menus(void);

#endif