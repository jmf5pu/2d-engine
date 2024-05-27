#ifndef ENEMY_HELPERS_H
#define ENEMY_HELPERS_H

#include "../structs.h"

#define SPAWN_ENEMIES true
#define ZOMBIE_MOVEMENT_SPEED 100

void init_enemies(usize item_size, usize initial_capacity);
void create_enemy(vec2 spawn_point);
Array_List *get_all_enemies(void);

#endif