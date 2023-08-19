#ifndef STRUCTS_H
#define STRUCTS_H

#include "engine/entity.h"

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
    u8 capacity;
    u8 current_capacity;
    u8 max_fire_rate;
} Weapon;

typedef struct player
{
    Entity *entity;
    Weapon *weapon;
    enum Direction direction;
    u8 health;
} Player;

#endif