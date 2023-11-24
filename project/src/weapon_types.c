#include "weapon_types.h"
#include "engine/render.h"

Weapon_Type *base;
Weapon_Type *m16;
Weapon_Type *m44;

void init_weapon_types(void)
{
    base = malloc(sizeof(Weapon_Type));
    base->name = "base";
    base->fire_mode = AUTO;
    base->capacity = 0;
    base->reserve = 0;
    base->max_fire_rate = 1;
    base->damage = 0;
    base->bullet_velocity = 0;
    base->aiming_scale_factor = 1.2; // DEFAULT_RENDER_SCALE_FACTOR;

    m16 = malloc(sizeof(Weapon_Type));
    m16->name = "m16";
    m16->fire_mode = BURST;
    m16->capacity = 30;
    m16->reserve = 60;
    m16->max_fire_rate = 900; // rounds per minute
    m16->burst_count = 3;
    m16->burst_delay = 0.4; // seconds
    m16->damage = 30;
    m16->bullet_velocity = 1500;
    m16->aiming_scale_factor = 1.2;

    m44 = malloc(sizeof(Weapon_Type));
    m44->name = "m44";
    m44->fire_mode = SEMI;
    m44->capacity = 5;
    m44->reserve = 10;
    m44->max_fire_rate = 30;
    m44->damage = 100;
    m44->bullet_velocity = 2000;
    m44->aiming_scale_factor = 0.6;
}

void free_weapon_types(void)
{
    free(base);
    free(m16);
    free(m44);
}