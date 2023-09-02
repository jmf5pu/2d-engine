#include "weapon_types.h"

Weapon_Type m16;
Weapon_Type m44;

void init_weapon_types()
{
    m16.name = M16;
    m16.fire_mode = BURST;
    m16.capacity = 30;
    m16.max_fire_rate = 900; // rounds per minute
    m16.burst_count = 3;
    m16.burst_delay = 0.4; // seconds
    m16.damage = 30;
    m16.bullet_velocity = 1500;

    m44.name = M44;
    m44.fire_mode = SEMI;
    m44.capacity = 5;
    m44.max_fire_rate = 30;
    m44.damage = 100;
    m44.bullet_velocity = 2000;
}