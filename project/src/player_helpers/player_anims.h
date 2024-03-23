#ifndef PLAYER_ANIMS_H
#define PLAYER_ANIMS_H

#include "../engine/animation.h"
#include "../engine/render.h"
#include "player_helpers.h"

void update_player_character_anim(Player *player);
void init_player_character_anim_hashmap(void);
void init_player_character_anims(void);

Sprite_Sheet sprite_sheet_player_skinhead_idle_1;
Sprite_Sheet sprite_sheet_player_skinhead_idle_2;
Sprite_Sheet sprite_sheet_player_skinhead_idle_3;
Sprite_Sheet sprite_sheet_player_skinhead_idle_4;

Animation_Definition *adef_player_skinhead_idle_1;
Animation_Definition *adef_player_skinhead_idle_2;
Animation_Definition *adef_player_skinhead_idle_3;
Animation_Definition *adef_player_skinhead_idle_4;

Animation *anim_player_skinhead_idle_1;
Animation *anim_player_skinhead_idle_2;
Animation *anim_player_skinhead_idle_3;
Animation *anim_player_skinhead_idle_4;

#endif