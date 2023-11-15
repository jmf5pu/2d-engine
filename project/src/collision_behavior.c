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
    // TODO: update this - temp fix because bullets are only being created from other players right now
    // need to create bullet struct that contains information on damage
    Player *player = get_player_from_body(player_one, player_two, self, false);

    if (SPLIT_SCREEN)
    {
        Player *other_player = get_player_from_body(player_one, player_two, self, true);
        if (other->collision_layer == COLLISION_LAYER_BULLET && other->is_active && self->is_active)
        {
            i8 bullet_damage = other_player->weapon->damage; // TODO: eventually may need to attach this value to a bullet struct
            if (player->armor->integrity > 0)
            {
                // Apply as much damage as possible to the armor
                if (player->armor->integrity >= bullet_damage)
                {
                    player->armor->integrity -= bullet_damage;
                }
                else
                {
                    player->health -= (bullet_damage - player->armor->integrity);
                    player->armor->integrity = 0;
                }
            }
            else
            {
                // If the armor is already 0, apply damage directly to health
                player->health -= bullet_damage;
            }
            other->is_active = false; // always mark bullet as inactive
        }
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
    // mark for body (and entity) for destruction
    if (other->is_active)
    {
        self->is_active = false;
    }
}

void bullet_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
    // mark for body (and entity) for destruction
    self->is_active = false;
}

void enemy_on_hit(Body *self, Body *other, Hit hit)
{
}

void enemy_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
    if (hit.normal[0] > 0)
    {
        self->velocity[0] = 400;
    }
    if (hit.normal[0] < 0)
    {
        self->velocity[0] = -400;
    }
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
