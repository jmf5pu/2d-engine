#ifndef PLAYER_HELPERS_H
#define PLAYER_HELPERS_H

#include "engine/hash_map.h"
#include "engine/animation.h"
#include "structs.h"

// number of animations to be stored in player_anim_map
#define PLAYER_ANIM_COUNT 56

// declare players
extern Player *player_one;
extern Player *player_two;

// hash map to store player anims
Hash_Map *player_anim_map;

// crosshair sprites & anims
Sprite_Sheet sprite_sheet_crosshair_red;
Animation_Definition *adef_crosshair_red;
Animation *anim_crosshair_red;

// placeholder animation if one is missing
Sprite_Sheet sprite_sheet_player_placeholder;
Animation_Definition *adef_player_placeholder;
Animation *anim_player_placeholder;

// player 1 sprites & anims
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_idle_side;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_running_side;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_idle_back;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_running_back;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_idle_front;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_running_front;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_idle_up_right;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_running_up_right;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_idle_down_right;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_running_down_right;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_spawning_side;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_dying_side;

Sprite_Sheet p1_sprite_sheet_soldier_1_m16_brewster_idle_side;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_brewster_running_side;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_brewster_idle_back;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_brewster_running_back;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_brewster_idle_front;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_brewster_running_front;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_brewster_spawning_side;
Sprite_Sheet p1_sprite_sheet_soldier_1_m16_brewster_dying_side;

Sprite_Sheet p1_sprite_sheet_soldier_1_m44_idle_side;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_running_side;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_idle_back;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_running_back;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_idle_front;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_running_front;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_spawning_side;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_dying_side;

Sprite_Sheet p1_sprite_sheet_soldier_1_m44_brewster_idle_side;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_brewster_running_side;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_brewster_idle_back;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_brewster_running_back;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_brewster_idle_front;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_brewster_running_front;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_brewster_spawning_side;
Sprite_Sheet p1_sprite_sheet_soldier_1_m44_brewster_dying_side;

Animation_Definition *p1_adef_soldier_1_m16_idle_side;
Animation_Definition *p1_adef_soldier_1_m16_running_side;
Animation_Definition *p1_adef_soldier_1_m16_idle_back;
Animation_Definition *p1_adef_soldier_1_m16_running_back;
Animation_Definition *p1_adef_soldier_1_m16_idle_front;
Animation_Definition *p1_adef_soldier_1_m16_running_front;
Animation_Definition *p1_adef_soldier_1_m16_idle_up_right;
Animation_Definition *p1_adef_soldier_1_m16_running_up_right;
Animation_Definition *p1_adef_soldier_1_m16_idle_down_right;
Animation_Definition *p1_adef_soldier_1_m16_running_down_right;
Animation_Definition *p1_adef_soldier_1_m16_spawning_side;
Animation_Definition *p1_adef_soldier_1_m16_dying_side;

Animation_Definition *p1_adef_soldier_1_m16_brewster_idle_side;
Animation_Definition *p1_adef_soldier_1_m16_brewster_running_side;
Animation_Definition *p1_adef_soldier_1_m16_brewster_idle_back;
Animation_Definition *p1_adef_soldier_1_m16_brewster_running_back;
Animation_Definition *p1_adef_soldier_1_m16_brewster_idle_front;
Animation_Definition *p1_adef_soldier_1_m16_brewster_running_front;
Animation_Definition *p1_adef_soldier_1_m16_brewster_spawning_side;
Animation_Definition *p1_adef_soldier_1_m16_brewster_dying_side;

Animation_Definition *p1_adef_soldier_1_m44_idle_side;
Animation_Definition *p1_adef_soldier_1_m44_running_side;
Animation_Definition *p1_adef_soldier_1_m44_idle_back;
Animation_Definition *p1_adef_soldier_1_m44_running_back;
Animation_Definition *p1_adef_soldier_1_m44_idle_front;
Animation_Definition *p1_adef_soldier_1_m44_running_front;
Animation_Definition *p1_adef_soldier_1_m44_spawning_side;
Animation_Definition *p1_adef_soldier_1_m44_dying_side;

Animation_Definition *p1_adef_soldier_1_m44_brewster_idle_side;
Animation_Definition *p1_adef_soldier_1_m44_brewster_running_side;
Animation_Definition *p1_adef_soldier_1_m44_brewster_idle_back;
Animation_Definition *p1_adef_soldier_1_m44_brewster_running_back;
Animation_Definition *p1_adef_soldier_1_m44_brewster_idle_front;
Animation_Definition *p1_adef_soldier_1_m44_brewster_running_front;
Animation_Definition *p1_adef_soldier_1_m44_brewster_spawning_side;
Animation_Definition *p1_adef_soldier_1_m44_brewster_dying_side;

