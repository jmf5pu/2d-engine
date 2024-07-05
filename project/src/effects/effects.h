#ifndef EFFECTS_H
#define EFFECTS_H

#include "../engine/animation.h"
#include "../engine/entity.h"
#include "../engine/render.h"
#include "../structs.h"

#define EXPLOSION_COUNT 1
#define BLOOD_SPLATTER_COUNT 2
#define ANGLES 16

// character shadow
Sprite_Sheet sprite_sheet_character_shadow;
Animation_Definition *adef_character_shadow;
Animation *anim_character_shadow;

// brass
Sprite_Sheet sprite_sheet_brass_falling_1;
Animation_Definition *adef_brass_falling_1;
Sprite_Sheet sprite_sheet_shotgun_shell_falling_1;
Animation_Definition *adef_shotgun_shell_falling_1;

// bullets
Sprite_Sheet sprite_sheet_bullet_small;
Animation_Definition *adef_bullet_small;
Sprite_Sheet sprite_sheet_bullet_medium;
Animation_Definition *adef_bullet_medium;
Sprite_Sheet sprite_sheet_bullet_impact_small;
Animation_Definition *adef_bullet_impact_small;
Sprite_Sheet sprite_sheet_bullet_impact_medium;
Animation_Definition *adef_bullet_impact_medium;

// muzzle flash
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

Sprite_Sheet sprite_sheet_muzzle_flash_2_0;
Animation_Definition *adef_muzzle_flash_2_0;
Sprite_Sheet sprite_sheet_muzzle_flash_2_1;
Animation_Definition *adef_muzzle_flash_2_1;
Sprite_Sheet sprite_sheet_muzzle_flash_2_2;
Animation_Definition *adef_muzzle_flash_2_2;
Sprite_Sheet sprite_sheet_muzzle_flash_2_3;
Animation_Definition *adef_muzzle_flash_2_3;
Sprite_Sheet sprite_sheet_muzzle_flash_2_4;
Animation_Definition *adef_muzzle_flash_2_4;
Sprite_Sheet sprite_sheet_muzzle_flash_2_5;
Animation_Definition *adef_muzzle_flash_2_5;
Sprite_Sheet sprite_sheet_muzzle_flash_2_6;
Animation_Definition *adef_muzzle_flash_2_6;
Sprite_Sheet sprite_sheet_muzzle_flash_2_7;
Animation_Definition *adef_muzzle_flash_2_7;
Sprite_Sheet sprite_sheet_muzzle_flash_2_8;
Animation_Definition *adef_muzzle_flash_2_8;
Sprite_Sheet sprite_sheet_muzzle_flash_2_9;
Animation_Definition *adef_muzzle_flash_2_9;
Sprite_Sheet sprite_sheet_muzzle_flash_2_10;
Animation_Definition *adef_muzzle_flash_2_10;
Sprite_Sheet sprite_sheet_muzzle_flash_2_11;
Animation_Definition *adef_muzzle_flash_2_11;
Sprite_Sheet sprite_sheet_muzzle_flash_2_12;
Animation_Definition *adef_muzzle_flash_2_12;
Sprite_Sheet sprite_sheet_muzzle_flash_2_13;
Animation_Definition *adef_muzzle_flash_2_13;
Sprite_Sheet sprite_sheet_muzzle_flash_2_14;
Animation_Definition *adef_muzzle_flash_2_14;
Sprite_Sheet sprite_sheet_muzzle_flash_2_15;
Animation_Definition *adef_muzzle_flash_2_15;

// blood splatters
Sprite_Sheet sprite_sheet_blood_splatter_1;
Animation_Definition *adef_blood_splatter_1;
Sprite_Sheet sprite_sheet_blood_splatter_2;
Animation_Definition *adef_blood_splatter_2;

void init_brass_animation_definitions(void);
void init_bullet_animation_definitions(void);
void init_explosion_animation_definitions(void);
void init_blood_splatter_animation_definitions(void);
void init_character_shadow_anim(void);
void init_explosion_adef_hashmap(void);
void init_blood_splatter_adef_hashmap(void);
void create_muzzle_flash_entity(
    Player *player, char *muzzle_flash_id, f32 angle, vec2 position, vec2 size, vec2 velocity, u8 collision_layer, u8 collision_mask, On_Hit on_hit, On_Hit_Static on_hit_static);
void create_player_muzzle_flash_effect(Player *player);
void update_muzzle_flash_entities(void);
void create_bullet_impact_entity(vec2 position, Animation_Definition *adef);
void create_brass_entity(vec2 position, Animation_Definition *adef, i32 z_index);
void create_player_brass_effect(Player *player, Animation_Definition *brass_adef);
Animation_Definition *get_blood_splatter_adef(char *adef_prefix);
void brass_movement(Entity *entity);
void render_character_shadow(vec2 character_position, f32 character_sprite_height);

#endif