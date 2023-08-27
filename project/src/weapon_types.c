#include "weapon_types.h"

Weapon_Type m16;
Weapon_Type m44;

void init_weapon_types()
{
    m16.name = M16;
    m16.fire_mode = AUTO;
    m16.capacity = 30;
    m16.max_fire_rate = 800;
    m16.damage = 34;

    m44.name = M44;
    m44.fire_mode = SEMI;
    m44.capacity = 5;
    m44.max_fire_rate = 20;
    m44.damage = 80;
}