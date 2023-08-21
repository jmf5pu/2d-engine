#ifndef STRUCTS_H
#define STRUCTS_H

#include "engine/entity.h"
#include "engine/types.h"
#include "engine/animation.h"

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum Weapon_Name
{
    RIFLE
};

typedef struct weapon
{
    enum Weapon_Name name;
    i8 capacity;
    i8 current_capacity;
    i8 max_fire_rate;
} Weapon;

typedef struct animation_set
{
    Animation *up_idle;
    Animation *up_moving;
    Animation *down_idle;
    Animation *down_moving;
    Animation *side_idle;
    Animation *side_moving;
} Animation_Set;

typedef struct player
{
    Entity *entity;
    Animation_Set *animation_set;
    Weapon *weapon;
    enum Direction direction;
    i8 health;
} Player;

#endif