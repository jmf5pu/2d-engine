#include "collision_behavior.h"
#include "../effects/effects.h"
#include "../engine/physics.h"
#include "../map_helpers/map_helpers.h"
#include "../player_helpers/player_helpers.h"
#include "../structs.h"
#include "../weapon_types/weapon_types.h"
#include <assert.h>

const u8 enemy_mask = COLLISION_LAYER_PLAYER | COLLISION_LAYER_TERRAIN | COLLISION_LAYER_BULLET;
const u8 player_mask = COLLISION_LAYER_ENEMY | COLLISION_LAYER_TERRAIN | COLLISION_LAYER_PICKUP | COLLISION_LAYER_BUTTON;
const u8 bullet_mask = COLLISION_LAYER_ENEMY | COLLISION_LAYER_TERRAIN;
const u8 pickup_mask = COLLISION_LAYER_PLAYER;
const u8 crosshair_mask = 0;

/// @brief updates all the attributes of the player's weapon to the specified weapon type
/// @param player relevant player
/// @param weapon_type new weapon_type
void update_player_weapon(Player *player, Weapon_Type *weapon_type)
{
    player->weapon->name = weapon_type->name;
    player->weapon->fire_mode = weapon_type->fire_mode;
    player->weapon->capacity = weapon_type->capacity;
    player->weapon->max_capacity = weapon_type->capacity;
    player->weapon->reserve = weapon_type->reserve;
    player->weapon->max_reserve = weapon_type->reserve;
    player->weapon->max_fire_rate = weapon_type->max_fire_rate;
    player->weapon->damage = weapon_type->damage;
    player->weapon->bullet_velocity = weapon_type->bullet_velocity;
    player->weapon->burst_count = weapon_type->burst_count;
    player->weapon->burst_shots_remaining = weapon_type->burst_count;
    player->weapon->burst_delay = weapon_type->burst_delay;
    player->weapon->frames_since_last_shot = 0;
    player->weapon->hud_ammo_icon = weapon_type->hud_ammo_icon;
    player->weapon->ready_to_fire = true;
    player->weapon->is_firing = false;
    player->weapon->on_shoot = weapon_type->on_shoot;
}

void weapon_pickup_base(Body *self, Body *other, Weapon_Type *weapon_type)
{
    Player *player = NULL;
    if (other == player_one->entity->body)
        player = player_one;
    else if (other == player_two->entity->body)
        player = player_two;

    if (player) {
        update_player_weapon(player, weapon_type);
        self->is_active = false;
    }
}

void m16_pickup_on_hit(Body *self, Body *other, Hit hit) { weapon_pickup_base(self, other, m16); }

void glock_pickup_on_hit(Body *self, Body *other, Hit hit) { weapon_pickup_base(self, other, glock); }

void player_on_hit(Body *self, Body *other, Hit hit)
{
    // make sure player_on_hit is only called on player physics bodies
    assert(sizeof(self->parent) == sizeof(Player *));
    Player *player = self->parent;

    if (other->collision_layer == COLLISION_LAYER_BULLET) {
        // all bullets should have a parent pointer populated
        assert(other->parent);
        assert(sizeof(other->parent) == sizeof(Bullet *));
        if (other->is_active && self->is_active) {
            Bullet *bullet = (Bullet *)other->parent;
            if (player->armor->integrity > 0) {
                // Apply as much damage as possible to the armor
                if (player->armor->integrity >= bullet->damage) {
                    player->armor->integrity -= bullet->damage;
                }
                else {
                    player->health -= (bullet->damage - player->armor->integrity);
                    player->armor->integrity = 0;
                }
            }
            else {
                // If the armor is already 0, apply damage
                // directly to health
                player->health -= bullet->damage;
            }
            other->is_active = false;
        }
    }

    // prevents players from pushing through enemies
    if (other->collision_layer == COLLISION_LAYER_ENEMY && other->is_active && self->is_active) {
        vec2_add(self->aabb.position, self->aabb.position, hit.normal);
    }
}

void player_on_hit_static(Body *self, Static_Body *other, Hit hit) {}

void enemy_on_hit(Body *self, Body *other, Hit hit)
{
    // every enemy body should have an associated enemy struct
    assert(self->parent);
    assert(sizeof(self->parent) == sizeof(Zombie *));

    Zombie *zombie = self->parent;

    // prevent enemy from overlapping with player
    if (other->collision_layer == COLLISION_LAYER_PLAYER) {
        vec2_add(self->aabb.position, self->aabb.position, hit.normal);
    }

    // update enemy health on bullet collisions
    if (other->collision_layer == COLLISION_LAYER_BULLET) {
        assert(other->parent);
        assert(sizeof(other->parent) == sizeof(Bullet *));
        Bullet *bullet = (Bullet *)other->parent;
        if (other->is_active && self->is_active) {
            zombie->health -= bullet->damage;
            other->is_active = false;
            free(bullet);
        }
    }
}

void enemy_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
    // if (hit.normal[0] > 0)
    // {
    //     self->velocity[0] = 400;
    // }
    // if (hit.normal[0] < 0)
    // {
    //     self->velocity[0] = -400;
    // }
}

// these aren't needed atm since pickups aren't moving around
void pickup_on_hit(Body *self, Body *other, Hit hit) {}

void pickup_on_hit_static(Body *self, Static_Body *other, Hit hit) {}

/// @brief Mark the bullet as inactive (will be destroyed next frame) when it hits any body
/// @param self
/// @param other
/// @param hit
void bullet_on_hit(Body *self, Body *other, Hit hit)
{
    if (other->is_active)
        self->is_active = false;
}

/// @brief Mark the bullet as inactive and create the impact effect's entity
/// @param self
/// @param other
/// @param hit
void bullet_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
    create_bullet_impact_entity(self->aabb.position, adef_bullet_impact_0);
    self->is_active = false;
}

/// @brief Check if the player is interacting with button and if so, spin up all props marked as teleporters and update button state
/// @param self
/// @param other
/// @param hit
void teleporter_button_on_hit(Body *self, Body *other, Hit hit)
{
    Player *player = get_player_from_body(other);
    DynamicProp *teleporter_button = self->parent;

    if (teleporter_button->state.button_state_enum == UNPRESSED && player != NULL && player->input_state->key_state->use) {
        for (int i = 0; i < map.num_dynamic_props; i++) {
            if (map.dynamic_props[i]->type == TELEPORTER)
                map.dynamic_props[i]->state.teleporter_state_enum = SPINNING_UP;
        }
        teleporter_button->state.button_state_enum = PRESSED;
        teleporter_button->frames_on_state = 0;
    }
}