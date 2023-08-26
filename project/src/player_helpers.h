#ifndef PLAYER_HELPERS_H
#define PLAYER_HELPERS_H

#include "engine/animation.h"
#include "structs.h"

// declare players
extern Player *player_one;
extern Player *player_two;

// player 1 sprites & anims
Sprite_Sheet p1_sprite_sheet_soldier_idle_side;
Sprite_Sheet p1_sprite_sheet_soldier_running_side;
Sprite_Sheet p1_sprite_sheet_soldier_idle_back;
Sprite_Sheet p1_sprite_sheet_soldier_running_back;
Sprite_Sheet p1_sprite_sheet_soldier_idle_front;
Sprite_Sheet p1_sprite_sheet_soldier_running_front;
Sprite_Sheet p1_sprite_sheet_soldier_spawning_side;
Sprite_Sheet p1_sprite_sheet_soldier_dying_side;

Animation_Definition *p1_adef_soldier_idle_side;
Animation_Definition *p1_adef_soldier_running_side;
Animation_Definition *p1_adef_soldier_idle_back;
Animation_Definition *p1_adef_soldier_running_back;
Animation_Definition *p1_adef_soldier_idle_front;
Animation_Definition *p1_adef_soldier_running_front;
Animation_Definition *p1_adef_soldier_spawning_side;
Animation_Definition *p1_adef_soldier_dying_side;

Animation *p1_anim_soldier_idle_side;
Animation *p1_anim_soldier_running_side;
Animation *p1_anim_soldier_idle_back;
Animation *p1_anim_soldier_running_back;
Animation *p1_anim_soldier_idle_front;
Animation *p1_anim_soldier_running_front;
Animation *p1_anim_soldier_spawning_side;
Animation *p1_anim_soldier_dying_side;

// player 2 sprites & anims
Sprite_Sheet p2_sprite_sheet_soldier_idle_side;
Sprite_Sheet p2_sprite_sheet_soldier_running_side;
Sprite_Sheet p2_sprite_sheet_soldier_idle_back;
Sprite_Sheet p2_sprite_sheet_soldier_running_back;
Sprite_Sheet p2_sprite_sheet_soldier_idle_front;
Sprite_Sheet p2_sprite_sheet_soldier_running_front;
Sprite_Sheet p2_sprite_sheet_soldier_spawning_side;
Sprite_Sheet p2_sprite_sheet_soldier_dying_side;

Animation_Definition *p2_adef_soldier_idle_side;
Animation_Definition *p2_adef_soldier_running_side;
Animation_Definition *p2_adef_soldier_idle_back;
Animation_Definition *p2_adef_soldier_running_back;
Animation_Definition *p2_adef_soldier_idle_front;
Animation_Definition *p2_adef_soldier_running_front;
Animation_Definition *p2_adef_soldier_spawning_side;
Animation_Definition *p2_adef_soldier_dying_side;

Animation *p2_anim_soldier_idle_side;
Animation *p2_anim_soldier_running_side;
Animation *p2_anim_soldier_idle_back;
Animation *p2_anim_soldier_running_back;
Animation *p2_anim_soldier_idle_front;
Animation *p2_anim_soldier_running_front;
Animation *p2_anim_soldier_spawning_side;
Animation *p2_anim_soldier_dying_side;

// bullet sprites & anims
Sprite_Sheet sprite_sheet_bullet_1_horizontal;
Sprite_Sheet sprite_sheet_bullet_1_vertical;

Animation_Definition *adef_bullet_1_horizontal;
Animation_Definition *adef_bullet_1_vertical;

Animation *anim_bullet_1_horizontal;
Animation *anim_bullet_1_vertical;

void init_all_anims();
void update_player_status(Player *player);
void update_player_animations(Player *player);
void handle_player_shooting(Player *player);
void handle_player_input(Player *player);
Player *get_player_from_body(Player *player_one, Player *player_two, Body *body);

#endif