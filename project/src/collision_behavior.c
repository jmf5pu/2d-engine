#include "engine/physics.h"
#include "collision_behavior.h"
#include "structs.h"
#include "player_helpers.h"
#include "map_helpers.h"
#include "weapon_types.h"

const u8 enemy_mask = COLLISION_LAYER_PLAYER | COLLISION_LAYER_TERRIAN | COLLISION_LAYER_BULLET;
const u8 player_mask = COLLISION_LAYER_ENEMY | COLLISION_LAYER_TERRIAN | COLLISION_LAYER_BULLET | COLLISION_LAYER_PICKUP;
const u8 bullet_mask = COLLISION_LAYER_ENEMY | COLLISION_LAYER_TERRIAN;
const u8 pickup_mask = COLLISION_LAYER_PLAYER;

void player_on_hit(Body *self, Body *other, Hit hit)
{
    Player *player = get_player_from_body(player_one, player_two, self);
    if (other->collision_layer == COLLISION_LAYER_BULLET && other->is_active && self->is_active)
    {
        player->health -= 50;     // TODO: attach this value to a bullet struct
        other->is_active = false; // always mark bullet as inactive
    }

    else if (other->collision_layer == COLLISION_LAYER_PICKUP && other->is_active && self->is_active)
    {
        Pickup *pickup = get_pickup_from_body(other);
        if (pickup->name == M44_PICKUP)
        {
            player->weapon->name = m44.name;
            player->weapon->fire_mode = m44.fire_mode;
            player->weapon->capacity = m44.capacity;
            player->weapon->current_capacity = m44.capacity;
            player->weapon->max_fire_rate = m44.max_fire_rate;
            player->weapon->frames_since_last_shot = 0;
            player->weapon->ready_to_fire = true;
        }

        pickup->entity->body->is_active = false;
        // TODO: implement respawn logic, timer etc
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