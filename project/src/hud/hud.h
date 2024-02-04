#ifndef HUD_H
#define HUD_H

#include "../engine/hash_map.h"
#include "../engine/render.h"
#include "../engine/util.h"
#include "../player_helpers/player_helpers.h"
#include "../structs.h"

// ammo display
#define DIGIT_WIDTH 20
#define DIGIT_HEIGHT 44
#define ICON_SPACE 10
#define AMMO_ANIM_COUNT 20
#define AMMO_BLINKING_THRESHOLD 0.25 // fraction at which blinking starts

// holds ammo display animations
Hash_Map *ammo_anim_map;

// health display sprite sheets, animation definitions, animations
Sprite_Sheet sprite_sheet_health_cross_0;
Sprite_Sheet sprite_sheet_health_cross_1;
Sprite_Sheet sprite_sheet_health_cross_2;
Sprite_Sheet sprite_sheet_health_cross_3;
Sprite_Sheet sprite_sheet_health_cross_4;
Sprite_Sheet sprite_sheet_health_cross_5;
Sprite_Sheet sprite_sheet_health_cross_6;
Sprite_Sheet sprite_sheet_health_cross_7;
Sprite_Sheet sprite_sheet_health_cross_8;
Sprite_Sheet sprite_sheet_health_cross_9;
Sprite_Sheet sprite_sheet_health_cross_10;
Sprite_Sheet sprite_sheet_health_cross_11;
Sprite_Sheet sprite_sheet_health_cross_12;
Sprite_Sheet sprite_sheet_health_cross_13;
Sprite_Sheet sprite_sheet_health_cross_14;

Animation_Definition *adef_health_cross_0;
Animation_Definition *adef_health_cross_1;
Animation_Definition *adef_health_cross_2;
Animation_Definition *adef_health_cross_3;
Animation_Definition *adef_health_cross_4;
Animation_Definition *adef_health_cross_5;
Animation_Definition *adef_health_cross_6;
Animation_Definition *adef_health_cross_7;
Animation_Definition *adef_health_cross_8;
Animation_Definition *adef_health_cross_9;
Animation_Definition *adef_health_cross_10;
Animation_Definition *adef_health_cross_11;
Animation_Definition *adef_health_cross_12;
Animation_Definition *adef_health_cross_13;
Animation_Definition *adef_health_cross_14;

Animation *anim_health_cross_0;
Animation *anim_health_cross_1;
Animation *anim_health_cross_2;
Animation *anim_health_cross_3;
Animation *anim_health_cross_4;
Animation *anim_health_cross_5;
Animation *anim_health_cross_6;
Animation *anim_health_cross_7;
Animation *anim_health_cross_8;
Animation *anim_health_cross_9;
Animation *anim_health_cross_10;
Animation *anim_health_cross_11;
Animation *anim_health_cross_12;
Animation *anim_health_cross_13;
Animation *anim_health_cross_14;

// ammo display sprite sheets, animation definitions, animations
Sprite_Sheet sprite_sheet_ammo_0;
Sprite_Sheet sprite_sheet_ammo_1;
Sprite_Sheet sprite_sheet_ammo_2;
Sprite_Sheet sprite_sheet_ammo_3;
Sprite_Sheet sprite_sheet_ammo_4;
Sprite_Sheet sprite_sheet_ammo_5;
Sprite_Sheet sprite_sheet_ammo_6;
Sprite_Sheet sprite_sheet_ammo_7;
Sprite_Sheet sprite_sheet_ammo_8;
Sprite_Sheet sprite_sheet_ammo_9;
Sprite_Sheet sprite_sheet_ammo_0_blinking;
Sprite_Sheet sprite_sheet_ammo_1_blinking;
Sprite_Sheet sprite_sheet_ammo_2_blinking;
Sprite_Sheet sprite_sheet_ammo_3_blinking;
Sprite_Sheet sprite_sheet_ammo_4_blinking;
Sprite_Sheet sprite_sheet_ammo_5_blinking;
Sprite_Sheet sprite_sheet_ammo_6_blinking;
Sprite_Sheet sprite_sheet_ammo_7_blinking;
Sprite_Sheet sprite_sheet_ammo_8_blinking;
Sprite_Sheet sprite_sheet_ammo_9_blinking;
Sprite_Sheet sprite_sheet_forward_slash;

Animation_Definition *adef_ammo_0;
Animation_Definition *adef_ammo_1;
Animation_Definition *adef_ammo_2;
Animation_Definition *adef_ammo_3;
Animation_Definition *adef_ammo_4;
Animation_Definition *adef_ammo_5;
Animation_Definition *adef_ammo_6;
Animation_Definition *adef_ammo_7;
Animation_Definition *adef_ammo_8;
Animation_Definition *adef_ammo_9;
Animation_Definition *adef_ammo_0_blinking;
Animation_Definition *adef_ammo_1_blinking;
Animation_Definition *adef_ammo_2_blinking;
Animation_Definition *adef_ammo_3_blinking;
Animation_Definition *adef_ammo_4_blinking;
Animation_Definition *adef_ammo_5_blinking;
Animation_Definition *adef_ammo_6_blinking;
Animation_Definition *adef_ammo_7_blinking;
Animation_Definition *adef_ammo_8_blinking;
Animation_Definition *adef_ammo_9_blinking;
Animation_Definition *adef_forward_slash;

Animation *anim_ammo_0;
Animation *anim_ammo_1;
Animation *anim_ammo_2;
Animation *anim_ammo_3;
Animation *anim_ammo_4;
Animation *anim_ammo_5;
Animation *anim_ammo_6;
Animation *anim_ammo_7;
Animation *anim_ammo_8;
Animation *anim_ammo_9;
Animation *anim_ammo_0_blinking;
Animation *anim_ammo_1_blinking;
Animation *anim_ammo_2_blinking;
Animation *anim_ammo_3_blinking;
Animation *anim_ammo_4_blinking;
Animation *anim_ammo_5_blinking;
Animation *anim_ammo_6_blinking;
Animation *anim_ammo_7_blinking;
Animation *anim_ammo_8_blinking;
Animation *anim_ammo_9_blinking;
Animation *anim_forward_slash;

// diviiding line sprite sheet
Sprite_Sheet sprite_sheet_divider;

extern HUD *hud;

void init_hud(SDL_Window *window);
void render_hud(SDL_Window *window, u32 texture_slots[32], vec4 color);
void render_health(SDL_Window *window, u32 texture_slots[32], Player *player,
                   vec2 position, vec4 color);
void render_ammo(SDL_Window *window, u32 texture_slots[32], Player *player,
                 vec2 position, vec4 color);
void free_hud(void);

#endif