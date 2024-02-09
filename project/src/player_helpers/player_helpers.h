#ifndef PLAYER_HELPERS_H
#define PLAYER_HELPERS_H

#include "../engine/animation.h"
#include "../engine/global.h"
#include "../engine/hash_map.h"
#include "../structs.h"

// number of animations to be stored in player_anim_map
#define PLAYER_ANIM_COUNT 56
#define BULLET_ANIM_COUNT 16

// used in reloading calculations
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define BULLET_DISTANCE_FROM_PLAYER 40

#define DEFAULT_PLAYER_MOVEMENT_SPEED 250
#define DEFAULT_CROSSHAIR_MOVEMENT_SPEED 350
#define CROSSHAIR_SIZE 200

// declare players
extern Player *player_one;
extern Player *player_two;

// animation hash maps
Hash_Map *bullet_anim_map;
Hash_Map *player_anim_map;

// crosshair sprites & anims
Sprite_Sheet sprite_sheet_player_1_crosshair;
Sprite_Sheet sprite_sheet_player_2_crosshair;
Animation_Definition *adef_player_1_crosshair;
Animation_Definition *adef_player_2_crosshair;
Animation *anim_p1_crosshair;
Animation *anim_p2_crosshair;

// placeholder animation if one is missing
Sprite_Sheet sprite_sheet_player_placeholder;
Animation_Definition *adef_player_placeholder;
Animation *anim_player_placeholder;

// bullet sprites & anims
Sprite_Sheet sprite_sheet_bullet_0;
Sprite_Sheet sprite_sheet_bullet_1;
Sprite_Sheet sprite_sheet_bullet_2;
Sprite_Sheet sprite_sheet_bullet_3;
Sprite_Sheet sprite_sheet_bullet_4;
Sprite_Sheet sprite_sheet_bullet_5;
Sprite_Sheet sprite_sheet_bullet_6;
Sprite_Sheet sprite_sheet_bullet_7;
Sprite_Sheet sprite_sheet_bullet_8;
Sprite_Sheet sprite_sheet_bullet_9;
Sprite_Sheet sprite_sheet_bullet_10;
Sprite_Sheet sprite_sheet_bullet_11;
Sprite_Sheet sprite_sheet_bullet_12;
Sprite_Sheet sprite_sheet_bullet_13;
Sprite_Sheet sprite_sheet_bullet_14;
Sprite_Sheet sprite_sheet_bullet_15;

Animation_Definition *adef_bullet_0;
Animation_Definition *adef_bullet_1;
Animation_Definition *adef_bullet_2;
Animation_Definition *adef_bullet_3;
Animation_Definition *adef_bullet_4;
Animation_Definition *adef_bullet_5;
Animation_Definition *adef_bullet_6;
Animation_Definition *adef_bullet_7;
Animation_Definition *adef_bullet_8;
Animation_Definition *adef_bullet_9;
Animation_Definition *adef_bullet_10;
Animation_Definition *adef_bullet_11;
Animation_Definition *adef_bullet_12;
Animation_Definition *adef_bullet_13;
Animation_Definition *adef_bullet_14;
Animation_Definition *adef_bullet_15;

Animation *anim_bullet_0;
Animation *anim_bullet_1;
Animation *anim_bullet_2;
Animation *anim_bullet_3;
Animation *anim_bullet_4;
Animation *anim_bullet_5;
Animation *anim_bullet_6;
Animation *anim_bullet_7;
Animation *anim_bullet_8;
Animation *anim_bullet_9;
Animation *anim_bullet_10;
Animation *anim_bullet_11;
Animation *anim_bullet_12;
Animation *anim_bullet_13;
Animation *anim_bullet_14;
Animation *anim_bullet_15;

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

/*
NEW PLAYER OBJECTS 11/12
*/
Sprite_Sheet sprite_sheet_soldier_purple_base_idle_right;
Sprite_Sheet sprite_sheet_soldier_purple_base_idle_left;
Sprite_Sheet sprite_sheet_soldier_purple_base_idle_down;
Sprite_Sheet sprite_sheet_soldier_purple_base_idle_down_right;
Sprite_Sheet sprite_sheet_soldier_purple_base_idle_down_left;
Sprite_Sheet sprite_sheet_soldier_purple_base_idle_up;
Sprite_Sheet sprite_sheet_soldier_purple_base_idle_up_right;
Sprite_Sheet sprite_sheet_soldier_purple_base_idle_up_left;

Animation_Definition *adef_soldier_purple_base_idle_right;
Animation_Definition *adef_soldier_purple_base_idle_left;
Animation_Definition *adef_soldier_purple_base_idle_down;
Animation_Definition *adef_soldier_purple_base_idle_down_left;
Animation_Definition *adef_soldier_purple_base_idle_down_right;
Animation_Definition *adef_soldier_purple_base_idle_up;
Animation_Definition *adef_soldier_purple_base_idle_up_left;
Animation_Definition *adef_soldier_purple_base_idle_up_right;

Animation *p1_anim_soldier_purple_base_idle_right;
Animation *p1_anim_soldier_purple_base_idle_left;
Animation *p1_anim_soldier_purple_base_idle_down;
Animation *p1_anim_soldier_purple_base_idle_down_left;
Animation *p1_anim_soldier_purple_base_idle_down_right;
Animation *p1_anim_soldier_purple_base_idle_up;
Animation *p1_anim_soldier_purple_base_idle_up_left;
Animation *p1_anim_soldier_purple_base_idle_up_right;

Animation *p2_anim_soldier_purple_base_idle_right;
Animation *p2_anim_soldier_purple_base_idle_left;
Animation *p2_anim_soldier_purple_base_idle_down;
Animation *p2_anim_soldier_purple_base_idle_up;
Animation *p2_anim_soldier_purple_base_idle_down_left;
Animation *p2_anim_soldier_purple_base_idle_down_right;
Animation *p2_anim_soldier_purple_base_idle_up;
Animation *p2_anim_soldier_purple_base_idle_up_left;
Animation *p2_anim_soldier_purple_base_idle_up_right;

// bullet sprites & anims
Sprite_Sheet sprite_sheet_bullet_1_horizontal;
Sprite_Sheet sprite_sheet_bullet_1_vertical;

Animation_Definition *adef_bullet_1_horizontal;
Animation_Definition *adef_bullet_1_vertical;

Animation *anim_bullet_1_horizontal;
Animation *anim_bullet_1_vertical;

void init_bullet_anim_hashmap();
void init_player_anim_hashmap();
void init_all_anims();
void init_player(Player *player, Map *map, Weapon_Type *starting_weapon, f32 despawn_time, f32 spawn_delay, f32 spawn_time, bool is_left_player);
void spawn_player(Player *player, Weapon_Type *starting_weapon);
void update_player_status(Player *player);
void update_player_animations(Player *player);
void handle_player_shooting(Player *player, Key_State shoot);
void handle_player_input(Player *player);
void free_player(Player *player);
void update_crosshair_position_percentage(Player *player);
void player_per_frame_updates(Player *player);

#endif