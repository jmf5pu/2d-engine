#ifndef PLAYER_H
#define PLAYER_H

#include "engine/entity.h"

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum Weapon
{
    RIFLE
};

typedef struct player
{
    Entity *entity;
    enum Direction direction;
    enum Weapon weapon;
    u8 health;
} Player;

#endif