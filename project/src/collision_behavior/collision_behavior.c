#include "collision_behavior.h"
#include "../effects/effects.h"
#include "../engine/animation.h"
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

void weapon_pickup_base(Body *self, Body *other, Animation_Definition *highlight_adef, vec2 anim_size, Weapon_Type *weapon_type)
{
    Player *player = get_player_from_body(other);
    if (self->first_frame_being_hit) {
        Entity *pickup_highlight = entity_create(self->aabb.position, anim_size, (vec2){0, 0}, 0, 0, NULL, NULL);
        pickup_highlight->animation = animation_create(highlight_adef, false);
        pickup_highlight->animation->z_index = 1;
        pickup_highlight->destroy_on_anim_completion = true;
    }

    if (player != NULL && player->input_state->key_state->use) {
        update_player_weapon(player, weapon_type);
        self->is_active = false;
    }
}

void m16_pickup_on_hit(Body *self, Body *other, Hit hit) { weapon_pickup_base(self, other, adef_m16_pickup_highlight, (vec2){20, 9}, m16); }

void glock_pickup_on_hit(Body *self, Body *other, Hit hit)
{
    Player *player = get_player_from_body(other);
    DynamicProp *pickup = self->parent;
    if (player) {
        pickup->colliding_player = player;
        pickup->state.pickup_state_enum = HIGHLIGHTING;
    }
    // weapon_pickup_base(self, other, adef_glock_pickup_highlight, (vec2){7, 9}, glock);
}

void coach_gun_pickup_on_hit(Body *self, Body *other, Hit hit) { weapon_pickup_base(self, other, adef_coach_gun_pickup_highlight, (vec2){25, 18}, coach_gun); }

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
}

void enemy_on_hit_static(Body *self, Static_Body *other, Hit hit) {}

// these aren't needed atm since pickups aren't moving around
void pickup_on_hit(Body *self, Body *other, Hit hit) {}

void pickup_on_hit_static(Body *self, Static_Body *other, Hit hit) {}

/// @brief Mark the bullet as inactive (will be destroyed next frame) when it hits any body
/// @param self
/// @param other
/// @param hit
void bullet_on_hit(Body *self, Body *other, Hit hit)
{
    if (other->collision_layer == COLLISION_LAYER_ENEMY) {
        Bullet *bullet = (Bullet *)self->parent;
        Zombie *zombie = (Zombie *)other->parent;
        if (other->is_active && self->is_active) {
            zombie->health -= bullet->damage;
            self->is_active = false;
        }

        // create blood splatter effect entity
        Entity *blood_splatter = entity_create(self->aabb.position, (vec2){13, 13}, (vec2){0, 0}, 0, 0, NULL, NULL);
        blood_splatter->destroy_on_anim_completion = true;
        blood_splatter->animation = animation_create(bullet->splatter_adef, false);
        blood_splatter->animation->z_index = zombie->entity->animation->z_index + 1;
    }
}

/// @brief Mark the bullet as inactive and create the impact effect's entity
/// @param self
/// @param other
/// @param hit
void bullet_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
    Bullet *bullet = (Bullet *)self->parent;
    create_bullet_impact_entity(self->aabb.position, bullet->impact_adef);
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
    bool is_interactable = teleporter_button->state.button_state_enum == UNPRESSED;

    if (is_interactable && self->first_frame_being_hit) { // TODO: pull this logic to a helper method
        Entity *button_highlight = entity_create(self->aabb.position, (vec2){TELEPORTER_BUTTON_DIMENSIONS[0], TELEPORTER_BUTTON_DIMENSIONS[1]}, (vec2){0, 0}, 0, 0, NULL, NULL);
        button_highlight->animation = animation_create(adef_teleporter_button_highlight, false);
        button_highlight->animation->z_index = 1;
        button_highlight->destroy_on_anim_completion = true;
    }

    if (is_interactable && player != NULL && player->input_state->key_state->use) { // TODO: pull this conditional to a helper method
        for (int i = 0; i < map.num_dynamic_props; i++) {
            if (map.dynamic_props[i]->type == TELEPORTER)
                map.dynamic_props[i]->state.teleporter_state_enum = SPINNING_UP;
        }
        teleporter_button->state.button_state_enum = PRESSED;
        teleporter_button->frames_on_state = 0;
    }
}