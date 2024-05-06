#include "../engine/animation.h"
#include "../engine/entity.h"
#include "../engine/render.h"

#define EXPLOSION_COUNT 1
#define ANGLES 16

// character shadow
Sprite_Sheet sprite_sheet_character_shadow;
Animation_Definition *adef_character_shadow;
Animation *anim_character_shadow;

// brass
Sprite_Sheet sprite_sheet_brass_falling_1;
Animation_Definition *adef_brass_falling_1;

// bullet impact
const u8 BULLET_IMPACT_DIMENSIONS[] = {5, 5};
Sprite_Sheet sprite_sheet_bullet_impact_0;
Animation_Definition *adef_bullet_impact_0;

// muzzle flash
const u8 MUZZLE_FLASH_DIMENSIONS[] = {19, 19};
const f32 MUZZLE_FLASH_DURATIONS[] = {0.005, 0.005, 0.005, 0.01, 0.01, 0.01};
const u8 MUZZLE_FLASH_ROWS[] = {0, 0, 0, 0, 0, 0};
const u8 MUZZLE_FLASH_COLS[] = {0, 1, 2, 3, 4, 5};
const u8 MUZZLE_FLASH_FRAME_COUNT = 6;
Sprite_Sheet sprite_sheet_muzzle_flash_0;
Sprite_Sheet sprite_sheet_muzzle_flash_1;
Sprite_Sheet sprite_sheet_muzzle_flash_2;
Sprite_Sheet sprite_sheet_muzzle_flash_3;
Sprite_Sheet sprite_sheet_muzzle_flash_4;
Sprite_Sheet sprite_sheet_muzzle_flash_5;
Sprite_Sheet sprite_sheet_muzzle_flash_6;
Sprite_Sheet sprite_sheet_muzzle_flash_7;
Sprite_Sheet sprite_sheet_muzzle_flash_8;
Sprite_Sheet sprite_sheet_muzzle_flash_9;
Sprite_Sheet sprite_sheet_muzzle_flash_10;
Sprite_Sheet sprite_sheet_muzzle_flash_11;
Sprite_Sheet sprite_sheet_muzzle_flash_12;
Sprite_Sheet sprite_sheet_muzzle_flash_13;
Sprite_Sheet sprite_sheet_muzzle_flash_14;
Sprite_Sheet sprite_sheet_muzzle_flash_15;
Animation_Definition *adef_muzzle_flash_0;
Animation_Definition *adef_muzzle_flash_1;
Animation_Definition *adef_muzzle_flash_2;
Animation_Definition *adef_muzzle_flash_3;
Animation_Definition *adef_muzzle_flash_4;
Animation_Definition *adef_muzzle_flash_5;
Animation_Definition *adef_muzzle_flash_6;
Animation_Definition *adef_muzzle_flash_7;
Animation_Definition *adef_muzzle_flash_8;
Animation_Definition *adef_muzzle_flash_9;
Animation_Definition *adef_muzzle_flash_10;
Animation_Definition *adef_muzzle_flash_11;
Animation_Definition *adef_muzzle_flash_12;
Animation_Definition *adef_muzzle_flash_13;
Animation_Definition *adef_muzzle_flash_14;
Animation_Definition *adef_muzzle_flash_15;

void init_brass_animation_definitions(void);
void init_bullet_impact_animation_definitions(void);
void init_explosion_animation_definitions(void);
void init_character_shadow_anim(void);
void init_explosion_adef_hashmap(void);
void create_muzzle_flash_entity(f32 angle, vec2 position, vec2 size, vec2 velocity, u8 collision_layer, u8 collision_mask, On_Hit on_hit, On_Hit_Static on_hit_static);
void create_bullet_impact_entity(vec2 position, Animation_Definition *adef);
void create_brass_entity(vec2 position, Animation_Definition *adef, i32 z_index);
void brass_movement(Entity *entity);