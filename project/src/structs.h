#ifndef STRUCTS_H
#define STRUCTS_H

#define MENU_MAX_LINES 10
#define MENU_MAX_LINE_LENGTH 50

#include "engine/animation.h"
#include "engine/entity.h"
#include "engine/render.h"
#include "engine/types.h"

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    UP_RIGHT,
    UP_LEFT,
    DOWN_RIGHT,
    DOWN_LEFT,
};

enum Pickup_Name { M44_PICKUP, BREWSTER_PICKUP };

enum Fire_Mode { AUTO, SEMI, BURST };

enum Player_Status {
    PLAYER_SPAWNING,
    PLAYER_ACTIVE,
    PLAYER_RELOADING,
    PLAYER_DESPAWNING,
    PLAYER_INACTIVE,
    PLAYER_CROUCHED,
};

enum Enemy_Status {
    ENEMY_ACTIVE,
    ENEMY_DESPAWNING,
    ENEMY_INACTIVE,
};

enum Pickup_Status { PICKUP_ACTIVE, PICKUP_INACTIVE, PICKUP_SPAWNING };

// used to define common weapon types
typedef struct weapon_type {
    char *name;
    enum Fire_Mode fire_mode;
    u16 capacity;      // max ammo in a magazine
    u16 reserve;       // maximum amount of spare ammo
    u16 max_fire_rate; // rounds per minute
    u16 burst_count;   // maximum number of shots in a "burst", both burst
                       // attributes will be null if Fire_Mode != BURST
    f32 burst_delay;   // in seconds
    i16 damage;
    i16 bullet_velocity;
    f32 aiming_scale_factor; // factor by which the rendering dimensions change
                             // when player is crouching
    Animation *hud_ammo_icon;
} Weapon_Type;

// contains weapon info as well as player-specific data
typedef struct weapon {
    char *name;
    enum Fire_Mode fire_mode;
    u16 capacity;
    u16 max_capacity;
    u16 reserve;
    u16 max_reserve;
    u16 max_fire_rate;
    i8 burst_shots_remaining;
    u16 burst_count;
    f32 burst_delay;
    i16 damage;
    i16 bullet_velocity;
    f32 aiming_scale_factor;
    u16 frames_since_last_shot;
    bool ready_to_fire;
    Animation *hud_ammo_icon;
} Weapon;

typedef struct pickup_animation_set {
    Animation *active;
    Animation *spawning;
} Pickup_Animation_Set;

typedef struct armor {
    char *name;
    i16 integrity;
} Armor;

typedef struct crosshair {
    Entity *entity;
    vec2 relative_position;
    vec2 percentage_of_screen; // x/y position in screen in terms of percentage
                               // of pixels in each direction (0.5, 0.5) would
                               // be center of screen
} Crosshair;

typedef struct bullet {
    Entity *entity;
    i32 damage;
} Bullet;

typedef struct camera {
    vec2 position;
    vec2 *target_position;
    vec4 buffer;
} Camera;

typedef struct player {
    Entity *entity;
    Camera *camera;
    Crosshair *crosshair;
    Weapon *weapon;
    Armor *armor;
    vec2 spawn_point;
    vec2 relative_position; // position relative to the rest of the map NOT to
                            // the window
    enum Direction direction;
    enum Player_Status status;
    f32 render_scale_factor; // render scale factor (determines FOV of the
                             // player). Normal is 0.5, render width is 0.5 of
                             // window width
    f32 despawn_time; // time it takes for animation to complete after health <=
                      // 0
    f32 spawn_delay;  // time in s from INACTIVE status to SPAWNING status
    f32 spawn_time;   // time in s from SPAWNING status to ACTIVE status
    u32 frames_on_status; // # of frames since last status change
    i16 health;
    bool is_left_player;
} Player;

typedef struct zombie {
    Entity *entity;
    enum Direction direction;
    enum Enemy_Status status;
    f32 despawn_time;
    u32 frames_on_status;
    i16 health;
} Zombie;

typedef struct pickup {
    Entity *entity;
    Pickup_Animation_Set *animation_set;
    enum Pickup_Name name;
    enum Pickup_Status status;
    f32 spawn_delay;
    f32 spawn_time;
    u32 frames_on_status;

} Pickup;

typedef struct prop {
    Sprite *sprite;      // sprite to render for this prop
    i32 layer_threshold; // if entity is ABOVE this y coordinate, the entity
                         // will render BEFORE this prop, and vice-versa
    usize
        num_static_bodies; // number of static bodies associated with this prop
    Static_Body **static_bodies; // holds the references of the static bodies
                                 // for this prop
} Prop;

typedef struct map {
    // these indicate the lengths of their respective arrays
    usize num_pickups;
    usize num_props;
    usize num_p1_spawns;
    usize num_p2_spawns;
    usize num_enemy_spawns;
    usize max_enemies;

    // used when calculating when to spawn enemies
    i32 enemy_spawn_delay;
    i32 frames_since_last_spawn;

    Pickup *pickups;               // start of pickups array
    Prop *props;                   // start of props array
    vec2 *player_one_spawn_points; // player one's spawn points
    vec2 *player_two_spawn_points; // player two's spawn points
    vec2 *enemy_spawn_points;
} Map;

typedef struct hud {
    SDL_Window *window;
    Sprite *p1_health_display;
    Sprite *p2_health_display;
} HUD;

typedef struct menu {
    void (*input_handler)(void);
    char items[MENU_MAX_LINES][MENU_MAX_LINE_LENGTH];
    u8 items_count;
    u8 selected_item;
} Menu;

#endif