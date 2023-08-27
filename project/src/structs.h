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
    M16,
    M44
};

enum Pickup_Name
{
    M44_PICKUP
};

enum Fire_Mode
{
    AUTO,
    SEMI,
    BURST
};

enum Player_Status
{
    PLAYER_SPAWNING,
    PLAYER_ACTIVE,
    PLAYER_DESPAWNING,
    PLAYER_INACTIVE
};

enum Pickup_Status
{
    PICKUP_ACTIVE,
    PICKUP_INACTIVE,
    PICKUP_SPAWNING
};

// used to define common weapon types
typedef struct weapon_type
{
    enum Weapon_Name name;
    enum Fire_Mode fire_mode;
    i8 capacity;
    u16 max_fire_rate; // rounds per minute
    i8 damage;
} Weapon_Type;

// contains weapon info as well as player-specific data
typedef struct weapon
{
    enum Weapon_Name name;
    enum Fire_Mode fire_mode;
    i8 capacity;
    i8 current_capacity;
    u16 max_fire_rate;
    i8 damage;
    u16 frames_since_last_shot;
    bool ready_to_fire;
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
    vec2 spawn_point;
    enum Direction direction;
    enum Player_Status status;
    f32 despawn_time;     // time it takes for animation to complete after health <= 0
    f32 spawn_delay;      // time in s from INACTIVE status to SPAWNING status
    f32 spawn_time;       // time in s from SPAWNING status to ACTIVE status
    u32 frames_on_status; // # of frames since last status change
    i8 health;
    bool is_left_player;
} Player;

typedef struct pickup
{
    Entity *entity;
    enum Pickup_Name name;
    enum Pickup_Status status;
    f32 spawn_delay;
    f32 spawn_time;
    u32 frames_on_status;

} Pickup;

typedef struct map
{
    // these indicate the lengths of their respective arrays
    usize num_sprites;
    usize num_pickups;
    usize num_static_bodies;
    usize num_p1_spawns;
    usize num_p2_spawns;

    Sprite *sprites;               // start of sprites array
    Pickup *pickups;               // start of pickups array
    Static_Body *static_bodies;    // start of static bodies array
    vec2 *player_one_spawn_points; // player one's spawn points
    vec2 *player_two_spawn_points; // player two's spawn points
} Map;

#endif