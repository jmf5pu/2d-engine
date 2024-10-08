#include "weapon_types.h"

#include "../collision_behavior/collision_behavior.h"
#include "../effects/effects.h"
#include "../engine/audio/audio.h"
#include "../engine/render.h"
#include "../main_helpers/main_helpers.h"

Weapon_Type *base;
Weapon_Type *m16;
Weapon_Type *glock;
Weapon_Type *coach_gun;

void create_bullet_straight(Player *player, f32 angle)
{
    vec2 bullet_position = {player->relative_position[0], player->relative_position[1]};
    vec2 bullet_velocity = {0, 0};

    // Calculate starting position using angle
    vec2 bullet_start_offset = {0, 0};
    get_xy_components_from_vector(BULLET_DISTANCE_FROM_PLAYER, angle, bullet_start_offset);
    vec2_add(bullet_position, bullet_position, bullet_start_offset);

    // Calculate velocity using angle
    get_xy_components_from_vector(player->weapon->weapon_type->bullet_velocity, angle, bullet_velocity);

    // create bullet struct and calculated anim and velocity
    Bullet *bullet = malloc(sizeof(Bullet));
    bullet->entity = entity_create(bullet_position, (vec2){5, 5}, (vec2){0, 0}, COLLISION_LAYER_BULLET, bullet_mask, bullet_on_hit, bullet_on_hit_static);
    bullet->impact_adef = player->weapon->weapon_type->bullet_impact_adef;
    bullet->splatter_adef = get_blood_splatter_adef(player->weapon->weapon_type->blood_splatter_prefix);
    bullet->damage = player->weapon->weapon_type->damage;
    bullet->entity->animation = animation_create(player->weapon->weapon_type->bullet_adef, true);
    vec2_dup(bullet->entity->body->velocity, bullet_velocity);
    bullet->entity->body->parent = bullet;
}

void create_scatter_shot(Player *player, f32 spread_angle, u8 shot_count)
{
    f32 angle_step = spread_angle / (shot_count - 1);
    f32 angle = player->crosshair_angle - (spread_angle / 2);

    for (int i = 0; i < shot_count; i++) {
        create_bullet_straight(player, angle);
        angle += angle_step;
    }
}

void base_on_shoot(Player *player) { return; }

void m16_on_shoot(Player *player)
{
    create_player_muzzle_flash_effect(player);
    create_player_brass_effect(player, adef_brass_falling_1);
    create_bullet_straight(player, player->crosshair_angle);
    play_audio_sound(player->weapon->weapon_type->shoot_chunk);
}

void glock_on_shoot(Player *player)
{
    create_player_muzzle_flash_effect(player);
    create_player_brass_effect(player, adef_brass_falling_1);
    create_bullet_straight(player, player->crosshair_angle);
    play_audio_sound(player->weapon->weapon_type->shoot_chunk);
}

void coach_gun_on_shoot(Player *player)
{
    const f32 scatter_angle = 0.35; // 20 degrees in radians //0.5236; // 30 degrees in radians
    const u8 num_shots = 7;
    create_player_muzzle_flash_effect(player);
    create_scatter_shot(player, scatter_angle, num_shots);
    play_audio_sound(player->weapon->weapon_type->shoot_chunk);
}

// when modifying weapon types be sure to update weapon_type and weapon structs as well as update_player_weapon
void init_weapon_types(void)
{
    // TODO: hud sprites, put this elsewhere
    // render_sprite_sheet_init(&sprite_sheet_556_burst, "assets/hud/556_burst.png", 20, 44);
    // adef_556_burst = animation_definition_create(&sprite_sheet_556_burst, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    // anim_556_burst = animation_create(adef_556_burst, false);

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
    m16->reload_frame_delay = 60;
    m16->pickup_frame_delay = 120;
    m16->muzzle_flash_id = "1";
    m16->bullet_adef = adef_bullet_medium;
    m16->bullet_impact_adef = adef_bullet_impact_medium;
    m16->blood_splatter_prefix = "blood_splatter_";
    m16->hud_ammo_icon = anim_556_burst;
    m16->on_shoot = m16_on_shoot;
    load_audio_sound(&m16->shoot_chunk, "assets/audio/gunshots/556.wav");

    glock = malloc(sizeof(Weapon_Type));
    glock->name = "glock";
    glock->fire_mode = SEMI;
    glock->capacity = 15;
    glock->reserve = 900;
    glock->max_fire_rate = 1200;
    glock->damage = 15;
    glock->bullet_velocity = 600;
    glock->reload_frame_delay = 90;
    glock->pickup_frame_delay = 120;
    glock->muzzle_flash_id = "2";
    glock->bullet_adef = adef_bullet_small;
    glock->bullet_impact_adef = adef_bullet_impact_small;
    glock->blood_splatter_prefix = "blood_splatter_";
    glock->hud_ammo_icon = anim_556_burst; // placeholder, update
    glock->on_shoot = glock_on_shoot;
    load_audio_sound(&glock->shoot_chunk, "assets/audio/gunshots/9mm.wav");

    coach_gun = malloc(sizeof(Weapon_Type));
    coach_gun->name = "coach_gun";
    coach_gun->fire_mode = SEMI;
    coach_gun->capacity = 2;
    coach_gun->reserve = 900;
    coach_gun->max_fire_rate = 400;
    coach_gun->damage = 15;
    coach_gun->bullet_velocity = 600;
    coach_gun->reload_frame_delay = 120;
    coach_gun->pickup_frame_delay = 120;
    coach_gun->muzzle_flash_id = "2";
    coach_gun->bullet_adef = adef_bullet_small;
    coach_gun->bullet_impact_adef = adef_bullet_impact_medium;
    coach_gun->blood_splatter_prefix = "blood_splatter_";
    coach_gun->hud_ammo_icon = anim_556_burst; // placeholder, update
    coach_gun->on_shoot = coach_gun_on_shoot;
    load_audio_sound(&coach_gun->shoot_chunk, "assets/audio/gunshots/20ga.wav");
}

void free_weapon_types(void)
{
    free(base);
    free(m16);
    free(glock);
    free(coach_gun);
}