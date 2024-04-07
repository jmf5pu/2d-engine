#include "player_helpers.h"
#include "../collision_behavior/collision_behavior.h"
#include "../effects/effects.h"
#include "../engine/camera.h"
#include "../engine/global.h"
#include "../engine/util.h"
#include "../main_helpers/main_helpers.h"
#include "../structs.h"
#include "../weapon_types/weapon_types.h"
#include "player_anims.h"
#include <math.h>

// declare players
Player *player_one;
Player *player_two;

// animation hash maps
static Hash_Map *weapon_adef_map;

void init_weapon_adef_hashmap(void)
{
    weapon_adef_map = create_hash_map(WEAPON_STATES * WEAPON_COUNT * ANGLES);

    insert(weapon_adef_map, "m16_static_0", adef_m16_static_0);
    insert(weapon_adef_map, "m16_static_1", adef_m16_static_1);
    insert(weapon_adef_map, "m16_static_2", adef_m16_static_2);
    insert(weapon_adef_map, "m16_static_3", adef_m16_static_3);
    insert(weapon_adef_map, "m16_static_4", adef_m16_static_4);
    insert(weapon_adef_map, "m16_static_5", adef_m16_static_5);
    insert(weapon_adef_map, "m16_static_6", adef_m16_static_6);
    insert(weapon_adef_map, "m16_static_7", adef_m16_static_7);
    insert(weapon_adef_map, "m16_static_8", adef_m16_static_8);
    insert(weapon_adef_map, "m16_static_9", adef_m16_static_9);
    insert(weapon_adef_map, "m16_static_10", adef_m16_static_10);
    insert(weapon_adef_map, "m16_static_11", adef_m16_static_11);
    insert(weapon_adef_map, "m16_static_12", adef_m16_static_12);
    insert(weapon_adef_map, "m16_static_13", adef_m16_static_13);
    insert(weapon_adef_map, "m16_static_14", adef_m16_static_14);
    insert(weapon_adef_map, "m16_static_15", adef_m16_static_15);

    insert(weapon_adef_map, "m16_firing_0", adef_m16_firing_0);
    insert(weapon_adef_map, "m16_firing_1", adef_m16_firing_1);
    insert(weapon_adef_map, "m16_firing_2", adef_m16_firing_2);
    insert(weapon_adef_map, "m16_firing_3", adef_m16_firing_3);
    insert(weapon_adef_map, "m16_firing_4", adef_m16_firing_4);
    insert(weapon_adef_map, "m16_firing_5", adef_m16_firing_5);
    insert(weapon_adef_map, "m16_firing_6", adef_m16_firing_6);
    insert(weapon_adef_map, "m16_firing_7", adef_m16_firing_7);
    insert(weapon_adef_map, "m16_firing_8", adef_m16_firing_8);
    insert(weapon_adef_map, "m16_firing_9", adef_m16_firing_9);
    insert(weapon_adef_map, "m16_firing_10", adef_m16_firing_10);
    insert(weapon_adef_map, "m16_firing_11", adef_m16_firing_11);
    insert(weapon_adef_map, "m16_firing_12", adef_m16_firing_12);
    insert(weapon_adef_map, "m16_firing_13", adef_m16_firing_13);
    insert(weapon_adef_map, "m16_firing_14", adef_m16_firing_14);
    insert(weapon_adef_map, "m16_firing_15", adef_m16_firing_15);

    insert(weapon_adef_map, "glock_static_0", adef_glock_static_0);
    insert(weapon_adef_map, "glock_static_1", adef_glock_static_1);
    insert(weapon_adef_map, "glock_static_2", adef_glock_static_2);
    insert(weapon_adef_map, "glock_static_3", adef_glock_static_3);
    insert(weapon_adef_map, "glock_static_4", adef_glock_static_4);
    insert(weapon_adef_map, "glock_static_5", adef_glock_static_5);
    insert(weapon_adef_map, "glock_static_6", adef_glock_static_6);
    insert(weapon_adef_map, "glock_static_7", adef_glock_static_7);
    insert(weapon_adef_map, "glock_static_8", adef_glock_static_8);
    insert(weapon_adef_map, "glock_static_9", adef_glock_static_9);
    insert(weapon_adef_map, "glock_static_10", adef_glock_static_10);
    insert(weapon_adef_map, "glock_static_11", adef_glock_static_11);
    insert(weapon_adef_map, "glock_static_12", adef_glock_static_12);
    insert(weapon_adef_map, "glock_static_13", adef_glock_static_13);
    insert(weapon_adef_map, "glock_static_14", adef_glock_static_14);
    insert(weapon_adef_map, "glock_static_15", adef_glock_static_15);

    insert(weapon_adef_map, "glock_firing_0", adef_glock_firing_0);
    insert(weapon_adef_map, "glock_firing_1", adef_glock_firing_1);
    insert(weapon_adef_map, "glock_firing_2", adef_glock_firing_2);
    insert(weapon_adef_map, "glock_firing_3", adef_glock_firing_3);
    insert(weapon_adef_map, "glock_firing_4", adef_glock_firing_4);
    insert(weapon_adef_map, "glock_firing_5", adef_glock_firing_5);
    insert(weapon_adef_map, "glock_firing_6", adef_glock_firing_6);
    insert(weapon_adef_map, "glock_firing_7", adef_glock_firing_7);
    insert(weapon_adef_map, "glock_firing_8", adef_glock_firing_8);
    insert(weapon_adef_map, "glock_firing_9", adef_glock_firing_9);
    insert(weapon_adef_map, "glock_firing_10", adef_glock_firing_10);
    insert(weapon_adef_map, "glock_firing_11", adef_glock_firing_11);
    insert(weapon_adef_map, "glock_firing_12", adef_glock_firing_12);
    insert(weapon_adef_map, "glock_firing_13", adef_glock_firing_13);
    insert(weapon_adef_map, "glock_firing_14", adef_glock_firing_14);
    insert(weapon_adef_map, "glock_firing_15", adef_glock_firing_15);
}

