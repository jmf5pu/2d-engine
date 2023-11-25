#include <math.h>
#include "engine/global.h"
#include "engine/util.h"
#include "engine/camera.h"
#include "player_helpers.h"
#include "collision_behavior.h"
#include "weapon_types.h"

// declare players
Player *player_one;
Player *player_two;

// init bullet animation hash_map
void init_bullet_anim_hashmap()
{
    bullet_anim_map = create_hash_map(BULLET_ANIM_COUNT);
    insert(bullet_anim_map, "bullet_0", anim_bullet_0);
    insert(bullet_anim_map, "bullet_1", anim_bullet_1);
    insert(bullet_anim_map, "bullet_2", anim_bullet_2);
    insert(bullet_anim_map, "bullet_3", anim_bullet_3);
    insert(bullet_anim_map, "bullet_4", anim_bullet_4);
    insert(bullet_anim_map, "bullet_5", anim_bullet_5);
    insert(bullet_anim_map, "bullet_6", anim_bullet_6);
    insert(bullet_anim_map, "bullet_7", anim_bullet_7);
    insert(bullet_anim_map, "bullet_8", anim_bullet_8);
    insert(bullet_anim_map, "bullet_9", anim_bullet_9);
    insert(bullet_anim_map, "bullet_10", anim_bullet_10);
    insert(bullet_anim_map, "bullet_11", anim_bullet_11);
    insert(bullet_anim_map, "bullet_12", anim_bullet_12);
    insert(bullet_anim_map, "bullet_13", anim_bullet_13);
    insert(bullet_anim_map, "bullet_14", anim_bullet_14);
    insert(bullet_anim_map, "bullet_15", anim_bullet_15);
}

// init player animation hash_map
void init_player_anim_hashmap()
{
    player_anim_map = create_hash_map(PLAYER_ANIM_COUNT);

    // player one stuff
    // insert(player_anim_map, "p1_anim_soldier_1_m16_idle_side", p1_anim_soldier_1_m16_idle_side);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_running_side", p1_anim_soldier_1_m16_running_side);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_idle_back", p1_anim_soldier_1_m16_idle_back);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_running_back", p1_anim_soldier_1_m16_running_back);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_idle_front", p1_anim_soldier_1_m16_idle_front);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_running_front", p1_anim_soldier_1_m16_running_front);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_idle_up_right", p1_anim_soldier_1_m16_idle_up_right);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_running_up_right", p1_anim_soldier_1_m16_running_up_right);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_idle_down_right", p1_anim_soldier_1_m16_idle_down_right);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_running_down_right", p1_anim_soldier_1_m16_running_down_right);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_spawning_side", p1_anim_soldier_1_m16_spawning_side);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_dying_side", p1_anim_soldier_1_m16_dying_side);

    // insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_idle_side", p1_anim_soldier_1_m16_brewster_idle_side);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_running_side", p1_anim_soldier_1_m16_brewster_running_side);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_idle_back", p1_anim_soldier_1_m16_brewster_idle_back);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_running_back", p1_anim_soldier_1_m16_brewster_running_back);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_idle_front", p1_anim_soldier_1_m16_brewster_idle_front);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_running_front", p1_anim_soldier_1_m16_brewster_running_front);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_spawning_side", p1_anim_soldier_1_m16_brewster_spawning_side);
    // insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_dying_side", p1_anim_soldier_1_m16_brewster_dying_side);

    // insert(player_anim_map, "p1_anim_soldier_1_m44_idle_side", p1_anim_soldier_1_m44_idle_side);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_running_side", p1_anim_soldier_1_m44_running_side);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_idle_back", p1_anim_soldier_1_m44_idle_back);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_running_back", p1_anim_soldier_1_m44_running_back);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_idle_front", p1_anim_soldier_1_m44_idle_front);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_running_front", p1_anim_soldier_1_m44_running_front);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_spawning_side", p1_anim_soldier_1_m44_spawning_side);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_dying_side", p1_anim_soldier_1_m44_dying_side);

    // insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_idle_side", p1_anim_soldier_1_m44_brewster_idle_side);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_running_side", p1_anim_soldier_1_m44_brewster_running_side);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_idle_back", p1_anim_soldier_1_m44_brewster_idle_back);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_running_back", p1_anim_soldier_1_m44_brewster_running_back);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_idle_front", p1_anim_soldier_1_m44_brewster_idle_front);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_running_front", p1_anim_soldier_1_m44_brewster_running_front);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_spawning_side", p1_anim_soldier_1_m44_brewster_spawning_side);
    // insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_dying_side", p1_anim_soldier_1_m44_brewster_dying_side);

    // insert(player_anim_map, "p2_anim_soldier_1_m16_idle_side", p2_anim_soldier_1_m16_idle_side);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_running_side", p2_anim_soldier_1_m16_running_side);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_idle_back", p2_anim_soldier_1_m16_idle_back);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_running_back", p2_anim_soldier_1_m16_running_back);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_idle_front", p2_anim_soldier_1_m16_idle_front);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_running_front", p2_anim_soldier_1_m16_running_front);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_idle_up_right", p2_anim_soldier_1_m16_idle_up_right);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_running_up_right", p2_anim_soldier_1_m16_running_up_right);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_idle_down_right", p2_anim_soldier_1_m16_idle_down_right);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_running_down_right", p2_anim_soldier_1_m16_running_down_right);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_spawning_side", p2_anim_soldier_1_m16_spawning_side);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_dying_side", p2_anim_soldier_1_m16_dying_side);

    // insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_idle_side", p2_anim_soldier_1_m16_brewster_idle_side);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_running_side", p2_anim_soldier_1_m16_brewster_running_side);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_idle_back", p2_anim_soldier_1_m16_brewster_idle_back);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_running_back", p2_anim_soldier_1_m16_brewster_running_back);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_idle_front", p2_anim_soldier_1_m16_brewster_idle_front);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_running_front", p2_anim_soldier_1_m16_brewster_running_front);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_spawning_side", p2_anim_soldier_1_m16_brewster_spawning_side);
    // insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_dying_side", p2_anim_soldier_1_m16_brewster_dying_side);

    // insert(player_anim_map, "p2_anim_soldier_1_m44_idle_side", p2_anim_soldier_1_m44_idle_side);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_running_side", p2_anim_soldier_1_m44_running_side);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_idle_back", p2_anim_soldier_1_m44_idle_back);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_running_back", p2_anim_soldier_1_m44_running_back);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_idle_front", p2_anim_soldier_1_m44_idle_front);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_running_front", p2_anim_soldier_1_m44_running_front);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_spawning_side", p2_anim_soldier_1_m44_spawning_side);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_dying_side", p2_anim_soldier_1_m44_dying_side);

    // insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_idle_side", p2_anim_soldier_1_m44_brewster_idle_side);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_running_side", p2_anim_soldier_1_m44_brewster_running_side);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_idle_back", p2_anim_soldier_1_m44_brewster_idle_back);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_running_back", p2_anim_soldier_1_m44_brewster_running_back);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_idle_front", p2_anim_soldier_1_m44_brewster_idle_front);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_running_front", p2_anim_soldier_1_m44_brewster_running_front);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_spawning_side", p2_anim_soldier_1_m44_brewster_spawning_side);
    // insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_dying_side", p2_anim_soldier_1_m44_brewster_dying_side);

    // new player stuff 11/12
    insert(player_anim_map, "p1_anim_soldier_purple_base_idle_back", p1_anim_soldier_purple_base_idle_back);
    insert(player_anim_map, "p1_anim_soldier_purple_base_idle_side", p1_anim_soldier_purple_base_idle_side);
    insert(player_anim_map, "p1_anim_soldier_purple_base_idle_front", p1_anim_soldier_purple_base_idle_front);

    insert(player_anim_map, "p2_anim_soldier_purple_base_idle_back", p2_anim_soldier_purple_base_idle_back);
    insert(player_anim_map, "p2_anim_soldier_purple_base_idle_side", p2_anim_soldier_purple_base_idle_side);
    insert(player_anim_map, "p2_anim_soldier_purple_base_idle_front", p2_anim_soldier_purple_base_idle_front);
}

