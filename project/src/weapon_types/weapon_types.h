#ifndef WEAPON_TYPES_H
#define WEAPON_TYPES_H

#include "../structs.h"

extern Weapon_Type *base;
extern Weapon_Type *m16;
extern Weapon_Type *m44;

Sprite_Sheet sprite_sheet_556_burst;
Animation_Definition *adef_556_burst;
Animation *anim_556_burst;

void init_weapon_types(void);
void free_weapon_types(void);

#endif