// sets up animations for players and bullets
void init_all_player_anims(void)
{
    init_player_character_anims();

    // TODO: separate player and non-player anims to separate methods
    // init placeholder anims
    render_sprite_sheet_init(&sprite_sheet_missing_anim_placeholder, "assets/question_mark.png", 36, 36);
    adef_missing_anim_placeholder = animation_definition_create(&sprite_sheet_missing_anim_placeholder, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    missing_anim_placeholder = animation_create(adef_missing_anim_placeholder, false);

    // init crosshair anims
    render_sprite_sheet_init(&sprite_sheet_player_1_crosshair, "assets/wip/crosshair_mock.png", 11, 11);
    adef_player_1_crosshair = animation_definition_create(&sprite_sheet_player_1_crosshair, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_player_2_crosshair, "assets/wip/crosshair_mock.png", 11, 11);
    adef_player_2_crosshair = animation_definition_create(&sprite_sheet_player_2_crosshair, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_p1_crosshair = animation_create(adef_player_1_crosshair, false);
    anim_p2_crosshair = animation_create(adef_player_2_crosshair, false);

    render_sprite_sheet_init(&sprite_sheet_m16_static_0, "assets/wip/m16_static_0.png", 25, 25);
    adef_m16_static_0 = animation_definition_create(&sprite_sheet_m16_static_0, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_1, "assets/wip/m16_static_1.png", 25, 25);
    adef_m16_static_1 = animation_definition_create(&sprite_sheet_m16_static_1, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_2, "assets/wip/m16_static_2.png", 25, 25);
    adef_m16_static_2 = animation_definition_create(&sprite_sheet_m16_static_2, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_3, "assets/wip/m16_static_3.png", 25, 25);
    adef_m16_static_3 = animation_definition_create(&sprite_sheet_m16_static_3, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_4, "assets/wip/m16_static_4.png", 25, 25);
    adef_m16_static_4 = animation_definition_create(&sprite_sheet_m16_static_4, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_5, "assets/wip/m16_static_5.png", 25, 25);
    adef_m16_static_5 = animation_definition_create(&sprite_sheet_m16_static_5, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_6, "assets/wip/m16_static_6.png", 25, 25);
    adef_m16_static_6 = animation_definition_create(&sprite_sheet_m16_static_6, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_7, "assets/wip/m16_static_7.png", 25, 25);
    adef_m16_static_7 = animation_definition_create(&sprite_sheet_m16_static_7, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_8, "assets/wip/m16_static_8.png", 25, 25);
    adef_m16_static_8 = animation_definition_create(&sprite_sheet_m16_static_8, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_9, "assets/wip/m16_static_9.png", 25, 25);
    adef_m16_static_9 = animation_definition_create(&sprite_sheet_m16_static_9, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_10, "assets/wip/m16_static_10.png", 25, 25);
    adef_m16_static_10 = animation_definition_create(&sprite_sheet_m16_static_10, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_11, "assets/wip/m16_static_11.png", 25, 25);
    adef_m16_static_11 = animation_definition_create(&sprite_sheet_m16_static_11, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_12, "assets/wip/m16_static_12.png", 25, 25);
    adef_m16_static_12 = animation_definition_create(&sprite_sheet_m16_static_12, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_13, "assets/wip/m16_static_13.png", 25, 25);
    adef_m16_static_13 = animation_definition_create(&sprite_sheet_m16_static_13, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_14, "assets/wip/m16_static_14.png", 25, 25);
    adef_m16_static_14 = animation_definition_create(&sprite_sheet_m16_static_14, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_m16_static_15, "assets/wip/m16_static_15.png", 25, 25);
    adef_m16_static_15 = animation_definition_create(&sprite_sheet_m16_static_15, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);

    render_sprite_sheet_init(&sprite_sheet_m16_firing_0, "assets/wip/m16_firing_0.png", 25, 25);
    adef_m16_firing_0 = animation_definition_create(&sprite_sheet_m16_firing_0, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_1, "assets/wip/m16_firing_1.png", 25, 25);
    adef_m16_firing_1 = animation_definition_create(&sprite_sheet_m16_firing_1, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_2, "assets/wip/m16_firing_2.png", 25, 25);
    adef_m16_firing_2 = animation_definition_create(&sprite_sheet_m16_firing_2, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_3, "assets/wip/m16_firing_3.png", 25, 25);
    adef_m16_firing_3 = animation_definition_create(&sprite_sheet_m16_firing_3, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_4, "assets/wip/m16_firing_4.png", 25, 25);
    adef_m16_firing_4 = animation_definition_create(&sprite_sheet_m16_firing_4, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_5, "assets/wip/m16_firing_5.png", 25, 25);
    adef_m16_firing_5 = animation_definition_create(&sprite_sheet_m16_firing_5, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_6, "assets/wip/m16_firing_6.png", 25, 25);
    adef_m16_firing_6 = animation_definition_create(&sprite_sheet_m16_firing_6, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_7, "assets/wip/m16_firing_7.png", 25, 25);
    adef_m16_firing_7 = animation_definition_create(&sprite_sheet_m16_firing_7, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_8, "assets/wip/m16_firing_8.png", 25, 25);
    adef_m16_firing_8 = animation_definition_create(&sprite_sheet_m16_firing_8, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_9, "assets/wip/m16_firing_9.png", 25, 25);
    adef_m16_firing_9 = animation_definition_create(&sprite_sheet_m16_firing_9, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_10, "assets/wip/m16_firing_10.png", 25, 25);
    adef_m16_firing_10 = animation_definition_create(&sprite_sheet_m16_firing_10, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_11, "assets/wip/m16_firing_11.png", 25, 25);
    adef_m16_firing_11 = animation_definition_create(&sprite_sheet_m16_firing_11, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_12, "assets/wip/m16_firing_12.png", 25, 25);
    adef_m16_firing_12 = animation_definition_create(&sprite_sheet_m16_firing_12, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_13, "assets/wip/m16_firing_13.png", 25, 25);
    adef_m16_firing_13 = animation_definition_create(&sprite_sheet_m16_firing_13, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_14, "assets/wip/m16_firing_14.png", 25, 25);
    adef_m16_firing_14 = animation_definition_create(&sprite_sheet_m16_firing_14, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_m16_firing_15, "assets/wip/m16_firing_15.png", 25, 25);
    adef_m16_firing_15 = animation_definition_create(&sprite_sheet_m16_firing_15, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);

    render_sprite_sheet_init(&sprite_sheet_glock_static_0, "assets/wip/glock_static_0.png", 25, 25);
    adef_glock_static_0 = animation_definition_create(&sprite_sheet_glock_static_0, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_1, "assets/wip/glock_static_1.png", 25, 25);
    adef_glock_static_1 = animation_definition_create(&sprite_sheet_glock_static_1, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_2, "assets/wip/glock_static_2.png", 25, 25);
    adef_glock_static_2 = animation_definition_create(&sprite_sheet_glock_static_2, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_3, "assets/wip/glock_static_3.png", 25, 25);
    adef_glock_static_3 = animation_definition_create(&sprite_sheet_glock_static_3, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_4, "assets/wip/glock_static_4.png", 25, 25);
    adef_glock_static_4 = animation_definition_create(&sprite_sheet_glock_static_4, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_5, "assets/wip/glock_static_5.png", 25, 25);
    adef_glock_static_5 = animation_definition_create(&sprite_sheet_glock_static_5, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_6, "assets/wip/glock_static_6.png", 25, 25);
    adef_glock_static_6 = animation_definition_create(&sprite_sheet_glock_static_6, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_7, "assets/wip/glock_static_7.png", 25, 25);
    adef_glock_static_7 = animation_definition_create(&sprite_sheet_glock_static_7, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_8, "assets/wip/glock_static_8.png", 25, 25);
    adef_glock_static_8 = animation_definition_create(&sprite_sheet_glock_static_8, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_9, "assets/wip/glock_static_9.png", 25, 25);
    adef_glock_static_9 = animation_definition_create(&sprite_sheet_glock_static_9, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_10, "assets/wip/glock_static_10.png", 25, 25);
    adef_glock_static_10 = animation_definition_create(&sprite_sheet_glock_static_10, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_11, "assets/wip/glock_static_11.png", 25, 25);
    adef_glock_static_11 = animation_definition_create(&sprite_sheet_glock_static_11, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_12, "assets/wip/glock_static_12.png", 25, 25);
    adef_glock_static_12 = animation_definition_create(&sprite_sheet_glock_static_12, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_13, "assets/wip/glock_static_13.png", 25, 25);
    adef_glock_static_13 = animation_definition_create(&sprite_sheet_glock_static_13, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_14, "assets/wip/glock_static_14.png", 25, 25);
    adef_glock_static_14 = animation_definition_create(&sprite_sheet_glock_static_14, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_glock_static_15, "assets/wip/glock_static_15.png", 25, 25);
    adef_glock_static_15 = animation_definition_create(&sprite_sheet_glock_static_15, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);

    render_sprite_sheet_init(&sprite_sheet_glock_firing_0, "assets/wip/glock_firing_0.png", 25, 25);
    adef_glock_firing_0 = animation_definition_create(&sprite_sheet_glock_firing_0, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_1, "assets/wip/glock_firing_1.png", 25, 25);
    adef_glock_firing_1 = animation_definition_create(&sprite_sheet_glock_firing_1, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_2, "assets/wip/glock_firing_2.png", 25, 25);
    adef_glock_firing_2 = animation_definition_create(&sprite_sheet_glock_firing_2, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_3, "assets/wip/glock_firing_3.png", 25, 25);
    adef_glock_firing_3 = animation_definition_create(&sprite_sheet_glock_firing_3, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_4, "assets/wip/glock_firing_4.png", 25, 25);
    adef_glock_firing_4 = animation_definition_create(&sprite_sheet_glock_firing_4, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_5, "assets/wip/glock_firing_5.png", 25, 25);
    adef_glock_firing_5 = animation_definition_create(&sprite_sheet_glock_firing_5, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_6, "assets/wip/glock_firing_6.png", 25, 25);
    adef_glock_firing_6 = animation_definition_create(&sprite_sheet_glock_firing_6, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_7, "assets/wip/glock_firing_7.png", 25, 25);
    adef_glock_firing_7 = animation_definition_create(&sprite_sheet_glock_firing_7, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_8, "assets/wip/glock_firing_8.png", 25, 25);
    adef_glock_firing_8 = animation_definition_create(&sprite_sheet_glock_firing_8, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_9, "assets/wip/glock_firing_9.png", 25, 25);
    adef_glock_firing_9 = animation_definition_create(&sprite_sheet_glock_firing_9, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_10, "assets/wip/glock_firing_10.png", 25, 25);
    adef_glock_firing_10 = animation_definition_create(&sprite_sheet_glock_firing_10, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_11, "assets/wip/glock_firing_11.png", 25, 25);
    adef_glock_firing_11 = animation_definition_create(&sprite_sheet_glock_firing_11, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_12, "assets/wip/glock_firing_12.png", 25, 25);
    adef_glock_firing_12 = animation_definition_create(&sprite_sheet_glock_firing_12, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_13, "assets/wip/glock_firing_13.png", 25, 25);
    adef_glock_firing_13 = animation_definition_create(&sprite_sheet_glock_firing_13, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_14, "assets/wip/glock_firing_14.png", 25, 25);
    adef_glock_firing_14 = animation_definition_create(&sprite_sheet_glock_firing_14, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);
    render_sprite_sheet_init(&sprite_sheet_glock_firing_15, "assets/wip/glock_firing_15.png", 25, 25);
    adef_glock_firing_15 = animation_definition_create(&sprite_sheet_glock_firing_15, (f32[]){0.05, 0.05}, (u8[]){0, 0}, (u8[]){0, 1}, 2);

    init_weapon_adef_hashmap();
    init_player_character_anim_hashmap();
}
// TODO: move everyone above this (hashmap related) to a separate file

// parent function for all the necessary player updates made each frame
void player_per_frame_updates(Player *player)
{
    handle_player_input(player);
    update_player_crosshair_angle(player);
    update_player_weapon_position(player);
    update_player_status(player);
    if (player->status != PLAYER_INACTIVE)
        update_player_anims(player);
}

/// @brief Renders the player and player weapon animations. Called each frame. Render the shadow first. Rendering order between weapon and character anim depends on the player's
/// direction (crosshair_angle)
/// @param player active player
/// @param window
/// @param texture_slots
/// @param color
void render_player_anims(Player *player, SDL_Window *window, u32 texture_slots[32], vec4 color)
{
    if (player) {
        vec2 character_shadow_pos = {0, 0};
        vec2_add(character_shadow_pos, player->entity->body->aabb.position, (vec2){0, -0.5 * player->entity->animation->animation_definition->sprite_sheet->cell_height});
        animation_render(anim_character_shadow, window, character_shadow_pos, color, texture_slots);

        // player is facing up, render weapon "under" player
        if (player->crosshair_angle > M_PI / 4 && player->crosshair_angle < 3 * M_PI / 4) {
            animation_render(player->weapon->character_anim, window, player->weapon->position, color, texture_slots);
            animation_render(player->entity->animation, window, player->entity->body->aabb.position, color, texture_slots);
        }
        else {
            animation_render(player->entity->animation, window, player->entity->body->aabb.position, color, texture_slots);
            animation_render(player->weapon->character_anim, window, player->weapon->position, color, texture_slots);
        }
    }
    else
        printf("player must be defined to update corresponding anims");
}

// initializes the player struct
void init_player(Player *player, Map *map, Weapon_Type *starting_weapon, f32 despawn_time, f32 spawn_delay, f32 spawn_time, bool is_left_player)
{
    player->entity =
        entity_create((vec2){render_width * 0.5, render_height * 0.5}, (vec2){18, 22}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static);
    player->entity->body->parent = player;
    player->crosshair = malloc(sizeof(Entity));
    player->crosshair = entity_create(
        (vec2){player->entity->body->aabb.position[0], player->entity->body->aabb.position[1]},
        (vec2){CROSSHAIR_SIZE, CROSSHAIR_SIZE},
        (vec2){0, 0},
        COLLISION_LAYER_CROSSHAIR,
        crosshair_mask,
        NULL,
        NULL);
    player->crosshair->animation = player->is_left_player ? anim_p1_crosshair : anim_p2_crosshair;
    player->crosshair->is_active = true;

    // populate weapon
    player->weapon = malloc(sizeof(Weapon));
    player->weapon->name = starting_weapon->name;
    player->weapon->fire_mode = starting_weapon->fire_mode;
    player->weapon->capacity = starting_weapon->capacity;
    player->weapon->max_capacity = starting_weapon->capacity;
    player->weapon->reserve = starting_weapon->reserve;
    player->weapon->max_reserve = starting_weapon->reserve;
    player->weapon->max_fire_rate = starting_weapon->max_fire_rate;
    player->weapon->damage = starting_weapon->damage;
    player->weapon->bullet_velocity = starting_weapon->bullet_velocity;
    player->weapon->burst_count = starting_weapon->burst_count;
    player->weapon->burst_shots_remaining = starting_weapon->burst_count;
    player->weapon->burst_delay = starting_weapon->burst_delay;
    player->weapon->frames_since_last_shot = 0;
    player->weapon->ready_to_fire = true;
    player->weapon->is_firing = false;
    player->weapon->hud_ammo_icon = starting_weapon->hud_ammo_icon;
    player->weapon->on_shoot = starting_weapon->on_shoot;

    // weapon anims will be populated each frame based on the current player inputs
    player->weapon->character_anim = NULL;

    // populate armor
    player->armor = malloc(sizeof(Armor));
    player->armor->name = "";
    player->armor->integrity = 0;

    player->spawn_point[0] = is_left_player ? map->player_one_spawn_points[0][0] : map->player_two_spawn_points[0][0];
    player->spawn_point[1] = is_left_player ? map->player_one_spawn_points[0][1] : map->player_two_spawn_points[0][1];
    player->despawn_time = despawn_time;
    player->spawn_delay = spawn_delay;
    player->spawn_time = spawn_time;
    player->is_left_player = is_left_player;
    if (is_left_player) {
        player->camera = SPLIT_SCREEN ? &left_cam : &main_cam;
    }
    else {
        player->camera = &right_cam;
    }

    // init input state members
    player->input_state = malloc(sizeof(Player_Input_State));
    player->input_state->controller_input_state = malloc(sizeof(Controller_Input_State));
    player->input_state->controller_input_state->controller_id = -1;
    player->input_state->controller_input_state->left_joystick_state.x_axis = 0.0f;
    player->input_state->controller_input_state->left_joystick_state.y_axis = 0.0f;
    player->input_state->controller_input_state->right_joystick_state.x_axis = 0.0f;
    player->input_state->controller_input_state->right_joystick_state.y_axis = 0.0f;

    // init key state members
    player->input_state->key_state = malloc(sizeof(Player_Key_State));
    player->input_state->key_state->up = 0;
    player->input_state->key_state->down = 0;
    player->input_state->key_state->left = 0;
    player->input_state->key_state->right = 0;
    player->input_state->key_state->shoot = 0;
    player->input_state->key_state->reload = 0;
    player->input_state->key_state->use = 0;
    player->input_state->key_state->pause = 0;
}

// Spawns the player and resets their attributes to default values
void spawn_player(Player *player, Weapon_Type *starting_weapon)
{
    // update status & reset counter
    player->status = PLAYER_SPAWNING;
    player->frames_on_status = 0;

    // move player to respawn point
    player->relative_position[0] = player->spawn_point[0];
    player->relative_position[1] = player->spawn_point[1];

    // set player to center of their window
    player->entity->body->aabb.position[0] = render_width * 0.5;
    player->entity->body->aabb.position[1] = render_height * 0.5;

    // set camera to center the spawn point
    player->camera->position[0] = player->spawn_point[0] - (0.5 * render_width);
    player->camera->position[1] = player->spawn_point[1] - (0.5 * render_height);

    // reset render scale factor
    player->render_scale_factor = DEFAULT_RENDER_SCALE_FACTOR;

    // reset health and armor
    player->armor->name = "";
    player->armor->integrity = 0;
    player->health = 100;

    // reset player anims to default (may have changed from pickups)

    // reset weapon
    player->weapon->name = starting_weapon->name;
    player->weapon->fire_mode = starting_weapon->fire_mode;
    player->weapon->capacity = starting_weapon->capacity;
    player->weapon->max_capacity = starting_weapon->capacity;
    player->weapon->reserve = starting_weapon->reserve;
    player->weapon->max_reserve = starting_weapon->reserve;
    player->weapon->max_fire_rate = starting_weapon->max_fire_rate;
    player->weapon->damage = starting_weapon->damage;
    player->weapon->bullet_velocity = starting_weapon->bullet_velocity;
    player->weapon->burst_count = starting_weapon->burst_count;
    player->weapon->burst_delay = starting_weapon->burst_delay;
    player->weapon->frames_since_last_shot = 0;
    player->weapon->ready_to_fire = true;
    player->weapon->hud_ammo_icon = starting_weapon->hud_ammo_icon;

    // make player visible
    player->entity->is_active = true;
    player->entity->body->is_active = true;
}

// updates player statuses based on frame counter associated with each playaer
void update_player_status(Player *player)
{
    // SPAWN LOGIC
    // check if spawn delay is up
    if (player->status == PLAYER_INACTIVE && player->frames_on_status >= (player->spawn_delay * global.time.frame_rate)) {
        spawn_player(player, m16);
    }

    // check if spawn time is up
    else if (player->status == PLAYER_SPAWNING && player->frames_on_status >= (player->spawn_time * global.time.frame_rate)) {
        player->status = PLAYER_ACTIVE;
        player->frames_on_status = 0;
    }

    // DESPAWN LOGIC
    // check if health is 0
    else if (player->health <= 0 && player->status == PLAYER_ACTIVE) {
        player->status = PLAYER_DESPAWNING;
        player->render_scale_factor = DEFAULT_RENDER_SCALE_FACTOR;
        player->frames_on_status = 0;

        // shouldn't be moving on death anim
        player->entity->body->velocity[0] = 0;
        player->entity->body->velocity[1] = 0;
    }
    // check if death animation is complete
    else if (player->status == PLAYER_DESPAWNING && player->frames_on_status >= (player->despawn_time * global.time.frame_rate)) {
        player->status = PLAYER_INACTIVE;
        player->frames_on_status = 0;

        // hide sprites
        player->entity->is_active = false;
        player->entity->body->is_active = false;
    }

    // WEAPON STATUS LOGIC
    // reloading logic
    if (player->status == PLAYER_RELOADING) {
        // reload either the missing bullets in the magazine or whatever
        // the player has left in reserve
        u16 reload_amount = MIN(player->weapon->reserve, (player->weapon->max_capacity - player->weapon->capacity));
        player->weapon->capacity += reload_amount;
        player->weapon->reserve -= reload_amount;
        // TODO: add animation / reload wait time logic
        player->status = PLAYER_ACTIVE;
    }

    // update weapon status (check if weapon is ready to fire again)
    if (player->status != PLAYER_RELOADING && !player->weapon->ready_to_fire &&
        player->weapon->frames_since_last_shot >= ((1.0 / (player->weapon->max_fire_rate / 60.0)) * global.time.frame_rate)) {
        if (player->weapon->fire_mode == AUTO || player->weapon->fire_mode == SEMI) {
            player->weapon->ready_to_fire = true;
        }

        // need an additional check for burst weapons, is ready to fire
        // if burst shots are left OR if burst delay is complete
        else if (
            player->weapon->fire_mode == BURST &&
            (player->weapon->burst_shots_remaining > 0 || (player->weapon->frames_since_last_shot * (1.0 / global.time.frame_rate)) >= player->weapon->burst_delay)) {
            if (player->weapon->burst_shots_remaining == 0 && (player->weapon->frames_since_last_shot * (1.0 / global.time.frame_rate) >= player->weapon->burst_delay)) {
                player->weapon->burst_shots_remaining = player->weapon->burst_count; // reset burst
            }
            player->weapon->ready_to_fire = true;
        }
    }

    // TIMER UPDATES
    // increments timers for BOTH player and weapon
    player->frames_on_status++;
    player->weapon->frames_since_last_shot++;
}

/*
 * updates players animations each frame.
 * Animations are named in the following manner:
 * character_weapon_armor_movement-status_direction
 */
void update_player_anims(Player *player)
{
    update_player_character_anim(player);
    update_player_weapon_anim(player);
}

/// @brief Calculates the weapon sprite's position using the player's crosshair angle
/// @param player
/// @param weapon_position
void update_player_weapon_position(Player *player)
{
    vec2 weapon_position = {0, 0};
    vec2_add(
        weapon_position,
        player->entity->body->aabb.position,
        (vec2){0, CHARACTER_ARMS_Y_OFFSET_FROM_CENTER}); // subtract some from the player pos as the hands are lower in the sprite than the center
    vec2 offset = {0, 0};
    get_xy_components_from_vector(CHARACTER_WEAPON_OFFSET, player->crosshair_angle, offset);
    vec2_add(player->weapon->position, weapon_position, offset);
}

/// @brief Anim assignment is typically broken up into 16 directions in this game. This method takes an angle (typically between the player and their crosshair) to pick an anim
/// suffix
/// @param angle the angle in question
/// @param direction_result store the result here
void get_direction_from_angle(f32 angle, char *direction_result)
{
    if (angle > -1 * M_PI / 16 && angle <= M_PI / 16)
        strcpy(direction_result, "0");
    else if (angle > M_PI / 16 && angle <= 3 * M_PI / 16)
        strcpy(direction_result, "1");
    else if (angle > 3 * M_PI / 16 && angle <= 5 * M_PI / 16)
        strcpy(direction_result, "2");
    else if (angle > 5 * M_PI / 16 && angle <= 7 * M_PI / 16)
        strcpy(direction_result, "3");

    else if (angle > 7 * M_PI / 16 && angle <= 9 * M_PI / 16)
        strcpy(direction_result, "4");

    else if (angle > 9 * M_PI / 16 && angle <= 11 * M_PI / 16)
        strcpy(direction_result, "5");

    else if (angle > 11 * M_PI / 16 && angle <= 13 * M_PI / 16)
        strcpy(direction_result, "6");

    else if (angle > 13 * M_PI / 16 && angle <= 15 * M_PI / 16)
        strcpy(direction_result, "7");

    else if (angle > 15 * M_PI / 16 || angle <= -15 * M_PI / 16)
        strcpy(direction_result, "8");

    else if (angle > -15 * M_PI / 16 && angle <= -13 * M_PI / 16)
        strcpy(direction_result, "9");

    else if (angle > -13 * M_PI / 16 && angle <= -11 * M_PI / 16)
        strcpy(direction_result, "10");

    else if (angle > -11 * M_PI / 16 && angle <= -9 * M_PI / 16)
        strcpy(direction_result, "11");

    else if (angle > -9 * M_PI / 16 && angle <= -7 * M_PI / 16)
        strcpy(direction_result, "12");

    else if (angle > -7 * M_PI / 16 && angle <= -5 * M_PI / 16)
        strcpy(direction_result, "13");

    else if (angle > -5 * M_PI / 16 && angle <= -3 * M_PI / 16)
        strcpy(direction_result, "14");

    else if (angle > -3 * M_PI / 16 && angle <= -1 * M_PI / 16)
        strcpy(direction_result, "15");

    else
        printf("got unexpected crosshair angle: %f\n", angle);
}

static void update_player_weapon_anim(Player *player)
{
    // cache old anim to check if we are SWITCHING anims
    Animation_Definition *prev_adef = player->weapon->character_anim ? player->weapon->character_anim->animation_definition : NULL;

    char *adef_name = calloc(50, sizeof(char));
    strcat(adef_name, player->weapon->name);
    strcat(adef_name, "_");

    bool show_firing_anim = player->weapon->is_firing ||
                            (player->weapon->character_anim && player->weapon->character_anim->current_frame_index > 0 && player->weapon->character_anim->reset_count == 0);
    char *firing_state = show_firing_anim ? "firing" : "static";

    char *direction = calloc(5, sizeof(char));
    get_direction_from_angle(player->crosshair_angle, direction);

    strcat(adef_name, firing_state);
    strcat(adef_name, "_");
    strcat(adef_name, direction);
    strcat(adef_name, "\0");

    Animation_Definition *weapon_character_adef = get(weapon_adef_map, adef_name);
    free(direction);
    free(adef_name);

    // only update the animation if it's a new one (otherwise keep looping through the old one)
    if (weapon_character_adef != prev_adef || !prev_adef) {
        if (prev_adef)
            animation_destroy(player->weapon->character_anim);
        if (weapon_character_adef)
            player->weapon->character_anim = animation_create(weapon_character_adef, true);
        else
            player->weapon->character_anim = animation_create(adef_missing_anim_placeholder, false);
    }
}

static void update_player_crosshair_angle(Player *player)
{
    player->crosshair_angle = atan2(
        player->crosshair->body->aabb.position[1] - player->entity->body->aabb.position[1], player->crosshair->body->aabb.position[0] - player->entity->body->aabb.position[0]);
}

void handle_player_shooting(Player *player, Key_State shoot)
{
    // check if key presses are correct based on fire mode
    bool key_state_ready = false;
    if ((player->weapon->fire_mode == AUTO && shoot == KS_HELD) || (player->weapon->fire_mode == SEMI && shoot == KS_PRESSED)) {
        key_state_ready = true;
    }
    else if (
        player->weapon->fire_mode == BURST && ((player->weapon->burst_shots_remaining == player->weapon->burst_count && shoot == KS_PRESSED) ||
                                               (player->weapon->burst_shots_remaining < player->weapon->burst_count && shoot == KS_HELD))) {
        key_state_ready = true;
    }

    // generate bullet if weapon is loaded and key state is correct
    if (player->weapon->capacity > 0 && player->weapon->ready_to_fire && key_state_ready) {
        // update flag on the weapon struct (used for anim assignment)
        player->weapon->is_firing = true;

        // create bullet(s) [anims and direction will be specific to the weapon's type]
        player->weapon->on_shoot(player);

        // decrement weapon capacity
        player->weapon->capacity -= 1;

        if (player->weapon->fire_mode == BURST) {
            player->weapon->burst_shots_remaining -= 1;
        }

        // restart rounds per minute timer
        player->weapon->ready_to_fire = false;
        player->weapon->frames_since_last_shot = 0;

        // Note the lack of collision masks and on hit methods - collisions aren't relevant for muzzle flash entities
        vec2 muzzle_flash_position = {0, 0};
        vec2 muzzle_flash_offset = {0, 0};
        get_xy_components_from_vector(MUZZLE_FLASH_DISTANCE_FROM_PLAYER, player->crosshair_angle, muzzle_flash_offset);
        vec2_add(muzzle_flash_offset, muzzle_flash_offset, (vec2){0, CHARACTER_ARMS_Y_OFFSET_FROM_CENTER});
        vec2_add(muzzle_flash_position, player->relative_position, muzzle_flash_offset);
        create_muzzle_flash_entity(player->crosshair_angle, muzzle_flash_position, (vec2){15, 15}, player->entity->body->velocity, 0, 0, NULL, NULL);

        // ccalculate brass offset from the player and create brass effect entity
        vec2 brass_position = {0, 0};
        vec2_dup(brass_position, player->relative_position);
        vec2 brass_offset = {0, 0};
        get_xy_components_from_vector(BRASS_EJECT_DISTANCE_FROM_PLAYER, player->crosshair_angle, brass_offset);
        vec2_add(brass_position, brass_position, brass_offset);
        vec2_add(brass_position, brass_position, (vec2){0, CHARACTER_ARMS_Y_OFFSET_FROM_CENTER});
        create_brass_entity(brass_position, adef_brass_falling_1, get_player_brass_z_index(player->crosshair_angle));
    }
    else
        player->weapon->is_firing = false;
}

/// @brief helper to get the z_index of brass entities based on player direction. If the player is facing up, we want to render the brass underneath the player sprite
/// @param angle player to crosshair angle
/// @return z index for the brass entity (1 or -1)
static i32 get_player_brass_z_index(f32 angle)
{
    bool player_facing_up = angle > M_PI / 4 && angle < 3 * M_PI / 4;
    return player_facing_up ? -1 : 1;
}

/// @brief Applies the player's input state to other relevant members, such as moving, shooting, and reloading states
/// @param player
void apply_player_input_state(Player *player)
{
    if (player->input_state->key_state->reload) {
        player->status = PLAYER_RELOADING;
    }

    // only update velocity from keyboard if the joysticks weren't updated this frame (no controller associated)
    if (player->input_state->controller_input_state->controller_id == -1)
        update_player_velocity_from_key_state(player);

    if (player->input_state->key_state->shoot)
        handle_player_shooting(player, player->input_state->key_state->shoot);
    else
        player->weapon->is_firing = false;
}

/// @brief Update the player's entity's velocity from its current key state. Supports 8 directional movement
/// @param player the active player
void update_player_velocity_from_key_state(Player *player)
{
    Player_Key_State *key_state = player->input_state->key_state;
    f32 velx = 0;
    f32 vely = 0;
    f32 angle = 0.78539816; // 45 degrees in radians
    f32 xy_magnitude = sin(angle) * MAX_PLAYER_MOVEMENT_SPEED;

    if (key_state->up && key_state->right) {
        velx += xy_magnitude;
        vely += xy_magnitude;
    }
    else if (key_state->up && key_state->left) {
        velx -= xy_magnitude;
        vely += xy_magnitude;
    }
    else if (key_state->down && key_state->right) {
        velx += xy_magnitude;
        vely -= xy_magnitude;
    }
    else if (key_state->down && key_state->left) {
        velx -= xy_magnitude;
        vely -= xy_magnitude;
    }
    else if (key_state->right) {
        velx += MAX_PLAYER_MOVEMENT_SPEED;
    }

    else if (key_state->left) {
        velx -= MAX_PLAYER_MOVEMENT_SPEED;
    }

    else if (key_state->up) {
        vely += MAX_PLAYER_MOVEMENT_SPEED;
    }

    else if (key_state->down) {
        vely -= MAX_PLAYER_MOVEMENT_SPEED;
    }
    player->entity->body->velocity[0] = velx;
    player->entity->body->velocity[1] = vely;
}

void free_player(Player *player)
{
    // crosshair mem is deallocated when we clear the entity array_list
    free(player->input_state->controller_input_state);
    free(player->input_state->key_state);
    free(player->input_state);

    free(player);
    player = NULL;
}

void free_players()
{
    if (player_one) {
        free_player(player_one);
    }
    if (player_two) {
        free_player(player_two);
    }
}