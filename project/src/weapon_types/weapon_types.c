#include "weapon_types.h"
#include "../collision_behavior/collision_behavior.h"
#include "../engine/render.h"
#include "../main_helpers/main_helpers.h"

Weapon_Type *base;
Weapon_Type *m16;
Weapon_Type *glock;

void create_bullet_straight(Player *player)
{
    vec2 bullet_position = {player->relative_position[0], player->relative_position[1]};
    vec2 bullet_velocity = {0, 0};

    // Calculate starting position using angle
    vec2 bullet_start_offset = {0, 0};
    get_xy_components_from_vector(BULLET_DISTANCE_FROM_PLAYER, player->crosshair_angle, bullet_start_offset);
    vec2_add(bullet_position, bullet_position, bullet_start_offset);

    // Calculate velocity using angle
    get_xy_components_from_vector(player->weapon->bullet_velocity, player->crosshair_angle, bullet_velocity);

    // check which of 16 buckets it falls into, assign animation
    char *bullet_adef_name;
    bullet_adef_name = "bullet_0";

    // create bullet struct and calculated anim and velocity
    Bullet *bullet = malloc(sizeof(Bullet));
    bullet->entity = entity_create(bullet_position, (vec2){5, 5}, (vec2){0, 0}, COLLISION_LAYER_BULLET, bullet_mask, bullet_on_hit, bullet_on_hit_static);
    bullet->damage = player->weapon->damage;
    bullet->entity->animation = animation_create(adef_bullet_medium, true);

    vec2_dup(bullet->entity->body->velocity, bullet_velocity);
    bullet->entity->body->parent = bullet;
}

void base_on_shoot(Player *player) { return; }

void m16_on_shoot(Player *player) { create_bullet_straight(player); }

void glock_on_shoot(Player *player) { create_bullet_straight(player); }

void init_weapon_types(void)
{

    render_sprite_sheet_init(&sprite_sheet_556_burst, "assets/hud/556_burst.png", 20, 44);
    adef_556_burst = animation_definition_create(&sprite_sheet_556_burst, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_556_burst = animation_create(adef_556_burst, false);

    // init bullet anims
    render_sprite_sheet_init(&sprite_sheet_bullet_medium, "assets/wip/bullet_v2.png", 4, 4);
    adef_bullet_medium = animation_definition_create(&sprite_sheet_bullet_medium, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);

    // Weapons
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
    m16->on_shoot = m16_on_shoot;

    glock = malloc(sizeof(Weapon_Type));
    glock->name = "glock";
    glock->fire_mode = SEMI;
    glock->capacity = 15;
    glock->reserve = 900;
    glock->max_fire_rate = 1200;
    glock->damage = 15;
    glock->bullet_velocity = 600;
    glock->hud_ammo_icon = anim_556_burst; // placeholder, update
    glock->on_shoot = glock_on_shoot;
}

void free_weapon_types(void)
{
    free(base);
    free(m16);
    free(glock);
}