#include <assert.h>
#include "engine/physics.h"
#include "collision_behavior.h"
#include "structs.h"
#include "player_helpers.h"
#include "map_helpers.h"
#include "weapon_types.h"

const u8 enemy_mask = COLLISION_LAYER_PLAYER | COLLISION_LAYER_TERRAIN | COLLISION_LAYER_BULLET;
const u8 player_mask = COLLISION_LAYER_ENEMY | COLLISION_LAYER_TERRAIN | COLLISION_LAYER_BULLET | COLLISION_LAYER_PICKUP;
const u8 bullet_mask = COLLISION_LAYER_ENEMY | COLLISION_LAYER_TERRAIN;
const u8 pickup_mask = COLLISION_LAYER_PLAYER;
const u8 crosshair_mask = 0;

void player_on_hit(Body *self, Body *other, Hit hit)
{
    // make sure player_on_hit is only called on player physics bodies
    assert(sizeof(self->parent) == sizeof(Player *));
    Player *player = self->parent;

    if (other->collision_layer == COLLISION_LAYER_BULLET)
    {
        // all bullets should have a parent pointer populated
        assert(other->parent);
        assert(sizeof(other->parent) == sizeof(Bullet *));
        if (other->is_active && self->is_active)
        {
            Bullet *bullet = (Bullet *)other->parent;
            if (player->armor->integrity > 0)
            {
                // Apply as much damage as possible to the armor
                if (player->armor->integrity >= bullet->damage)
                {
                    player->armor->integrity -= bullet->damage;
                }
                else
                {
                    player->health -= (bullet->damage - player->armor->integrity);
                    player->armor->integrity = 0;
                }
            }
            else
            {
                // If the armor is already 0, apply damage directly to health
                player->health -= bullet->damage;
            }
            other->is_active = false;
            free(bullet);
        }
    }

    // prevents players from pushing through enemies
    if (other->collision_layer == COLLISION_LAYER_ENEMY && other->is_active && self->is_active)
    {
        vec2_add(self->aabb.position, self->aabb.position, hit.normal);
    }

    if (other->collision_layer == COLLISION_LAYER_PICKUP && other->is_active && self->is_active)
    {
        Pickup *pickup = get_pickup_from_body(other);
        if (pickup->name == M44_PICKUP && pickup->status == PICKUP_ACTIVE)
        {
            // update player weapon
            player->weapon->name = m44->name;
            player->weapon->fire_mode = m44->fire_mode;
            player->weapon->capacity = m44->capacity;
            player->weapon->max_capacity = m44->capacity;
            player->weapon->reserve = m44->reserve;
            player->weapon->max_reserve = m44->reserve;
            player->weapon->max_fire_rate = m44->max_fire_rate;
            player->weapon->damage = m44->damage;
            player->weapon->bullet_velocity = m44->bullet_velocity;
            player->weapon->aiming_scale_factor = m44->aiming_scale_factor;
            player->weapon->frames_since_last_shot = 0;
            player->weapon->ready_to_fire = true;
        }
        else if (pickup->name == BREWSTER_PICKUP && pickup->status == PICKUP_ACTIVE)
        {

            // apply armor to player
            player->armor->name = "brewster";
            player->armor->integrity = 200;
        }

        // deactivate pickup and start respawn timer
        pickup->entity->body->is_active = false;
        pickup->status = PICKUP_INACTIVE;
        pickup->frames_on_status = 0;
    }
}

void player_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
}

void bullet_on_hit(Body *self, Body *other, Hit hit)
{
    // // mark for body (and entity) for destruction
    // if (other->is_active)
    // {
    //     self->is_active = false;
    // }
}

void bullet_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
    // all bullet bodies should have a pointer to their parent struct
    assert(self->parent);
    assert(sizeof(self->parent) == sizeof(Bullet *));

    // mark for body (and entity) for destruction
    self->is_active = false;

    // free parent struct
    free(self->parent);
}

void enemy_on_hit(Body *self, Body *other, Hit hit)
{
    // every enemy body should have an associated enemy struct
    assert(self->parent);
    assert(sizeof(self->parent) == sizeof(Zombie *));

    Zombie *zombie = self->parent;

    // prevent enemy from overlapping with player
    if (other->collision_layer == COLLISION_LAYER_PLAYER)
    {
        vec2_add(self->aabb.position, self->aabb.position, hit.normal);
    }

    // update enemy health on bullet collisions
    if (other->collision_layer == COLLISION_LAYER_BULLET)
    {
        assert(other->parent);
        assert(sizeof(other->parent) == sizeof(Bullet *));
        Bullet *bullet = (Bullet *)other->parent;
        if (other->is_active && self->is_active)
        {
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
void pickup_on_hit(Body *self, Body *other, Hit hit)
{
}

void pickup_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
}

// not needed atm
void crosshair_on_hit(Body *self, Body *other, Hit hit)
{
}
void crosshair_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
}
