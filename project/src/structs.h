#ifndef STRUCTS_H
#define STRUCTS_H

#include "engine/entity.h"
#include "engine/types.h"
#include "engine/animation.h"
#include "engine/render.h"

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum Weapon_Name
{
    RIFLE
};

enum Player_Status
{
    SPAWNING,
    ACTIVE,
    DESPAWNING,
    INACTIVE
};

typedef struct weapon
{
    enum Weapon_Name name;
    i8 capacity;
    i8 current_capacity;
    i8 max_fire_rate;
} Weapon;

typedef struct animation_set
{
    Animation *up_idle;
    Animation *up_moving;
    Animation *down_idle;
    Animation *down_moving;
    Animation *side_idle;
    Animation *side_moving;
    Animation *spawning;
    Animation *dying;
} Animation_Set;

typedef struct player
{
    Entity *entity;
    Animation_Set *animation_set;
    Weapon *weapon;
    enum Direction direction;
    enum Player_Status status;
    f32 despawn_time;     // time it takes for animation to complete after health <= 0
    f32 spawn_delay;      // time in s from INACTIVE status to SPAWNING status
    f32 spawn_time;       // time in s from SPAWNING status to ACTIVE status
    u32 frames_on_status; // # of frames since last status change
    i8 health;
} Player;

typedef struct map
{
    // these indicate the lengths of their respective arrays
    usize num_sprites;
    usize num_static_bodies;
    usize num_p1_spawns;
    usize num_p2_spawns;

    Sprite *sprites;               // start of sprites array
    Static_Body *static_bodies;    // start of static bodies array
    vec2 *player_one_spawn_points; // player one's spawn points
    vec2 *player_two_spawn_points; // player two's spawn points
} Map;

#endif