Animation *p1_anim_soldier_1_m16_idle_side;
Animation *p1_anim_soldier_1_m16_running_side;
Animation *p1_anim_soldier_1_m16_idle_back;
Animation *p1_anim_soldier_1_m16_running_back;
Animation *p1_anim_soldier_1_m16_idle_front;
Animation *p1_anim_soldier_1_m16_running_front;
Animation *p1_anim_soldier_1_m16_idle_up_right;
Animation *p1_anim_soldier_1_m16_running_up_right;
Animation *p1_anim_soldier_1_m16_idle_down_right;
Animation *p1_anim_soldier_1_m16_running_down_right;
Animation *p1_anim_soldier_1_m16_spawning_side;
Animation *p1_anim_soldier_1_m16_dying_side;

Animation *p1_anim_soldier_1_m16_brewster_idle_side;
Animation *p1_anim_soldier_1_m16_brewster_running_side;
Animation *p1_anim_soldier_1_m16_brewster_idle_back;
Animation *p1_anim_soldier_1_m16_brewster_running_back;
Animation *p1_anim_soldier_1_m16_brewster_idle_front;
Animation *p1_anim_soldier_1_m16_brewster_running_front;
Animation *p1_anim_soldier_1_m16_brewster_spawning_side;
Animation *p1_anim_soldier_1_m16_brewster_dying_side;

Animation *p1_anim_soldier_1_m44_idle_side;
Animation *p1_anim_soldier_1_m44_running_side;
Animation *p1_anim_soldier_1_m44_idle_back;
Animation *p1_anim_soldier_1_m44_running_back;
Animation *p1_anim_soldier_1_m44_idle_front;
Animation *p1_anim_soldier_1_m44_running_front;
Animation *p1_anim_soldier_1_m44_spawning_side;
Animation *p1_anim_soldier_1_m44_dying_side;

Animation *p1_anim_soldier_1_m44_brewster_idle_side;
Animation *p1_anim_soldier_1_m44_brewster_running_side;
Animation *p1_anim_soldier_1_m44_brewster_idle_back;
Animation *p1_anim_soldier_1_m44_brewster_running_back;
Animation *p1_anim_soldier_1_m44_brewster_idle_front;
Animation *p1_anim_soldier_1_m44_brewster_running_front;
Animation *p1_anim_soldier_1_m44_brewster_spawning_side;
Animation *p1_anim_soldier_1_m44_brewster_dying_side;

// player 2 sprites & anims
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_idle_side;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_running_side;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_idle_back;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_running_back;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_idle_front;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_running_front;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_idle_up_right;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_running_up_right;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_idle_down_right;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_running_down_right;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_spawning_side;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_dying_side;

Sprite_Sheet p2_sprite_sheet_soldier_1_m16_brewster_idle_side;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_brewster_running_side;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_brewster_idle_back;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_brewster_running_back;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_brewster_idle_front;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_brewster_running_front;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_brewster_spawning_side;
Sprite_Sheet p2_sprite_sheet_soldier_1_m16_brewster_dying_side;

Sprite_Sheet p2_sprite_sheet_soldier_1_m44_idle_side;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_running_side;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_idle_back;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_running_back;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_idle_front;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_running_front;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_spawning_side;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_dying_side;

Sprite_Sheet p2_sprite_sheet_soldier_1_m44_brewster_idle_side;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_brewster_running_side;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_brewster_idle_back;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_brewster_running_back;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_brewster_idle_front;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_brewster_running_front;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_brewster_spawning_side;
Sprite_Sheet p2_sprite_sheet_soldier_1_m44_brewster_dying_side;

Animation_Definition *p2_adef_soldier_1_m16_idle_side;
Animation_Definition *p2_adef_soldier_1_m16_running_side;
Animation_Definition *p2_adef_soldier_1_m16_idle_back;
Animation_Definition *p2_adef_soldier_1_m16_running_back;
Animation_Definition *p2_adef_soldier_1_m16_idle_front;
Animation_Definition *p2_adef_soldier_1_m16_running_front;
Animation_Definition *p2_adef_soldier_1_m16_idle_up_right;
Animation_Definition *p2_adef_soldier_1_m16_running_up_right;
Animation_Definition *p2_adef_soldier_1_m16_idle_down_right;
Animation_Definition *p2_adef_soldier_1_m16_running_down_right;
Animation_Definition *p2_adef_soldier_1_m16_spawning_side;
Animation_Definition *p2_adef_soldier_1_m16_dying_side;

