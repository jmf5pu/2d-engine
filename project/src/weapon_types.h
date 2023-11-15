#ifndef WEAPON_TYPES_H
#define WEAPON_TYPES_H

#include "structs.h"

extern Weapon_Type *base;
extern Weapon_Type *m16;
extern Weapon_Type *m44;

void init_weapon_types(void);
void free_weapon_types(void);

#endif