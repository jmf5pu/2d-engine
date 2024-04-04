#include "weapon_types.h"
#include "../engine/render.h"

Weapon_Type *base;
Weapon_Type *m16;
Weapon_Type *glock;

void init_weapon_types(void)
{

    render_sprite_sheet_init(&sprite_sheet_556_burst, "assets/hud/556_burst.png", 20, 44);
    adef_556_burst = animation_definition_create(&sprite_sheet_556_burst, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_556_burst = animation_create(adef_556_burst, false);

    base = malloc(sizeof(Weapon_Type));
    base->name = "base";
    base->fire_mode = AUTO;
    base->capacity = 0;
    base->reserve = 0;
    base->max_fire_rate = 1;
    base->damage = 0;
    base->bullet_velocity = 0;
    base->hud_ammo_icon = NULL;

    m16 = malloc(sizeof(Weapon_Type));
    m16->name = "m16";
    m16->fire_mode = BURST;
    m16->capacity = 30;
    m16->reserve = 900;
    m16->max_fire_rate = 800; // rounds per minute
    m16->burst_count = 3;
    m16->burst_delay = 0.3; // seconds
    m16->damage = 30;
    m16->bullet_velocity = 800;
    m16->hud_ammo_icon = anim_556_burst;

    glock = malloc(sizeof(Weapon_Type));
    glock->name = "glock";
    glock->fire_mode = SEMI;
    glock->capacity = 15;
    glock->reserve = 900;
    glock->max_fire_rate = 1200;
    glock->damage = 15;
    glock->bullet_velocity = 600;
    glock->hud_ammo_icon = anim_556_burst; // placeholder, update
}

void free_weapon_types(void)
{
    free(base);
    free(m16);
    free(glock);
}