#ifndef WEAPON_TYPES_H
#define WEAPON_TYPES_H

#include "../engine/animation.h"
#include "../player_helpers/player_structs.h"
#include "../structs.h"

#define BULLET_DISTANCE_FROM_PLAYER 40

enum Fire_Mode { AUTO, SEMI, BURST };

typedef struct player Player;

typedef void (*OnShoot)(Player *player);
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
    Animation *hud_ammo_icon;
    OnShoot on_shoot; // handles bullet entity creation when the weapon is fired
} Weapon_Type;

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
    u16 frames_since_last_shot;
    bool ready_to_fire;
    bool is_firing;
    Animation *hud_ammo_icon;
    Animation *character_anim;
    vec2 position;
    OnShoot on_shoot;
} Weapon;

extern Weapon_Type *base;
extern Weapon_Type *m16;
extern Weapon_Type *glock;

// bullet sprite sheets/animation definitions
Sprite_Sheet sprite_sheet_bullet_medium;
Animation_Definition *adef_bullet_medium;

Sprite_Sheet sprite_sheet_556_burst;
Animation_Definition *adef_556_burst;
Animation *anim_556_burst;

void init_weapon_types(void);
void free_weapon_types(void);

#endif