#include "collision_behavior.h"
#include "../engine/physics.h"
#include "../map_helpers/map_helpers.h"
#include "../player_helpers/player_helpers.h"
#include "../structs.h"
#include "../weapon_types/weapon_types.h"
#include <assert.h>

const u8 enemy_mask = COLLISION_LAYER_PLAYER | COLLISION_LAYER_TERRAIN | COLLISION_LAYER_BULLET;
const u8 player_mask = COLLISION_LAYER_ENEMY | COLLISION_LAYER_TERRAIN | COLLISION_LAYER_PICKUP;
const u8 bullet_mask = COLLISION_LAYER_ENEMY | COLLISION_LAYER_TERRAIN;
const u8 pickup_mask = COLLISION_LAYER_PLAYER;
const u8 crosshair_mask = 0;

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

// for bullets, always mark as inactive when they hit another body
void bullet_on_hit(Body *self, Body *other, Hit hit)
{
    // mark for body (and entity) for destruction
    if (other->is_active) {
        self->is_active = false;
    }
}

void bullet_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
    // all bullet bodies should have a pointer to their parent struct
    assert(self->parent);
    assert(sizeof(self->parent) == sizeof(Bullet *));

    // mark for body (and entity) for destruction
    self->is_active = false;
}