// sets up animations for players and bullets
void init_all_anims()
{
    // TODO: separate player and non-player anims to separate methods
    // init placeholder anims
    render_sprite_sheet_init(&sprite_sheet_player_placeholder, "assets/question_mark.png", 36, 36);
    adef_player_placeholder = animation_definition_create(
        &sprite_sheet_player_placeholder,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_player_placeholder = animation_create(adef_player_placeholder, false);

    // init crosshair anims
    render_sprite_sheet_init(&sprite_sheet_crosshair_red, "assets/crosshair_red.png", 27, 27);
    adef_crosshair_red = animation_definition_create(
        &sprite_sheet_crosshair_red,
        (f32[]){0.1, 0.1, 0.1, 0.1},
        (u8[]){0, 0, 0, 0},
        (u8[]){1, 2, 3, 4},
        4);
    anim_crosshair_red = animation_create(adef_crosshair_red, true);

    // init bullet anims
    render_sprite_sheet_init(&sprite_sheet_bullet_0, "assets/bullet_0.png", 3, 1);
    adef_bullet_0 = animation_definition_create(
        &sprite_sheet_bullet_0,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_0 = animation_create(adef_bullet_0, false);
    render_sprite_sheet_init(&sprite_sheet_bullet_1, "assets/bullet_1.png", 3, 2);
    adef_bullet_1 = animation_definition_create(
        &sprite_sheet_bullet_1,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_1 = animation_create(adef_bullet_1, false);
    render_sprite_sheet_init(&sprite_sheet_bullet_2, "assets/bullet_2.png", 3, 3);
    adef_bullet_2 = animation_definition_create(
        &sprite_sheet_bullet_2,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_2 = animation_create(adef_bullet_2, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_3, "assets/bullet_3.png", 2, 3);
    adef_bullet_3 = animation_definition_create(
        &sprite_sheet_bullet_3,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_3 = animation_create(adef_bullet_3, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_4, "assets/bullet_4.png", 1, 3);
    adef_bullet_4 = animation_definition_create(
        &sprite_sheet_bullet_4,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_4 = animation_create(adef_bullet_4, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_5, "assets/bullet_5.png", 2, 3);
    adef_bullet_5 = animation_definition_create(
        &sprite_sheet_bullet_5,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_5 = animation_create(adef_bullet_5, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_6, "assets/bullet_6.png", 3, 3);
    adef_bullet_6 = animation_definition_create(
        &sprite_sheet_bullet_6,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_6 = animation_create(adef_bullet_6, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_7, "assets/bullet_7.png", 3, 2);
    adef_bullet_7 = animation_definition_create(
        &sprite_sheet_bullet_7,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_7 = animation_create(adef_bullet_7, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_8, "assets/bullet_8.png", 3, 1);
    adef_bullet_8 = animation_definition_create(
        &sprite_sheet_bullet_8,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_8 = animation_create(adef_bullet_8, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_9, "assets/bullet_9.png", 3, 2);
    adef_bullet_9 = animation_definition_create(
        &sprite_sheet_bullet_9,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_9 = animation_create(adef_bullet_9, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_10, "assets/bullet_10.png", 3, 3);
    adef_bullet_10 = animation_definition_create(
        &sprite_sheet_bullet_10,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_10 = animation_create(adef_bullet_10, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_11, "assets/bullet_11.png", 2, 3);
    adef_bullet_11 = animation_definition_create(
        &sprite_sheet_bullet_11,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_11 = animation_create(adef_bullet_11, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_12, "assets/bullet_12.png", 1, 3);
    adef_bullet_12 = animation_definition_create(
        &sprite_sheet_bullet_12,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_12 = animation_create(adef_bullet_12, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_13, "assets/bullet_13.png", 2, 3);
    adef_bullet_13 = animation_definition_create(
        &sprite_sheet_bullet_13,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_13 = animation_create(adef_bullet_13, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_14, "assets/bullet_14.png", 3, 3);
    adef_bullet_14 = animation_definition_create(
        &sprite_sheet_bullet_14,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_14 = animation_create(adef_bullet_14, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_15, "assets/bullet_15.png", 3, 2);
    adef_bullet_15 = animation_definition_create(
        &sprite_sheet_bullet_15,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_15 = animation_create(adef_bullet_15, false);

    /*
     * player one animations
     */

    // m16
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_idle_side, "assets/soldier_1_m16_idle_side.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_running_side, "assets/soldier_1_m16_running_side.png", 36, 37);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_idle_back, "assets/soldier_1_m16_idle_back.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_running_back, "assets/soldier_1_m16_running_back.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_idle_front, "assets/soldier_1_m16_idle_front.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_running_front, "assets/soldier_1_m16_running_front.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_idle_up_right, "assets/soldier_1_m16_idle_up_right.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_running_up_right, "assets/soldier_1_m16_running_up_right.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_idle_down_right, "assets/soldier_1_m16_idle_down_right.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_running_down_right, "assets/soldier_1_m16_running_down_right.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_spawning_side, "assets/soldier_1_m16_spawning_side.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_dying_side, "assets/soldier_1_m16_dying_side.png", 42, 42);

    p1_adef_soldier_1_m16_idle_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m16_running_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    p1_adef_soldier_1_m16_idle_back = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m16_running_back = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_running_back,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    p1_adef_soldier_1_m16_idle_front = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m16_running_front = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_running_front,
        (f32[]){0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.04, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
    p1_adef_soldier_1_m16_idle_up_right = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_idle_up_right,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m16_running_up_right = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_running_up_right,
        (f32[]){0.06, 0.1, 0.08, 0.06, 0.1, 0.08},
        (u8[]){0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6},
        6);
    p1_adef_soldier_1_m16_idle_down_right = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_idle_down_right,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m16_running_down_right = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_running_down_right,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6},
        6);
    p1_adef_soldier_1_m16_spawning_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_spawning_side,
        (f32[]){0.25, 0.25},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    p1_adef_soldier_1_m16_dying_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_dying_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.75, 0.5, 0.5, 0.5, 0.75},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);

    p1_anim_soldier_1_m16_idle_side = animation_create(p1_adef_soldier_1_m16_idle_side, false);
    p1_anim_soldier_1_m16_running_side = animation_create(p1_adef_soldier_1_m16_running_side, true);
    p1_anim_soldier_1_m16_idle_back = animation_create(p1_adef_soldier_1_m16_idle_back, false);
    p1_anim_soldier_1_m16_running_back = animation_create(p1_adef_soldier_1_m16_running_back, true);
    p1_anim_soldier_1_m16_idle_front = animation_create(p1_adef_soldier_1_m16_idle_front, false);
    p1_anim_soldier_1_m16_running_front = animation_create(p1_adef_soldier_1_m16_running_front, true);
    p1_anim_soldier_1_m16_idle_up_right = animation_create(p1_adef_soldier_1_m16_idle_up_right, false);
    p1_anim_soldier_1_m16_running_up_right = animation_create(p1_adef_soldier_1_m16_running_up_right, true);
    p1_anim_soldier_1_m16_idle_down_right = animation_create(p1_adef_soldier_1_m16_idle_down_right, false);
    p1_anim_soldier_1_m16_running_down_right = animation_create(p1_adef_soldier_1_m16_running_down_right, true);
    p1_anim_soldier_1_m16_spawning_side = animation_create(p1_adef_soldier_1_m16_spawning_side, true);
    p1_anim_soldier_1_m16_dying_side = animation_create(p1_adef_soldier_1_m16_dying_side, true);

    // m16 w brewster
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_brewster_idle_side, "assets/soldier_1_m16_brewster_idle_side.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_brewster_running_side, "assets/soldier_1_m16_brewster_running_side.png", 36, 37);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_brewster_idle_back, "assets/soldier_1_m16_brewster_idle_back.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_brewster_running_back, "assets/soldier_1_m16_brewster_running_back.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_brewster_idle_front, "assets/soldier_1_m16_brewster_idle_front.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_brewster_running_front, "assets/soldier_1_m16_brewster_running_front.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_brewster_spawning_side, "assets/soldier_1_m16_spawning_side.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_brewster_dying_side, "assets/soldier_1_m16_dying_side.png", 42, 42);

    p1_adef_soldier_1_m16_brewster_idle_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_brewster_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m16_brewster_running_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_brewster_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    p1_adef_soldier_1_m16_brewster_idle_back = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_brewster_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m16_brewster_running_back = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_brewster_running_back,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    p1_adef_soldier_1_m16_brewster_idle_front = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_brewster_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m16_brewster_running_front = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_brewster_running_front,
        (f32[]){0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.04, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
    p1_adef_soldier_1_m16_brewster_spawning_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_brewster_spawning_side,
        (f32[]){0.25, 0.25},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    p1_adef_soldier_1_m16_brewster_dying_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m16_brewster_dying_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.75, 0.5, 0.5, 0.5, 0.75},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);

    p1_anim_soldier_1_m16_brewster_idle_side = animation_create(p1_adef_soldier_1_m16_brewster_idle_side, false);
    p1_anim_soldier_1_m16_brewster_running_side = animation_create(p1_adef_soldier_1_m16_brewster_running_side, true);
    p1_anim_soldier_1_m16_brewster_idle_back = animation_create(p1_adef_soldier_1_m16_brewster_idle_back, false);
    p1_anim_soldier_1_m16_brewster_running_back = animation_create(p1_adef_soldier_1_m16_brewster_running_back, true);
    p1_anim_soldier_1_m16_brewster_idle_front = animation_create(p1_adef_soldier_1_m16_brewster_idle_front, false);
    p1_anim_soldier_1_m16_brewster_running_front = animation_create(p1_adef_soldier_1_m16_brewster_running_front, true);
    p1_anim_soldier_1_m16_brewster_spawning_side = animation_create(p1_adef_soldier_1_m16_brewster_spawning_side, true);
    p1_anim_soldier_1_m16_brewster_dying_side = animation_create(p1_adef_soldier_1_m16_brewster_dying_side, true);

    // m44
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_idle_side, "assets/soldier_1_m44_idle_side.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_running_side, "assets/soldier_1_m44_running_side.png", 36, 37);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_idle_back, "assets/soldier_1_m44_idle_back.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_running_back, "assets/soldier_1_m44_running_back.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_idle_front, "assets/soldier_1_m44_idle_front.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_running_front, "assets/soldier_1_m44_running_front.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_spawning_side, "assets/soldier_1_m16_spawning_side.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_dying_side, "assets/soldier_1_m16_dying_side.png", 42, 42);

    p1_adef_soldier_1_m44_idle_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m44_running_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    p1_adef_soldier_1_m44_idle_back = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m44_running_back = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_running_back,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    p1_adef_soldier_1_m44_idle_front = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m44_running_front = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_running_front,
        (f32[]){0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.04, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
    p1_adef_soldier_1_m44_spawning_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_spawning_side,
        (f32[]){0.25, 0.25},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    p1_adef_soldier_1_m44_dying_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_dying_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.75, 0.5, 0.5, 0.5, 0.75},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);

    p1_anim_soldier_1_m44_idle_side = animation_create(p1_adef_soldier_1_m44_idle_side, false);
    p1_anim_soldier_1_m44_running_side = animation_create(p1_adef_soldier_1_m44_running_side, true);
    p1_anim_soldier_1_m44_idle_back = animation_create(p1_adef_soldier_1_m44_idle_back, false);
    p1_anim_soldier_1_m44_running_back = animation_create(p1_adef_soldier_1_m44_running_back, true);
    p1_anim_soldier_1_m44_idle_front = animation_create(p1_adef_soldier_1_m44_idle_front, false);
    p1_anim_soldier_1_m44_running_front = animation_create(p1_adef_soldier_1_m44_running_front, true);
    p1_anim_soldier_1_m44_spawning_side = animation_create(p1_adef_soldier_1_m44_spawning_side, true);
    p1_anim_soldier_1_m44_dying_side = animation_create(p1_adef_soldier_1_m44_dying_side, true);

    // m44 w brewster
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_brewster_idle_side, "assets/soldier_1_m44_brewster_idle_side.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_brewster_running_side, "assets/soldier_1_m44_brewster_running_side.png", 36, 37);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_brewster_idle_back, "assets/soldier_1_m44_brewster_idle_back.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_brewster_running_back, "assets/soldier_1_m44_brewster_running_back.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_brewster_idle_front, "assets/soldier_1_m44_brewster_idle_front.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_brewster_running_front, "assets/soldier_1_m44_brewster_running_front.png", 36, 36);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_brewster_spawning_side, "assets/soldier_1_m16_spawning_side.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m44_brewster_dying_side, "assets/soldier_1_m16_dying_side.png", 42, 42);

    p1_adef_soldier_1_m44_brewster_idle_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_brewster_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m44_brewster_running_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_brewster_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    p1_adef_soldier_1_m44_brewster_idle_back = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_brewster_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m44_brewster_running_back = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_brewster_running_back,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    p1_adef_soldier_1_m44_brewster_idle_front = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_brewster_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_1_m44_brewster_running_front = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_brewster_running_front,
        (f32[]){0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.04, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
    p1_adef_soldier_1_m44_brewster_spawning_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_brewster_spawning_side,
        (f32[]){0.25, 0.25},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    p1_adef_soldier_1_m44_brewster_dying_side = animation_definition_create(
        &p1_sprite_sheet_soldier_1_m44_brewster_dying_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.75, 0.5, 0.5, 0.5, 0.75},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);

    p1_anim_soldier_1_m44_brewster_idle_side = animation_create(p1_adef_soldier_1_m44_brewster_idle_side, false);
    p1_anim_soldier_1_m44_brewster_running_side = animation_create(p1_adef_soldier_1_m44_brewster_running_side, true);
    p1_anim_soldier_1_m44_brewster_idle_back = animation_create(p1_adef_soldier_1_m44_brewster_idle_back, false);
    p1_anim_soldier_1_m44_brewster_running_back = animation_create(p1_adef_soldier_1_m44_brewster_running_back, true);
    p1_anim_soldier_1_m44_brewster_idle_front = animation_create(p1_adef_soldier_1_m44_brewster_idle_front, false);
    p1_anim_soldier_1_m44_brewster_running_front = animation_create(p1_adef_soldier_1_m44_brewster_running_front, true);
    p1_anim_soldier_1_m44_brewster_spawning_side = animation_create(p1_adef_soldier_1_m44_brewster_spawning_side, true);
    p1_anim_soldier_1_m44_brewster_dying_side = animation_create(p1_adef_soldier_1_m44_brewster_dying_side, true);

    /*
     * player two animations
     */

    // m16
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_idle_side, "assets/soldier_1_m16_idle_side.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_running_side, "assets/soldier_1_m16_running_side.png", 36, 37);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_idle_back, "assets/soldier_1_m16_idle_back.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_running_back, "assets/soldier_1_m16_running_back.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_idle_front, "assets/soldier_1_m16_idle_front.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_running_front, "assets/soldier_1_m16_running_front.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_idle_up_right, "assets/soldier_1_m16_idle_up_right.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_running_up_right, "assets/soldier_1_m16_running_up_right.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_idle_down_right, "assets/soldier_1_m16_idle_down_right.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_running_down_right, "assets/soldier_1_m16_running_down_right.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_spawning_side, "assets/soldier_1_m16_spawning_side.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_dying_side, "assets/soldier_1_m16_dying_side.png", 42, 42);

    p2_adef_soldier_1_m16_idle_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m16_running_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    p2_adef_soldier_1_m16_idle_back = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m16_running_back = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_running_back,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    p2_adef_soldier_1_m16_idle_front = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m16_running_front = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_running_front,
        (f32[]){0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.04, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
    p2_adef_soldier_1_m16_idle_up_right = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_idle_up_right,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m16_running_up_right = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_running_up_right,
        (f32[]){0.06, 0.1, 0.08, 0.06, 0.1, 0.08},
        (u8[]){0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6},
        6);
    p2_adef_soldier_1_m16_idle_down_right = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_idle_down_right,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m16_running_down_right = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_running_down_right,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6},
        6);
    p2_adef_soldier_1_m16_spawning_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_spawning_side,
        (f32[]){0.25, 0.25},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    p2_adef_soldier_1_m16_dying_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_dying_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.75, 0.5, 0.5, 0.5, 0.75},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);

    p2_anim_soldier_1_m16_idle_side = animation_create(p2_adef_soldier_1_m16_idle_side, false);
    p2_anim_soldier_1_m16_running_side = animation_create(p2_adef_soldier_1_m16_running_side, true);
    p2_anim_soldier_1_m16_idle_back = animation_create(p2_adef_soldier_1_m16_idle_back, false);
    p2_anim_soldier_1_m16_running_back = animation_create(p2_adef_soldier_1_m16_running_back, true);
    p2_anim_soldier_1_m16_idle_front = animation_create(p2_adef_soldier_1_m16_idle_front, false);
    p2_anim_soldier_1_m16_running_front = animation_create(p2_adef_soldier_1_m16_running_front, true);
    p2_anim_soldier_1_m16_idle_up_right = animation_create(p2_adef_soldier_1_m16_idle_up_right, false);
    p2_anim_soldier_1_m16_running_up_right = animation_create(p2_adef_soldier_1_m16_running_up_right, true);
    p2_anim_soldier_1_m16_idle_down_right = animation_create(p2_adef_soldier_1_m16_idle_down_right, false);
    p2_anim_soldier_1_m16_running_down_right = animation_create(p2_adef_soldier_1_m16_running_down_right, true);
    p2_anim_soldier_1_m16_spawning_side = animation_create(p2_adef_soldier_1_m16_spawning_side, true);
    p2_anim_soldier_1_m16_dying_side = animation_create(p2_adef_soldier_1_m16_dying_side, true);

    // m16 w brewster
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_brewster_idle_side, "assets/soldier_1_m16_brewster_idle_side.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_brewster_running_side, "assets/soldier_1_m16_brewster_running_side.png", 36, 37);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_brewster_idle_back, "assets/soldier_1_m16_brewster_idle_back.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_brewster_running_back, "assets/soldier_1_m16_brewster_running_back.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_brewster_idle_front, "assets/soldier_1_m16_brewster_idle_front.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_brewster_running_front, "assets/soldier_1_m16_brewster_running_front.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_brewster_spawning_side, "assets/soldier_1_m16_spawning_side.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_brewster_dying_side, "assets/soldier_1_m16_dying_side.png", 42, 42);

    p2_adef_soldier_1_m16_brewster_idle_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_brewster_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m16_brewster_running_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_brewster_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    p2_adef_soldier_1_m16_brewster_idle_back = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_brewster_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m16_brewster_running_back = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_brewster_running_back,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    p2_adef_soldier_1_m16_brewster_idle_front = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_brewster_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m16_brewster_running_front = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_brewster_running_front,
        (f32[]){0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.04, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
    p2_adef_soldier_1_m16_brewster_spawning_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_brewster_spawning_side,
        (f32[]){0.25, 0.25},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    p2_adef_soldier_1_m16_brewster_dying_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m16_brewster_dying_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.75, 0.5, 0.5, 0.5, 0.75},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);

    p2_anim_soldier_1_m16_brewster_idle_side = animation_create(p2_adef_soldier_1_m16_brewster_idle_side, false);
    p2_anim_soldier_1_m16_brewster_running_side = animation_create(p2_adef_soldier_1_m16_brewster_running_side, true);
    p2_anim_soldier_1_m16_brewster_idle_back = animation_create(p2_adef_soldier_1_m16_brewster_idle_back, false);
    p2_anim_soldier_1_m16_brewster_running_back = animation_create(p2_adef_soldier_1_m16_brewster_running_back, true);
    p2_anim_soldier_1_m16_brewster_idle_front = animation_create(p2_adef_soldier_1_m16_brewster_idle_front, false);
    p2_anim_soldier_1_m16_brewster_running_front = animation_create(p2_adef_soldier_1_m16_brewster_running_front, true);
    p2_anim_soldier_1_m16_brewster_spawning_side = animation_create(p2_adef_soldier_1_m16_brewster_spawning_side, true);
    p2_anim_soldier_1_m16_brewster_dying_side = animation_create(p2_adef_soldier_1_m16_brewster_dying_side, true);

    // m44
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_idle_side, "assets/soldier_1_m44_idle_side.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_running_side, "assets/soldier_1_m44_running_side.png", 36, 37);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_idle_back, "assets/soldier_1_m44_idle_back.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_running_back, "assets/soldier_1_m44_running_back.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_idle_front, "assets/soldier_1_m44_idle_front.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_running_front, "assets/soldier_1_m44_running_front.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_spawning_side, "assets/soldier_1_m16_spawning_side.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_dying_side, "assets/soldier_1_m16_dying_side.png", 42, 42);

    p2_adef_soldier_1_m44_idle_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m44_running_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    p2_adef_soldier_1_m44_idle_back = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m44_running_back = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_running_back,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    p2_adef_soldier_1_m44_idle_front = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m44_running_front = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_running_front,
        (f32[]){0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.04, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
    p2_adef_soldier_1_m44_spawning_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_spawning_side,
        (f32[]){0.25, 0.25},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    p2_adef_soldier_1_m44_dying_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_dying_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.75, 0.5, 0.5, 0.5, 0.75},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);

    p2_anim_soldier_1_m44_idle_side = animation_create(p2_adef_soldier_1_m44_idle_side, false);
    p2_anim_soldier_1_m44_running_side = animation_create(p2_adef_soldier_1_m44_running_side, true);
    p2_anim_soldier_1_m44_idle_back = animation_create(p2_adef_soldier_1_m44_idle_back, false);
    p2_anim_soldier_1_m44_running_back = animation_create(p2_adef_soldier_1_m44_running_back, true);
    p2_anim_soldier_1_m44_idle_front = animation_create(p2_adef_soldier_1_m44_idle_front, false);
    p2_anim_soldier_1_m44_running_front = animation_create(p2_adef_soldier_1_m44_running_front, true);
    p2_anim_soldier_1_m44_spawning_side = animation_create(p2_adef_soldier_1_m44_spawning_side, true);
    p2_anim_soldier_1_m44_dying_side = animation_create(p2_adef_soldier_1_m44_dying_side, true);

    // m44 w brewster
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_brewster_idle_side, "assets/soldier_1_m44_brewster_idle_side.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_brewster_running_side, "assets/soldier_1_m44_brewster_running_side.png", 36, 37);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_brewster_idle_back, "assets/soldier_1_m44_brewster_idle_back.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_brewster_running_back, "assets/soldier_1_m44_brewster_running_back.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_brewster_idle_front, "assets/soldier_1_m44_brewster_idle_front.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_brewster_running_front, "assets/soldier_1_m44_brewster_running_front.png", 36, 36);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_brewster_spawning_side, "assets/soldier_1_m16_spawning_side.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m44_brewster_dying_side, "assets/soldier_1_m16_dying_side.png", 42, 42);

    p2_adef_soldier_1_m44_brewster_idle_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_brewster_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m44_brewster_running_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_brewster_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    p2_adef_soldier_1_m44_brewster_idle_back = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_brewster_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m44_brewster_running_back = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_brewster_running_back,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    p2_adef_soldier_1_m44_brewster_idle_front = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_brewster_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_1_m44_brewster_running_front = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_brewster_running_front,
        (f32[]){0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.04, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
    p2_adef_soldier_1_m44_brewster_spawning_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_brewster_spawning_side,
        (f32[]){0.25, 0.25},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    p2_adef_soldier_1_m44_brewster_dying_side = animation_definition_create(
        &p2_sprite_sheet_soldier_1_m44_brewster_dying_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.75, 0.5, 0.5, 0.5, 0.75},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);

    p2_anim_soldier_1_m44_brewster_idle_side = animation_create(p2_adef_soldier_1_m44_brewster_idle_side, false);
    p2_anim_soldier_1_m44_brewster_running_side = animation_create(p2_adef_soldier_1_m44_brewster_running_side, true);
    p2_anim_soldier_1_m44_brewster_idle_back = animation_create(p2_adef_soldier_1_m44_brewster_idle_back, false);
    p2_anim_soldier_1_m44_brewster_running_back = animation_create(p2_adef_soldier_1_m44_brewster_running_back, true);
    p2_anim_soldier_1_m44_brewster_idle_front = animation_create(p2_adef_soldier_1_m44_brewster_idle_front, false);
    p2_anim_soldier_1_m44_brewster_running_front = animation_create(p2_adef_soldier_1_m44_brewster_running_front, true);
    p2_anim_soldier_1_m44_brewster_spawning_side = animation_create(p2_adef_soldier_1_m44_brewster_spawning_side, true);
    p2_anim_soldier_1_m44_brewster_dying_side = animation_create(p2_adef_soldier_1_m44_brewster_dying_side, true);

    // bullet stuff
    render_sprite_sheet_init(&sprite_sheet_bullet_1_horizontal, "assets/bullet_round_small.png", 2, 2);
    render_sprite_sheet_init(&sprite_sheet_bullet_1_vertical, "assets/bullet_round_small.png", 2, 2);
    adef_bullet_1_horizontal = animation_definition_create(
        &sprite_sheet_bullet_1_horizontal,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    adef_bullet_1_vertical = animation_definition_create(
        &sprite_sheet_bullet_1_vertical,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_1_horizontal = animation_create(adef_bullet_1_horizontal, false);
    anim_bullet_1_vertical = animation_create(adef_bullet_1_vertical, false);

    /*
    NEW PLAYER ANIMS 11/12
    */
    render_sprite_sheet_init(&sprite_sheet_soldier_purple_base_idle_back, "assets/soldier_purple_base_idle_back.png", 175, 175);
    adef_soldier_purple_base_idle_back = animation_definition_create(
        &sprite_sheet_soldier_purple_base_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_anim_soldier_purple_base_idle_back = animation_create(adef_soldier_purple_base_idle_back, false);
    p2_anim_soldier_purple_base_idle_back = animation_create(adef_soldier_purple_base_idle_back, false);

    render_sprite_sheet_init(&sprite_sheet_soldier_purple_base_idle_side, "assets/soldier_purple_base_idle_side.png", 175, 175);
    adef_soldier_purple_base_idle_side = animation_definition_create(
        &sprite_sheet_soldier_purple_base_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_anim_soldier_purple_base_idle_side = animation_create(adef_soldier_purple_base_idle_side, false);
    p2_anim_soldier_purple_base_idle_side = animation_create(adef_soldier_purple_base_idle_side, false);

    render_sprite_sheet_init(&sprite_sheet_soldier_purple_base_idle_front, "assets/soldier_purple_base_idle_front.png", 175, 175);
    adef_soldier_purple_base_idle_front = animation_definition_create(
        &sprite_sheet_soldier_purple_base_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_anim_soldier_purple_base_idle_front = animation_create(adef_soldier_purple_base_idle_front, false);
    p2_anim_soldier_purple_base_idle_front = animation_create(adef_soldier_purple_base_idle_front, false);

    init_bullet_anim_hashmap();
    init_player_anim_hashmap();
}

// initializes the player struct
void init_player(Player *player, Map *map, Weapon_Type *starting_weapon, f32 despawn_time, f32 spawn_delay, f32 spawn_time, bool is_left_player)
{
    player->entity = entity_create((vec2){render_width * 0.5, render_height * 0.5}, (vec2){40, 75}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static);
    player->entity->body->parent = player;
    player->crosshair = malloc(sizeof(Crosshair));
    player->crosshair->entity = entity_create((vec2){player->entity->body->aabb.position[0], player->entity->body->aabb.position[1]}, (vec2){27, 27}, (vec2){0, 0}, COLLISION_LAYER_CROSSHAIR, crosshair_mask, crosshair_on_hit, crosshair_on_hit_static);
    player->crosshair->relative_position[0] = player->entity->body->aabb.position[0];
    player->crosshair->relative_position[1] = player->entity->body->aabb.position[1];
    player->crosshair->entity->is_active = false;
    player->direction = RIGHT;

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
    player->weapon->burst_delay = starting_weapon->burst_delay;
    player->weapon->aiming_scale_factor = starting_weapon->aiming_scale_factor;
    player->weapon->frames_since_last_shot = 0;
    player->weapon->ready_to_fire = true;
    player->weapon->hud_ammo_icon = starting_weapon->hud_ammo_icon;

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
    if (is_left_player)
    {
        player->camera = SPLIT_SCREEN ? &left_cam : &main_cam;
    }
    else
    {
        player->camera = &right_cam;
    }
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
    player->direction = RIGHT;

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
    player->weapon->aiming_scale_factor = starting_weapon->aiming_scale_factor;
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
    if (player->status == PLAYER_INACTIVE && player->frames_on_status >= (player->spawn_delay * global.time.frame_rate))
    {
        spawn_player(player, m16);
    }

    // check if spawn time is up
    else if (player->status == PLAYER_SPAWNING && player->frames_on_status >= (player->spawn_time * global.time.frame_rate))
    {
        player->status = PLAYER_ACTIVE;
        player->frames_on_status = 0;
    }

    // DESPAWN LOGIC
    // check if health is 0
    else if (player->health <= 0 && player->status == PLAYER_ACTIVE)
    {
        player->status = PLAYER_DESPAWNING;
        player->render_scale_factor = DEFAULT_RENDER_SCALE_FACTOR;
        player->frames_on_status = 0;

        // shouldn't be moving on death anim
        player->entity->body->velocity[0] = 0;
        player->entity->body->velocity[1] = 0;
    }
    // check if death animation is complete
    else if (player->status == PLAYER_DESPAWNING && player->frames_on_status >= (player->despawn_time * global.time.frame_rate))
    {
        player->status = PLAYER_INACTIVE;
        player->frames_on_status = 0;

        // hide sprites
        player->entity->is_active = false;
        player->entity->body->is_active = false;
    }

    // WEAPON STATUS LOGIC
    // reloading logic
    if (player->status == PLAYER_RELOADING)
    {
        // reload either the missing bullets in the magazine or whatever the player has left in reserve
        u16 reload_amount = MIN(player->weapon->reserve, (player->weapon->max_capacity - player->weapon->capacity));
        player->weapon->capacity += reload_amount;
        player->weapon->reserve -= reload_amount;
        // TODO: add animation / reload wait time logic
        player->status = PLAYER_ACTIVE;
    }

    // update weapon status (check if weapon is ready to fire again)
    if (player->status != PLAYER_RELOADING && !player->weapon->ready_to_fire && player->weapon->frames_since_last_shot >= ((1.0 / (player->weapon->max_fire_rate / 60.0)) * global.time.frame_rate))
    {
        if (player->weapon->fire_mode == AUTO || player->weapon->fire_mode == SEMI)
        {
            player->weapon->ready_to_fire = true;
        }

        // need an additional check for burst weapons, is ready to fire if burst shots are left OR if burst delay is complete
        else if (player->weapon->fire_mode == BURST && (player->weapon->burst_shots_remaining > 0 || (player->weapon->frames_since_last_shot * (1.0 / global.time.frame_rate)) >= player->weapon->burst_delay))
        {
            if (player->weapon->burst_shots_remaining == 0 && (player->weapon->frames_since_last_shot * (1.0 / global.time.frame_rate) >= player->weapon->burst_delay))
            {
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
 * Animations are named in the following manner: character_weapon_armor_movement-status_direction
 */
void update_player_animations(Player *player)
{
    if (player->status == PLAYER_INACTIVE)
    {
        return;
    }

    // cache old anim to check if we are SWITCHING anims
    Animation *prev_anim = player->entity->animation;

    char *anim_name = calloc(50, sizeof(char));
    char *player_side = player->is_left_player ? "p1_anim" : "p2_anim";
    char *character = "soldier_purple"; // player->character
    char *weapon = player->weapon->name;
    char *armor = player->armor->name;
    char *status;
    if (player->status == PLAYER_SPAWNING)
        status = "spawning";
    else if (player->status == PLAYER_DESPAWNING)
        status = "dying";
    else if (player->entity->body->velocity[0] || player->entity->body->velocity[1])
        status = "running";
    else // player NOT moving
        status = "idle";
    char *direction;
    if (player->direction == LEFT || player->direction == RIGHT)
        direction = "side";
    else if (player->direction == UP)
        direction = "back";
    else if (player->direction == UP_RIGHT)
        direction = "up_right";
    else if (player->direction == DOWN_RIGHT)
        direction = "down_right";
    else // player->direction == DOWN
        direction = "front";
    strcat(anim_name, player_side);
    strcat(anim_name, "_");
    strcat(anim_name, character);
    strcat(anim_name, "_");
    strcat(anim_name, weapon);
    strcat(anim_name, "_");
    if (strcmp(armor, "") != 0)
    {
        strcat(anim_name, armor);
        strcat(anim_name, "_");
    }
    strcat(anim_name, status);
    strcat(anim_name, "_");
    strcat(anim_name, direction);

    Animation *player_anim = get(player_anim_map, anim_name);
    if (player_anim)
        player->entity->animation = player_anim;
    else
        player->entity->animation = anim_player_placeholder;

    // ensure we are starting new anims at the first frame
    if (player->entity->animation != prev_anim)
        player->entity->animation->current_frame_index = 0;

    // TODO: remove this once animations are added for facing left (right now right facing anims are flipped and reused)
    player->entity->animation->is_flipped = player->direction == LEFT ? true : false;

    free(anim_name);
}

void handle_player_shooting(Player *player, Key_State shoot)
{
    // check if key presses are correct based on fire mode
    bool key_state_ready = false;
    if ((player->weapon->fire_mode == AUTO && shoot == KS_HELD) || (player->weapon->fire_mode == SEMI && shoot == KS_PRESSED))
    {
        key_state_ready = true;
    }
    else if (player->weapon->fire_mode == BURST && ((player->weapon->burst_shots_remaining == player->weapon->burst_count && shoot == KS_PRESSED) || (player->weapon->burst_shots_remaining < player->weapon->burst_count && shoot == KS_HELD)))
    {
        key_state_ready = true;
    }

    // generate bullet if weapon is loaded and key state is correct
    if (player->weapon->capacity > 0 && player->weapon->ready_to_fire && key_state_ready)
    {
        f32 cx = 0;
        f32 cy = 0;
        f32 px = player->relative_position[0];
        f32 py = player->relative_position[1];
        vec2 bullet_position = {player->relative_position[0], player->relative_position[1]};
        vec2 bullet_velocity = {0, 0};

        // shoot at crosshair if present
        if (player->crosshair->entity->is_active)
        {
            // populate crosshair position
            cx = player->crosshair->relative_position[0];
            cy = player->crosshair->relative_position[1];
        }
        else
        { // player not crouching
            if (player->direction == UP)
            {
                cx = px;
                cy = py + 1;
            }
            else if (player->direction == RIGHT)
            {
                cx = px + 1;
                cy = py;
            }
            else if (player->direction == DOWN)
            {
                cx = px;
                cy = py - 1;
            }
            else if (player->direction == LEFT)
            {
                cx = px - 1;
                cy = py;
            }
            else if (player->direction == UP_RIGHT)
            {
                cx = px + 1;
                cy = py + 1;
            }
            else if (player->direction == UP_LEFT)
            {
                cx = px - 1;
                cy = py + 1;
            }
            else if (player->direction == DOWN_RIGHT)
            {
                cx = px + 1;
                cy = py - 1;
            }
            else if (player->direction == DOWN_LEFT)
            {
                cx = px - 1;
                cy = py - 1;
            }
        }

        // calculate angle
        f32 dx = px - cx;
        f32 dy = py - cy;
        f32 angle = fabs((cx > px && cy > py) || (cx < px && cy < py) ? atan(dy / dx) : -1 * atan(dy / dx));

        // calculate bullet starting position using angle
        f32 bullet_x = cx >= px ? BULLET_DISTANCE_FROM_PLAYER * cos(angle) : BULLET_DISTANCE_FROM_PLAYER * cos(angle) * -1;
        f32 bullet_y = cy >= py ? BULLET_DISTANCE_FROM_PLAYER * sin(angle) : BULLET_DISTANCE_FROM_PLAYER * sin(angle) * -1;

        // calculate starting position using angle
        bullet_position[0] = player->relative_position[0] + bullet_x;
        bullet_position[1] = player->relative_position[1] + bullet_y;

        // calculate velocity using angle
        f32 vx = cx >= px ? player->weapon->bullet_velocity * cos(angle) : player->weapon->bullet_velocity * cos(angle) * -1;
        f32 vy = cy >= py ? player->weapon->bullet_velocity * sin(angle) : player->weapon->bullet_velocity * sin(angle) * -1;
        bullet_velocity[0] = vx;
        bullet_velocity[1] = vy;

        // correct angle
        if (cx < px && cy > py) // 2nd quadrant
            angle = M_PI - angle;
        else if (cx < px && cy < py) // 3rd quadrant
            angle += M_PI;
        else if (cx > px && cy < py) // 4th quadrant
            angle = 2 * M_PI - angle;

        // check which of 16 buckets it falls into, assign animation
        char *bullet_anim_name;
        if (angle >= 6.1 || angle < 0.2)
        {
            bullet_anim_name = "bullet_0";
        }
        else if (angle >= 0.2 && angle < 0.59)
        {
            bullet_anim_name = "bullet_1";
        }
        else if (angle >= 0.59 && angle < 0.983)
        {
            bullet_anim_name = "bullet_2";
        }
        else if (angle >= 0.983 && angle < 1.375)
        {
            bullet_anim_name = "bullet_3";
        }
        else if (angle >= 1.375 && angle < 1.769)
        {
            bullet_anim_name = "bullet_4";
        }
        else if (angle >= 1.769 && angle < 2.163)
        {
            bullet_anim_name = "bullet_5";
        }
        else if (angle >= 2.163 && angle < 2.557)
        {
            bullet_anim_name = "bullet_6";
        }
        else if (angle >= 2.557 && angle < 2.95)
        {
            bullet_anim_name = "bullet_7";
        }
        else if (angle >= 2.95 && angle < 3.344)
        {
            bullet_anim_name = "bullet_8";
        }
        else if (angle >= 3.344 && angle < 3.738)
        {
            bullet_anim_name = "bullet_9";
        }
        else if (angle >= 3.738 && angle < 4.131)
        {
            bullet_anim_name = "bullet_10";
        }
        else if (angle >= 4.131 && angle < 4.525)
        {
            bullet_anim_name = "bullet_11";
        }
        else if (angle >= 4.525 && angle < 4.919)
        {
            bullet_anim_name = "bullet_12";
        }
        else if (angle >= 4.919 && angle < 5.313)
        {
            bullet_anim_name = "bullet_13";
        }
        else if (angle >= 5.313 && angle < 5.706)
        {
            bullet_anim_name = "bullet_14";
        }
        else if (angle >= 5.706 && angle < 6.1)
        {
            bullet_anim_name = "bullet_15";
        }

        // create bullet struct and calculated anim and velocity
        Bullet *bullet = malloc(sizeof(Bullet));
        bullet->entity = entity_create(bullet_position, (vec2){5, 5}, (vec2){0, 0}, COLLISION_LAYER_BULLET, bullet_mask, bullet_on_hit, bullet_on_hit_static);
        bullet->damage = player->weapon->damage;
        bullet->entity->animation = get(bullet_anim_map, bullet_anim_name);
        bullet->entity->body->velocity[0] = bullet_velocity[0];
        bullet->entity->body->velocity[1] = bullet_velocity[1];
        bullet->entity->body->parent = bullet;

        // decrement weapon capacity
        player->weapon->capacity -= 1;

        if (player->weapon->fire_mode == BURST)
        {
            player->weapon->burst_shots_remaining -= 1;
        }

        // restart rounds per minute timer
        player->weapon->ready_to_fire = false;
        player->weapon->frames_since_last_shot = 0;
    }
}

/*
 *   handles key inputs of players, typically updates player status, other attributes
 *
 *   Priority of keys is as follows - crouch, reload, movement, shoot.
 *   Players can only shoot while crouching.
 *   Players cannot reload while doing any other actions (running, crouching, shooting)
 */
void handle_player_input(Player *player)
{
    if (player->status == PLAYER_SPAWNING || player->status == PLAYER_DESPAWNING || player->status == PLAYER_INACTIVE) // don't allow inputs on inactive players
    {
        return;
    }

    Key_State left = player->is_left_player ? global.input.l_left : global.input.r_left;
    Key_State right = player->is_left_player ? global.input.l_right : global.input.r_right;
    Key_State up = player->is_left_player ? global.input.l_up : global.input.r_up;
    Key_State down = player->is_left_player ? global.input.l_down : global.input.r_down;
    Key_State shoot = player->is_left_player ? global.input.l_shoot : global.input.r_shoot;
    Key_State crouch = player->is_left_player ? global.input.l_crouch : global.input.r_crouch;
    Key_State reload = player->is_left_player ? global.input.l_reload : global.input.r_reload;

    f32 velx = 0;
    f32 vely = 0;

    /*
     * check if player is crouched
     *
     * if so, update player anim to crouch, create crosshair entity
     * and track movement input to the crosshair instead of the player
     */

    if (crouch)
    {
        if (player->status != PLAYER_CROUCHED)
        {
            player->render_scale_factor = player->weapon->aiming_scale_factor;

            // update rendering dimensions and projection matrix
            set_render_dimensions(player->render_scale_factor, false, true);

            // set aabb location to center of screen
            player->entity->body->aabb.position[0] = (render_width * 0.5);
            player->entity->body->aabb.position[1] = (render_height * 0.5);

            // set camera location to center the player
            player->camera->position[0] = player->relative_position[0] - (0.5 * render_width);
            player->camera->position[1] = player->relative_position[1] - (0.5 * render_height);

            // update status
            player->status = PLAYER_CROUCHED;
        }

        // don't let players move while crouching
        player->entity->body->velocity[0] = 0;
        player->entity->body->velocity[1] = 0;

        // if player doesn't already have a crosshair entity associated, create one
        if (!player->crosshair->entity->is_active)
        {
            // calculate where the crosshair will start using the player's direction
            const f32 crosshair_starting_distance_from_player = 50;
            f32 crosshair_xy_distance_at_45_deg = 0.707106781 * crosshair_starting_distance_from_player; // sin/cos(45) * hypotenuse
            vec2 crosshair_starting_distance_vector = {0, 0};

            if (player->direction == UP)
                crosshair_starting_distance_vector[1] = crosshair_starting_distance_from_player;
            if (player->direction == RIGHT)
                crosshair_starting_distance_vector[0] = crosshair_starting_distance_from_player;
            if (player->direction == DOWN)
                crosshair_starting_distance_vector[1] = -1 * crosshair_starting_distance_from_player;
            if (player->direction == LEFT)
                crosshair_starting_distance_vector[0] = -1 * crosshair_starting_distance_from_player;
            if (player->direction == UP_RIGHT)
            {
                crosshair_starting_distance_vector[0] = crosshair_xy_distance_at_45_deg;
                crosshair_starting_distance_vector[1] = crosshair_xy_distance_at_45_deg;
            }
            if (player->direction == DOWN_RIGHT)
            {
                crosshair_starting_distance_vector[0] = crosshair_xy_distance_at_45_deg;
                crosshair_starting_distance_vector[1] = -1 * crosshair_xy_distance_at_45_deg;
            }

            if (player->direction == DOWN_LEFT)
            {
                crosshair_starting_distance_vector[0] = -1 * crosshair_xy_distance_at_45_deg;
                crosshair_starting_distance_vector[1] = -1 * crosshair_xy_distance_at_45_deg;
            }

            if (player->direction == UP_LEFT)
            {
                crosshair_starting_distance_vector[0] = -1 * crosshair_xy_distance_at_45_deg;
                crosshair_starting_distance_vector[1] = crosshair_xy_distance_at_45_deg;
            }

            // set crosshair aabb position with respect to player aabb position
            player->crosshair->entity->body->aabb.position[0] = player->entity->body->aabb.position[0] + crosshair_starting_distance_vector[0];
            player->crosshair->entity->body->aabb.position[1] = player->entity->body->aabb.position[1] + crosshair_starting_distance_vector[1];

            // set crosshair relative position with respect to player relative position
            player->crosshair->relative_position[0] = player->relative_position[0] + crosshair_starting_distance_vector[0];
            player->crosshair->relative_position[1] = player->relative_position[1] + crosshair_starting_distance_vector[1];

            // activate entity and set anim
            player->crosshair->entity->is_active = true;
            player->crosshair->entity->animation = anim_crosshair_red;
        }

        // movement inputs now move crosshair instead of player
        if (left)
            velx -= DEFAULT_PLAYER_MOVEMENT_SPEED;
        if (right)
            velx += DEFAULT_PLAYER_MOVEMENT_SPEED;
        if (up)
            vely += DEFAULT_PLAYER_MOVEMENT_SPEED;
        if (down)
            vely -= DEFAULT_PLAYER_MOVEMENT_SPEED;

        // check if crosshair is out of bounds, if so, put in bounds, set velocity to 0
        if (player->crosshair->entity->body->aabb.position[0] < 0)
        {
            player->crosshair->entity->body->aabb.position[0] = 0;
            velx = 0;
        }
        if (player->crosshair->entity->body->aabb.position[0] > render_width)
        {
            player->crosshair->entity->body->aabb.position[0] = render_width;
            velx = 0;
        }
        if (player->crosshair->entity->body->aabb.position[1] < 0)
        {
            player->crosshair->entity->body->aabb.position[1] = 0;
            vely = 0;
        }
        if (player->crosshair->entity->body->aabb.position[1] > render_height)
        {
            player->crosshair->entity->body->aabb.position[1] = render_height;
            vely = 0;
        }

        player->crosshair->entity->body->velocity[0] = velx;
        player->crosshair->entity->body->velocity[1] = vely;

        handle_player_shooting(player, shoot);
        return;
    }

    // handle reloading (logic implemented in update_player_status)
    if (reload)
    {
        player->status = PLAYER_RELOADING;
        return;
    }

    // if player isn't crouched updated status, make sure the crosshair isn't activated, and reset view to normal
    if (player->status == PLAYER_CROUCHED)
    {
        // update player and crosshair status
        player->status = PLAYER_ACTIVE;
        player->crosshair->entity->is_active = false;

        // reset render dimensions and projection matrix
        player->render_scale_factor = DEFAULT_RENDER_SCALE_FACTOR;
        set_render_dimensions(player->render_scale_factor, false, true);

        // center camera on player
        player->camera->position[0] = player->relative_position[0] - (0.5 * render_width);
        player->camera->position[1] = player->relative_position[1] - (0.5 * render_height);

        // center player aabb
        player->entity->body->aabb.position[0] = (render_width * 0.5);
        player->entity->body->aabb.position[1] = (render_height * 0.5);
    }

    // 8 directional movement
    f32 angle = 0.78539816; // 45 degrees in radians
    f32 xy_magnitude = sin(angle) * DEFAULT_PLAYER_MOVEMENT_SPEED;
    if (up && right)
    {
        player->direction = UP_RIGHT;
        velx += xy_magnitude;
        vely += xy_magnitude;
    }
    else if (up && left)
    {
        player->direction = UP_LEFT;
        velx -= xy_magnitude;
        vely += xy_magnitude;
    }
    else if (down && right)
    {
        player->direction = DOWN_RIGHT;
        velx += xy_magnitude;
        vely -= xy_magnitude;
    }
    else if (down && left)
    {
        player->direction = DOWN_LEFT;
        velx -= xy_magnitude;
        vely -= xy_magnitude;
    }
    else if (right)
    {
        player->direction = RIGHT;
        velx += DEFAULT_PLAYER_MOVEMENT_SPEED;
    }

    else if (left)
    {
        player->direction = LEFT;
        velx -= DEFAULT_PLAYER_MOVEMENT_SPEED;
    }

    else if (up)
    {
        player->direction = UP;
        vely += DEFAULT_PLAYER_MOVEMENT_SPEED;
    }

    else if (down)
    {
        player->direction = DOWN;
        vely -= DEFAULT_PLAYER_MOVEMENT_SPEED;
    }

    // handle weapon attribute updates & bullet generation, contingent on fire mode, input, and weapon shot cooldown
    handle_player_shooting(player, shoot);

    player->entity->body->velocity[0] = velx;
    player->entity->body->velocity[1] = vely;
}

// cleans up the player struct
void free_player(Player *player)
{
    free(player->crosshair);
    free(player);
}

// helper to get the player from a body (if associated), used in on_hit helpers
Player *get_player_from_body(Player *player_one, Player *player_two, Body *body, bool return_other_player)
{
    if (player_one->entity->body == body)
    {
        return !return_other_player ? player_one : player_two;
    }
    else if (SPLIT_SCREEN && player_two->entity->body == body)
    {
        return !return_other_player ? player_two : player_one;
    }
    else
    {
        return NULL;
    }
}