Animation_Definition *p2_adef_soldier_1_m16_brewster_idle_side;
Animation_Definition *p2_adef_soldier_1_m16_brewster_running_side;
Animation_Definition *p2_adef_soldier_1_m16_brewster_idle_back;
Animation_Definition *p2_adef_soldier_1_m16_brewster_running_back;
Animation_Definition *p2_adef_soldier_1_m16_brewster_idle_front;
Animation_Definition *p2_adef_soldier_1_m16_brewster_running_front;
Animation_Definition *p2_adef_soldier_1_m16_brewster_spawning_side;
Animation_Definition *p2_adef_soldier_1_m16_brewster_dying_side;

Animation_Definition *p2_adef_soldier_1_m44_idle_side;
Animation_Definition *p2_adef_soldier_1_m44_running_side;
Animation_Definition *p2_adef_soldier_1_m44_idle_back;
Animation_Definition *p2_adef_soldier_1_m44_running_back;
Animation_Definition *p2_adef_soldier_1_m44_idle_front;
Animation_Definition *p2_adef_soldier_1_m44_running_front;
Animation_Definition *p2_adef_soldier_1_m44_spawning_side;
Animation_Definition *p2_adef_soldier_1_m44_dying_side;

Animation_Definition *p2_adef_soldier_1_m44_brewster_idle_side;
Animation_Definition *p2_adef_soldier_1_m44_brewster_running_side;
Animation_Definition *p2_adef_soldier_1_m44_brewster_idle_back;
Animation_Definition *p2_adef_soldier_1_m44_brewster_running_back;
Animation_Definition *p2_adef_soldier_1_m44_brewster_idle_front;
Animation_Definition *p2_adef_soldier_1_m44_brewster_running_front;
Animation_Definition *p2_adef_soldier_1_m44_brewster_spawning_side;
Animation_Definition *p2_adef_soldier_1_m44_brewster_dying_side;

Animation *p2_anim_soldier_1_m16_idle_side;
Animation *p2_anim_soldier_1_m16_running_side;
Animation *p2_anim_soldier_1_m16_idle_back;
Animation *p2_anim_soldier_1_m16_running_back;
Animation *p2_anim_soldier_1_m16_idle_front;
Animation *p2_anim_soldier_1_m16_running_front;
Animation *p2_anim_soldier_1_m16_idle_up_right;
Animation *p2_anim_soldier_1_m16_running_up_right;
Animation *p2_anim_soldier_1_m16_idle_down_right;
Animation *p2_anim_soldier_1_m16_running_down_right;
Animation *p2_anim_soldier_1_m16_spawning_side;
Animation *p2_anim_soldier_1_m16_dying_side;

Animation *p2_anim_soldier_1_m16_brewster_idle_side;
Animation *p2_anim_soldier_1_m16_brewster_running_side;
Animation *p2_anim_soldier_1_m16_brewster_idle_back;
Animation *p2_anim_soldier_1_m16_brewster_running_back;
Animation *p2_anim_soldier_1_m16_brewster_idle_front;
Animation *p2_anim_soldier_1_m16_brewster_running_front;
Animation *p2_anim_soldier_1_m16_brewster_spawning_side;
Animation *p2_anim_soldier_1_m16_brewster_dying_side;

Animation *p2_anim_soldier_1_m44_idle_side;
Animation *p2_anim_soldier_1_m44_running_side;
Animation *p2_anim_soldier_1_m44_idle_back;
Animation *p2_anim_soldier_1_m44_running_back;
Animation *p2_anim_soldier_1_m44_idle_front;
Animation *p2_anim_soldier_1_m44_running_front;
Animation *p2_anim_soldier_1_m44_spawning_side;
Animation *p2_anim_soldier_1_m44_dying_side;

Animation *p2_anim_soldier_1_m44_brewster_idle_side;
Animation *p2_anim_soldier_1_m44_brewster_running_side;
Animation *p2_anim_soldier_1_m44_brewster_idle_back;
Animation *p2_anim_soldier_1_m44_brewster_running_back;
Animation *p2_anim_soldier_1_m44_brewster_idle_front;
Animation *p2_anim_soldier_1_m44_brewster_running_front;
Animation *p2_anim_soldier_1_m44_brewster_spawning_side;
Animation *p2_anim_soldier_1_m44_brewster_dying_side;

// bullet sprites & anims
Sprite_Sheet sprite_sheet_bullet_1_horizontal;
Sprite_Sheet sprite_sheet_bullet_1_vertical;

Animation_Definition *adef_bullet_1_horizontal;
Animation_Definition *adef_bullet_1_vertical;

Animation *anim_bullet_1_horizontal;
Animation *anim_bullet_1_vertical;

void init_player_anim_hashmap();
void init_all_anims();
void update_player_status(Player *player);
void update_player_animations(Player *player);
void handle_player_shooting(Player *player);
void handle_player_input(Player *player);
Player *get_player_from_body(Player *player_one, Player *player_two, Body *body, bool return_other_player);

#endif