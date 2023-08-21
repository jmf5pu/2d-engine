#ifndef STRUCTS_H
#define STRUCTS_H

#include "engine/entity.h"
#include "engine/types.h"

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

typedef struct player
{
    Entity *entity;
    Weapon *weapon;
    enum Direction direction;
    i8 health;
} Player;

#endif