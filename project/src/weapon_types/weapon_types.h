#ifndef WEAPON_TYPES_H
#define WEAPON_TYPES_H

#include "../engine/animation.h"
#include "../player_helpers/player_helpers.h"
#include "../structs.h"

#define BULLET_DISTANCE_FROM_PLAYER 40

extern Weapon_Type *base;
extern Weapon_Type *m16;
extern Weapon_Type *glock;
extern Weapon_Type *coach_gun;

// bullet sprite sheets/animation definitions
Sprite_Sheet sprite_sheet_bullet_medium;
Animation_Definition *adef_bullet_medium;

Sprite_Sheet sprite_sheet_556_burst;
Animation_Definition *adef_556_burst;
Animation *anim_556_burst;

void init_weapon_types(void);
void free_weapon_types(void);
void create_bullet_straight(Player *player, f32 angle);
void create_scatter_shot(Player *player, f32 spread_angle, u8 shot_count);

#endif