#ifndef HUD_H
#define HUD_H

#include "structs.h"
#include "player_helpers.h"
#include "engine/render.h"
#include "engine/util.h"

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
Animation *anim_forward_slash;

extern HUD *hud;

void init_hud(SDL_Window *window);
void render_hud(SDL_Window *window, u32 texture_slots[32]);
void render_health(SDL_Window *window, u32 texture_slots[32], Player *player, vec2 position);
void render_ammo(SDL_Window *window, u32 texture_slots[32], Player *player, vec2 position);
void free_hud(void);

#endif