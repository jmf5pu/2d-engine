#ifndef COLLISION_BEHAVIOR_H
#define COLLISION_BEHAVIOR_H

#include "../engine/physics.h"

typedef enum collision_layer {
    COLLISION_LAYER_PLAYER = 1,
    COLLISION_LAYER_ENEMY = 1 << 1,
    COLLISION_LAYER_TERRAIN = 1 << 2,
    COLLISION_LAYER_BULLET = 1 << 3,
    COLLISION_LAYER_PICKUP = 1 << 4,
    COLLISION_LAYER_CROSSHAIR = 1 << 5,
} Collision_Layer;

// collision masks
extern const u8 enemy_mask;
extern const u8 player_mask;
extern const u8 bullet_mask;
extern const u8 pickup_mask;
extern const u8 crosshair_mask;

void player_on_hit(Body *self, Body *other, Hit hit);
void player_on_hit_static(Body *self, Static_Body *other, Hit hit);
void bullet_on_hit(Body *self, Body *other, Hit hit);
void bullet_on_hit_static(Body *self, Static_Body *other, Hit hit);
void enemy_on_hit(Body *self, Body *other, Hit hit);
void enemy_on_hit_static(Body *self, Static_Body *other, Hit hit);
void pickup_on_hit(Body *self, Body *other, Hit hit);
void pickup_on_hit_static(Body *self, Static_Body *other, Hit hit);

void m16_pickup_on_hit(Body *self, Body *other, Hit hit);
void glock_pickup_on_hit(Body *self, Body *other, Hit hit);

#endif