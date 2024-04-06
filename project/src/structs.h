#ifndef STRUCTS_H
#define STRUCTS_H

#define MENU_MAX_LINES 10
#define MENU_MAX_LINE_LENGTH 50

#include "engine/animation.h"
#include "engine/entity.h"
#include "engine/input/input.h"
#include "engine/render.h"
#include "engine/types.h"
//#include "weapon_types/weapon_types.h"

enum Pickup_Name { M44_PICKUP, BREWSTER_PICKUP };

enum Player_Status {
    PLAYER_SPAWNING,
    PLAYER_ACTIVE,
    PLAYER_RELOADING,
    PLAYER_DESPAWNING,
    PLAYER_INACTIVE,
};

enum Enemy_Status {
    ENEMY_ACTIVE,
    ENEMY_DESPAWNING,
    ENEMY_INACTIVE,
};

enum Pickup_Status { PICKUP_ACTIVE, PICKUP_INACTIVE, PICKUP_SPAWNING };

typedef struct pickup_animation_set {
    Animation *active;
    Animation *spawning;
} Pickup_Animation_Set;

typedef struct armor {
    char *name;
    i16 integrity;
} Armor;

typedef struct bullet {
    Entity *entity;
    i32 damage;
} Bullet;

typedef struct camera {
    vec2 position;
    vec2 *target_position;
    vec4 buffer;
} Camera;

typedef struct zombie {
    Entity *entity;
    enum Enemy_Status status;
    f32 despawn_time;
    u32 frames_on_status;
    i16 health;
} Zombie;

typedef struct hud {
    SDL_Window *window;
    Sprite_Sheet_Frame *p1_health_display;
    Sprite_Sheet_Frame *p2_health_display;
} HUD;

typedef struct menu {
    void (*input_handler)(void);
    char items[MENU_MAX_LINES][MENU_MAX_LINE_LENGTH];
    u8 items_count;
    u8 selected_item;
} Menu;

#endif