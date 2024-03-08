#ifndef PLAYER_STRUCTS_H
#define PLAYER_STRUCTS_H

#include "../engine/entity.h"
#include "../engine/types.h"
#include "../structs.h"

typedef struct player_key_state {
    Key_State left;
    Key_State right;
    Key_State up;
    Key_State down;
    Key_State shoot;
    Key_State reload;
    Key_State use;
    Key_State pause;
} Player_Key_State;

typedef struct player_input_state {
    Controller_Input_State *controller_input_state;
    Player_Key_State *key_state;
} Player_Input_State;

typedef struct player {
    Entity *entity;
    Entity *crosshair;
    Camera *camera;
    Weapon *weapon;
    Armor *armor;
    vec2 spawn_point;
    vec2 relative_position; // position relative to the rest of the map NOT
                            // to the window
    enum Player_Status status;
    Player_Input_State *input_state;
    f32 render_scale_factor; // render scale factor (determines FOV of the
                             // player). Normal is 0.5, render width is 0.5
                             // of window width
    f32 despawn_time;        // time it takes for animation to complete after
                             // health <=
                             // 0
    f32 spawn_delay;         // time in s from INACTIVE status to SPAWNING status
    f32 spawn_time;          // time in s from SPAWNING status to ACTIVE status
    f32 crosshair_angle;
    u32 frames_on_status;    // # of frames since last status change
    i16 health;
    bool is_left_player;
} Player;

#endif