#ifndef PLAYER_HELPERS_H
#define PLAYER_HELPERS_H

#include "../engine/animation.h"
#include "../engine/global.h"
#include "../engine/hash_map.h"
#include "../map_helpers/map_helpers.h"
#include "../structs.h"
#include "player_structs.h"

// number of animations to be stored in player_anim_map
#define PLAYER_ANIM_COUNT 56
#define BULLET_ADEF_COUNT 16
#define WEAPON_COUNT 1
#define WEAPON_STATES 2
#define ANGLES 16

#define MIN(x, y) (((x) < (y)) ? (x) : (y)) // used in reloading calculations
#define BULLET_DISTANCE_FROM_PLAYER 40
#define MUZZLE_FLASH_DISTANCE_FROM_PLAYER 25
#define PLAYER_HEIGHT 22 // used for shadow position and brass bounce
#define BRASS_EJECT_DISTANCE_FROM_PLAYER 5
#define INVERT_Y_AXIS true // if true, joystick up motion will correspond to positive y axis value
#define CROSSHAIR_SIZE 11
#define CHARACTER_WEAPON_OFFSET 2              // how far away the weapon should be from the character at any given angle
#define CHARACTER_ARMS_Y_OFFSET_FROM_CENTER -3 // how far the arms depicted in the sprite are off from the center in terms of y
#define MAX_PLAYER_MOVEMENT_SPEED 250
#define MAX_CROSSHAIR_MOVEMENT_SPEED 600

// declare players
extern Player *player_one;
extern Player *player_two;

// crosshair sprites & anims
Sprite_Sheet sprite_sheet_player_1_crosshair;
Sprite_Sheet sprite_sheet_player_2_crosshair;
Animation_Definition *adef_player_1_crosshair;
Animation_Definition *adef_player_2_crosshair;
Animation *anim_p1_crosshair;
Animation *anim_p2_crosshair;

// placeholder animation if one is missing
Sprite_Sheet sprite_sheet_missing_anim_placeholder;
Animation_Definition *adef_missing_anim_placeholder;
Animation *missing_anim_placeholder;

// weapon sprite sheets/ animation definitions
Sprite_Sheet sprite_sheet_m16_static_0;
Animation_Definition *adef_m16_static_0;

Sprite_Sheet sprite_sheet_m16_static_1;
Animation_Definition *adef_m16_static_1;

Sprite_Sheet sprite_sheet_m16_static_2;
Animation_Definition *adef_m16_static_2;

Sprite_Sheet sprite_sheet_m16_static_3;
Animation_Definition *adef_m16_static_3;

Sprite_Sheet sprite_sheet_m16_static_4;
Animation_Definition *adef_m16_static_4;

Sprite_Sheet sprite_sheet_m16_static_5;
Animation_Definition *adef_m16_static_5;

Sprite_Sheet sprite_sheet_m16_static_6;
Animation_Definition *adef_m16_static_6;

Sprite_Sheet sprite_sheet_m16_static_7;
Animation_Definition *adef_m16_static_7;

Sprite_Sheet sprite_sheet_m16_static_8;
Animation_Definition *adef_m16_static_8;

Sprite_Sheet sprite_sheet_m16_static_9;
Animation_Definition *adef_m16_static_9;

Sprite_Sheet sprite_sheet_m16_static_10;
Animation_Definition *adef_m16_static_10;

Sprite_Sheet sprite_sheet_m16_static_11;
Animation_Definition *adef_m16_static_11;

Sprite_Sheet sprite_sheet_m16_static_12;
Animation_Definition *adef_m16_static_12;

Sprite_Sheet sprite_sheet_m16_static_13;
Animation_Definition *adef_m16_static_13;

Sprite_Sheet sprite_sheet_m16_static_14;
Animation_Definition *adef_m16_static_14;

Sprite_Sheet sprite_sheet_m16_static_15;
Animation_Definition *adef_m16_static_15;

Sprite_Sheet sprite_sheet_m16_firing_0;
Animation_Definition *adef_m16_firing_0;

Sprite_Sheet sprite_sheet_m16_firing_1;
Animation_Definition *adef_m16_firing_1;

Sprite_Sheet sprite_sheet_m16_firing_2;
Animation_Definition *adef_m16_firing_2;

Sprite_Sheet sprite_sheet_m16_firing_3;
Animation_Definition *adef_m16_firing_3;

Sprite_Sheet sprite_sheet_m16_firing_4;
Animation_Definition *adef_m16_firing_4;

Sprite_Sheet sprite_sheet_m16_firing_5;
Animation_Definition *adef_m16_firing_5;

Sprite_Sheet sprite_sheet_m16_firing_6;
Animation_Definition *adef_m16_firing_6;

Sprite_Sheet sprite_sheet_m16_firing_7;
Animation_Definition *adef_m16_firing_7;

Sprite_Sheet sprite_sheet_m16_firing_8;
Animation_Definition *adef_m16_firing_8;

Sprite_Sheet sprite_sheet_m16_firing_9;
Animation_Definition *adef_m16_firing_9;

Sprite_Sheet sprite_sheet_m16_firing_10;
Animation_Definition *adef_m16_firing_10;

Sprite_Sheet sprite_sheet_m16_firing_11;
Animation_Definition *adef_m16_firing_11;

Sprite_Sheet sprite_sheet_m16_firing_12;
Animation_Definition *adef_m16_firing_12;

Sprite_Sheet sprite_sheet_m16_firing_13;
Animation_Definition *adef_m16_firing_13;

Sprite_Sheet sprite_sheet_m16_firing_14;
Animation_Definition *adef_m16_firing_14;

Sprite_Sheet sprite_sheet_m16_firing_15;
Animation_Definition *adef_m16_firing_15;

// bullet sprite sheets/animation definitions
Sprite_Sheet sprite_sheet_bullet_medium;
Animation_Definition *adef_bullet_medium;

void init_bullet_anim_hashmap(void);
void init_weapon_adef_hashmap(void);
void init_all_player_anims(void);
void init_player(Player *player, Map *map, Weapon_Type *starting_weapon, f32 despawn_time, f32 spawn_delay, f32 spawn_time, bool is_left_player);
void spawn_player(Player *player, Weapon_Type *starting_weapon);
void update_player_status(Player *player);
void handle_player_shooting(Player *player, Key_State shoot);
void handle_player_input(Player *player);
void free_players(void);
void player_per_frame_updates(Player *player);
void render_player_anims(Player *player, SDL_Window *window, u32 texture_slots[32], vec4 color);

void assign_player_input_devices(void);
void update_player_input_state_via_controller(Player *player, SDL_Event *event);
void update_player_input_state_from_joysticks(Player *player);
void update_player_input_state_from_keyboard(Player *player);
void update_menu_input_state(Menu_Input_State menu_input_state);
void update_player_velocity_from_key_state(Player *player);
void apply_player_joystick_movement(Player *player);
void update_entity_velocity_from_joystick_input(Joystick_State input, Entity *entity, int max_velocity);
void apply_player_input_state(Player *player);
void update_crosshair_position_from_cursor(Player *player);
void maintain_controller_keypresses(Player *player);
void maintain_controller_keypress(Key_State *key_state);

void update_player_anims(Player *player);
static void update_player_weapon_anim(Player *player);
static void update_player_crosshair_angle(Player *player);
static void update_player_weapon_position(Player *player);
static i32 get_player_brass_z_index(f32 angle);

void get_direction_from_angle(f32 angle, char *direction_result);

#endif