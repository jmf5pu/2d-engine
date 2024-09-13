#ifndef ENEMY_HELPERS_H
#define ENEMY_HELPERS_H

#include "../structs.h"

#define SPAWN_ENEMIES true
#define ZOMBIE_MOVEMENT_SPEED 250
#define NUM_ENEMY_TYPES 1
#define NUM_ENEMY_STATES 2
#define NUM_ENEMY_DIRECTIONS 4
#define ENEMY_ADEF_COUNT NUM_ENEMY_TYPES *NUM_ENEMY_STATES *NUM_ENEMY_DIRECTIONS

Sprite_Sheet sprite_sheet_zombie_idle_1;
Sprite_Sheet sprite_sheet_zombie_idle_2;
Sprite_Sheet sprite_sheet_zombie_idle_3;
Sprite_Sheet sprite_sheet_zombie_idle_4;
Sprite_Sheet sprite_sheet_zombie_moving_1;
Sprite_Sheet sprite_sheet_zombie_moving_2;
Sprite_Sheet sprite_sheet_zombie_moving_3;
Sprite_Sheet sprite_sheet_zombie_moving_4;

Animation_Definition *adef_zombie_idle_1;
Animation_Definition *adef_zombie_idle_2;
Animation_Definition *adef_zombie_idle_3;
Animation_Definition *adef_zombie_idle_4;
Animation_Definition *adef_zombie_moving_1;
Animation_Definition *adef_zombie_moving_2;
Animation_Definition *adef_zombie_moving_3;
Animation_Definition *adef_zombie_moving_4;

void init_enemies(usize item_size, usize initial_capacity);
void create_enemy(vec2 spawn_point);
Array_List *get_all_enemies(void);

void update_enemy_anim(Zombie *zombie);
void render_enemy_shadows(void);
void init_enemy_adef_hashmap(void);
void init_enemy_adefs(void);

#endif