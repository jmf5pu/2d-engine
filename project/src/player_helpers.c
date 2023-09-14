#include <math.h> // for pi approximation
#include "engine/global.h"
#include "engine/util.h"
#include "player_helpers.h"
#include "collision_behavior.h"
#include "weapon_types.h"

// declare players
Player *player_one;
Player *player_two;

// init animation hash_map
void init_player_anim_hashmap()
{
    player_anim_map = create_hash_map(PLAYER_ANIM_COUNT);

    // player one stuff
    insert(player_anim_map, "p1_anim_soldier_1_m16_idle_side", p1_anim_soldier_1_m16_idle_side);
    insert(player_anim_map, "p1_anim_soldier_1_m16_running_side", p1_anim_soldier_1_m16_running_side);
    insert(player_anim_map, "p1_anim_soldier_1_m16_idle_back", p1_anim_soldier_1_m16_idle_back);
    insert(player_anim_map, "p1_anim_soldier_1_m16_running_back", p1_anim_soldier_1_m16_running_back);
    insert(player_anim_map, "p1_anim_soldier_1_m16_idle_front", p1_anim_soldier_1_m16_idle_front);
    insert(player_anim_map, "p1_anim_soldier_1_m16_running_front", p1_anim_soldier_1_m16_running_front);
    insert(player_anim_map, "p1_anim_soldier_1_m16_idle_up_right", p1_anim_soldier_1_m16_idle_up_right);
    insert(player_anim_map, "p1_anim_soldier_1_m16_running_up_right", p1_anim_soldier_1_m16_running_up_right);
    insert(player_anim_map, "p1_anim_soldier_1_m16_idle_down_right", p1_anim_soldier_1_m16_idle_down_right);
    insert(player_anim_map, "p1_anim_soldier_1_m16_running_down_right", p1_anim_soldier_1_m16_running_down_right);
    insert(player_anim_map, "p1_anim_soldier_1_m16_spawning_side", p1_anim_soldier_1_m16_spawning_side);
    insert(player_anim_map, "p1_anim_soldier_1_m16_dying_side", p1_anim_soldier_1_m16_dying_side);

    insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_idle_side", p1_anim_soldier_1_m16_brewster_idle_side);
    insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_running_side", p1_anim_soldier_1_m16_brewster_running_side);
    insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_idle_back", p1_anim_soldier_1_m16_brewster_idle_back);
    insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_running_back", p1_anim_soldier_1_m16_brewster_running_back);
    insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_idle_front", p1_anim_soldier_1_m16_brewster_idle_front);
    insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_running_front", p1_anim_soldier_1_m16_brewster_running_front);
    insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_spawning_side", p1_anim_soldier_1_m16_brewster_spawning_side);
    insert(player_anim_map, "p1_anim_soldier_1_m16_brewster_dying_side", p1_anim_soldier_1_m16_brewster_dying_side);

    insert(player_anim_map, "p1_anim_soldier_1_m44_idle_side", p1_anim_soldier_1_m44_idle_side);
    insert(player_anim_map, "p1_anim_soldier_1_m44_running_side", p1_anim_soldier_1_m44_running_side);
    insert(player_anim_map, "p1_anim_soldier_1_m44_idle_back", p1_anim_soldier_1_m44_idle_back);
    insert(player_anim_map, "p1_anim_soldier_1_m44_running_back", p1_anim_soldier_1_m44_running_back);
    insert(player_anim_map, "p1_anim_soldier_1_m44_idle_front", p1_anim_soldier_1_m44_idle_front);
    insert(player_anim_map, "p1_anim_soldier_1_m44_running_front", p1_anim_soldier_1_m44_running_front);
    insert(player_anim_map, "p1_anim_soldier_1_m44_spawning_side", p1_anim_soldier_1_m44_spawning_side);
    insert(player_anim_map, "p1_anim_soldier_1_m44_dying_side", p1_anim_soldier_1_m44_dying_side);

    insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_idle_side", p1_anim_soldier_1_m44_brewster_idle_side);
    insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_running_side", p1_anim_soldier_1_m44_brewster_running_side);
    insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_idle_back", p1_anim_soldier_1_m44_brewster_idle_back);
    insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_running_back", p1_anim_soldier_1_m44_brewster_running_back);
    insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_idle_front", p1_anim_soldier_1_m44_brewster_idle_front);
    insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_running_front", p1_anim_soldier_1_m44_brewster_running_front);
    insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_spawning_side", p1_anim_soldier_1_m44_brewster_spawning_side);
    insert(player_anim_map, "p1_anim_soldier_1_m44_brewster_dying_side", p1_anim_soldier_1_m44_brewster_dying_side);

    insert(player_anim_map, "p2_anim_soldier_1_m16_idle_side", p2_anim_soldier_1_m16_idle_side);
    insert(player_anim_map, "p2_anim_soldier_1_m16_running_side", p2_anim_soldier_1_m16_running_side);
    insert(player_anim_map, "p2_anim_soldier_1_m16_idle_back", p2_anim_soldier_1_m16_idle_back);
    insert(player_anim_map, "p2_anim_soldier_1_m16_running_back", p2_anim_soldier_1_m16_running_back);
    insert(player_anim_map, "p2_anim_soldier_1_m16_idle_front", p2_anim_soldier_1_m16_idle_front);
    insert(player_anim_map, "p2_anim_soldier_1_m16_running_front", p2_anim_soldier_1_m16_running_front);
    insert(player_anim_map, "p2_anim_soldier_1_m16_idle_up_right", p2_anim_soldier_1_m16_idle_up_right);
    insert(player_anim_map, "p2_anim_soldier_1_m16_running_up_right", p2_anim_soldier_1_m16_running_up_right);
    insert(player_anim_map, "p2_anim_soldier_1_m16_idle_down_right", p2_anim_soldier_1_m16_idle_down_right);
    insert(player_anim_map, "p2_anim_soldier_1_m16_running_down_right", p2_anim_soldier_1_m16_running_down_right);
    insert(player_anim_map, "p2_anim_soldier_1_m16_spawning_side", p2_anim_soldier_1_m16_spawning_side);
    insert(player_anim_map, "p2_anim_soldier_1_m16_dying_side", p2_anim_soldier_1_m16_dying_side);

    insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_idle_side", p2_anim_soldier_1_m16_brewster_idle_side);
    insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_running_side", p2_anim_soldier_1_m16_brewster_running_side);
    insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_idle_back", p2_anim_soldier_1_m16_brewster_idle_back);
    insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_running_back", p2_anim_soldier_1_m16_brewster_running_back);
    insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_idle_front", p2_anim_soldier_1_m16_brewster_idle_front);
    insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_running_front", p2_anim_soldier_1_m16_brewster_running_front);
    insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_spawning_side", p2_anim_soldier_1_m16_brewster_spawning_side);
    insert(player_anim_map, "p2_anim_soldier_1_m16_brewster_dying_side", p2_anim_soldier_1_m16_brewster_dying_side);

    insert(player_anim_map, "p2_anim_soldier_1_m44_idle_side", p2_anim_soldier_1_m44_idle_side);
    insert(player_anim_map, "p2_anim_soldier_1_m44_running_side", p2_anim_soldier_1_m44_running_side);
    insert(player_anim_map, "p2_anim_soldier_1_m44_idle_back", p2_anim_soldier_1_m44_idle_back);
    insert(player_anim_map, "p2_anim_soldier_1_m44_running_back", p2_anim_soldier_1_m44_running_back);
    insert(player_anim_map, "p2_anim_soldier_1_m44_idle_front", p2_anim_soldier_1_m44_idle_front);
    insert(player_anim_map, "p2_anim_soldier_1_m44_running_front", p2_anim_soldier_1_m44_running_front);
    insert(player_anim_map, "p2_anim_soldier_1_m44_spawning_side", p2_anim_soldier_1_m44_spawning_side);
    insert(player_anim_map, "p2_anim_soldier_1_m44_dying_side", p2_anim_soldier_1_m44_dying_side);

    insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_idle_side", p2_anim_soldier_1_m44_brewster_idle_side);
    insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_running_side", p2_anim_soldier_1_m44_brewster_running_side);
    insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_idle_back", p2_anim_soldier_1_m44_brewster_idle_back);
    insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_running_back", p2_anim_soldier_1_m44_brewster_running_back);
    insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_idle_front", p2_anim_soldier_1_m44_brewster_idle_front);
    insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_running_front", p2_anim_soldier_1_m44_brewster_running_front);
    insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_spawning_side", p2_anim_soldier_1_m44_brewster_spawning_side);
    insert(player_anim_map, "p2_anim_soldier_1_m44_brewster_dying_side", p2_anim_soldier_1_m44_brewster_dying_side);
}

// sets up animations for players and bullets
void init_all_anims()
{
    // init placeholder anims
    render_sprite_sheet_init(&sprite_sheet_player_placeholder, "assets/question_mark.png", 36, 36);
    adef_player_placeholder = animation_definition_create(
        &sprite_sheet_player_placeholder,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_player_placeholder = animation_create(adef_player_placeholder, false);

    // init crosshairs
    render_sprite_sheet_init(&sprite_sheet_crosshair_red, "assets/crosshair_red.png", 27, 27);
    adef_crosshair_red = animation_definition_create(
        &sprite_sheet_crosshair_red,
        (f32[]){0.1, 0.1, 0.1, 0.1},
        (u8[]){0, 0, 0, 0},
        (u8[]){1, 2, 3, 4},
        4);
    anim_crosshair_red = animation_create(adef_crosshair_red, true);

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
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_1_m16_running_down_right, "assets/soldier_1_m16_idle_down_right.png", 36, 36);
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
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
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
    p1_anim_soldier_1_m16_running_down_right = animation_create(p1_adef_soldier_1_m16_running_down_right, false);
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
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_1_m16_running_down_right, "assets/soldier_1_m16_idle_down_right.png", 36, 36);
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
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
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
    p2_anim_soldier_1_m16_running_down_right = animation_create(p2_adef_soldier_1_m16_running_down_right, false);
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

    init_player_anim_hashmap();
}

// updates player statuses based on frame counter associated with each playaer
void update_player_status(Player *player)
{
    // SPAWN LOGIC
    // check if spawn delay is up
    if (player->status == PLAYER_INACTIVE && player->frames_on_status >= (player->spawn_delay * global.time.frame_rate))
    {
        // update status & reset counter
        player->status = PLAYER_SPAWNING;
        player->frames_on_status = 0;

        // reset location
        player->entity->body->aabb.position[0] = player->spawn_point[0];
        player->entity->body->aabb.position[1] = player->spawn_point[1];

        // reset health and armor
        player->armor->name = "";
        player->armor->integrity = 0;
        player->health = 100;

        // reset player anims to default (may have changed from pickups)
        if (player == player_one)
        {
            player_one->direction = RIGHT;
        }
        else
        { // player two
            player_two->direction = LEFT;
        }

        // reset weapon
        player->weapon->name = m16.name;
        player->weapon->fire_mode = m16.fire_mode;
        player->weapon->capacity = m16.capacity;
        player->weapon->current_capacity = m16.capacity;
        player->weapon->max_fire_rate = m16.max_fire_rate;
        player->weapon->damage = m16.damage;
        player->weapon->frames_since_last_shot = 0;
        player->weapon->ready_to_fire = true;

        // make player visible
        player->entity->is_active = true;
        player->entity->body->is_active = true;
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
        player->frames_on_status = 0;

        // TODO: remove this once more dying animations are added
        if (player->direction == UP)
            player->direction = RIGHT;
        if (player->direction == DOWN)
            player->direction = LEFT;

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
    // update weapon status (check if weapon is ready to fire again)
    if (!player->weapon->ready_to_fire && player->weapon->frames_since_last_shot >= ((1.0 / (player->weapon->max_fire_rate / 60.0)) * global.time.frame_rate))
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
    char *character = "soldier_1"; // player->character
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
    if (player->weapon->current_capacity > 0 && player->weapon->ready_to_fire && key_state_ready)
    {
        vec2 bullet_position = {player->entity->body->aabb.position[0], player->entity->body->aabb.position[1]};
        Animation *bullet_anim = anim_bullet_1_horizontal;
        vec2 bullet_velocity = {0, 0};

        char *bullet_anim_name;

        // shoot at crosshair if present
        if (player->crosshair)
        {
            // calculating angle
            f32 cx = player->crosshair->body->aabb.position[0];
            f32 cy = player->crosshair->body->aabb.position[1];
            f32 px = player->entity->body->aabb.position[0];
            f32 py = player->entity->body->aabb.position[1];
            f32 dx = px - cx;
            f32 dy = py - cy;
            f32 angle = (cx > px && cy > py) || (cx < px && cy < py) ? atan(dy / dx) : -1 * atan(dy / dx);

            // calculate starting position using angle
            f32 bullet_x = cx > px ? 30 * cos(angle) : 32 * cos(angle) * -1;
            f32 bullet_y = cy > py ? 30 * sin(angle) : 32 * sin(angle) * -1;
            bullet_position[0] = player->entity->body->aabb.position[0] + bullet_x;
            bullet_position[1] = player->entity->body->aabb.position[1] + bullet_y;

            // calculate velocity using angle
            f32 vx = cx > px ? player->weapon->bullet_velocity * cos(angle) : player->weapon->bullet_velocity * cos(angle) * -1;
            f32 vy = cy > py ? player->weapon->bullet_velocity * sin(angle) : player->weapon->bullet_velocity * sin(angle) * -1;
            bullet_velocity[0] = vx;
            bullet_velocity[1] = vy;

            // assign anim based on angle TODO: debug why anim number is wrong and why aiming directly downward shoots up
            if (cx < px && cy > py)
                angle += 0.5 * M_PI;
            if (cx < px && cy < py)
                angle += M_PI;
            if (cx > px && cy < py)
                angle += 1.5 * M_PI;
            if (cx < px && cy == py)
                angle = M_PI;
            if (cx == px && cy < py)
                angle = 1.5 * M_PI;
            float anim_number = floor((15 * angle) / (2 * M_PI));
            printf("%f\n", anim_number);
        }
        else // handle 8 directional shooting (player not crouched / aiming)
        {
            // calculate x/y components of position and velocity based off 45 degree angle
            const float rad_45_deg = 0.78539816;
            const float bullet_position_45_deg = 32 * sin(rad_45_deg);
            float bullet_velocity_45_deg = player->weapon->bullet_velocity * sin(rad_45_deg);
            if (player->direction == UP)
            {
                bullet_position[1] += 32;
                bullet_velocity[1] = player->weapon->bullet_velocity;
                bullet_anim_name = "bullet_4";
            }
            else if (player->direction == RIGHT)
            {
                bullet_position[0] += 32;
                bullet_velocity[0] = player->weapon->bullet_velocity;
                bullet_anim_name = "bullet_0";
            }
            else if (player->direction == DOWN)
            {
                bullet_position[1] -= 32;
                bullet_velocity[1] = -1 * player->weapon->bullet_velocity;
                bullet_anim_name = "bullet_12";
            }
            else if (player->direction == LEFT)
            {
                bullet_position[0] -= 32;
                bullet_velocity[0] = -1 * player->weapon->bullet_velocity;
                bullet_anim_name = "bullet_8";
            }
            else if (player->direction == UP_RIGHT)
            {
                bullet_position[0] += bullet_position_45_deg;
                bullet_position[1] += bullet_position_45_deg;
                bullet_velocity[0] += bullet_velocity_45_deg;
                bullet_velocity[1] += bullet_velocity_45_deg;
                bullet_anim_name = "bullet_2";
            }
            else if (player->direction == UP_LEFT)
            {
                bullet_position[0] += -1 * bullet_position_45_deg;
                bullet_position[1] += bullet_position_45_deg;
                bullet_velocity[0] += -1 * bullet_velocity_45_deg;
                bullet_velocity[1] += bullet_velocity_45_deg;
                bullet_anim_name = "bullet_6";
            }
            else if (player->direction == DOWN_RIGHT)
            {
                bullet_position[0] += bullet_position_45_deg;
                bullet_position[1] += -1 * bullet_position_45_deg;
                bullet_velocity[0] += bullet_velocity_45_deg;
                bullet_velocity[1] += -1 * bullet_velocity_45_deg;
                bullet_anim_name = "bullet_10";
            }
            else if (player->direction == DOWN_LEFT)
            {
                bullet_position[0] += -1 * bullet_position_45_deg;
                bullet_position[1] += -1 * bullet_position_45_deg;
                bullet_velocity[0] += -1 * bullet_velocity_45_deg;
                bullet_velocity[1] += -1 * bullet_velocity_45_deg;
                bullet_anim_name = "bullet_14";
            }
            else
            {
                ERROR_EXIT(NULL, "Player direction not recognized");
            }
        }
        Entity *bullet = entity_create(bullet_position, (vec2){5, 5}, (vec2){0, 0}, COLLISION_LAYER_BULLET, bullet_mask, bullet_on_hit, bullet_on_hit_static);
        bullet->animation = bullet_anim;
        bullet->body->velocity[0] = bullet_velocity[0];
        bullet->body->velocity[1] = bullet_velocity[1];

        // decrement weapon capacity
        player->weapon->current_capacity -= 1;

        if (player->weapon->fire_mode == BURST)
        {
            player->weapon->burst_shots_remaining -= 1;
        }

        // restart rpm timer
        player->weapon->ready_to_fire = false;
        player->weapon->frames_since_last_shot = 0;
    }
}

// handles key inputs of players
void handle_player_input(Player *player)
{
    if (player->status != PLAYER_ACTIVE) // don't allow inputs on inactive players
    {
        return;
    }

    Key_State left = player->is_left_player ? global.input.l_left : global.input.r_left;
    Key_State right = player->is_left_player ? global.input.l_right : global.input.r_right;
    Key_State up = player->is_left_player ? global.input.l_up : global.input.r_up;
    Key_State down = player->is_left_player ? global.input.l_down : global.input.r_down;
    Key_State shoot = player->is_left_player ? global.input.l_shoot : global.input.r_shoot;
    Key_State crouch = player->is_left_player ? global.input.l_crouch : global.input.r_crouch;

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
        // don't let players move while crouching
        player->entity->body->velocity[0] = 0;
        player->entity->body->velocity[1] = 0;

        // TODO: update player animation

        vec2 player_position = {(player->entity->body->aabb.position[0]),
                                (player->entity->body->aabb.position[1])};

        // if player doesn't already have a crosshair entity associated, create one
        if (!player->crosshair)
        {
            player->crosshair = entity_create(player_position, (vec2){27, 27}, (vec2){0, 0}, COLLISION_LAYER_CROSSHAIR, crosshair_mask, crosshair_on_hit, crosshair_on_hit_static);
            player->crosshair->animation = anim_crosshair_red;
        }

        // crosshairs not restricted to 4 directions *unlike players*
        if (left)
            velx -= 250;
        if (right)
            velx += 250;
        if (up)
            vely += 250;
        if (down)
            vely -= 250;

        player->crosshair->body->velocity[0] = velx;
        player->crosshair->body->velocity[1] = vely;

        handle_player_shooting(player, shoot);
        return;
    }

    if (player->crosshair)
    {
        entity_destroy(player->crosshair);
        player->crosshair = NULL;
    }

    // 4 directional movement only, no diagonals
    if (up && right)
    {
        player->direction = UP_RIGHT;
        velx += 106;
        vely += 106;
    }
    else if (up && left)
    {
        player->direction = UP_LEFT;
        velx -= 106;
        vely += 106;
    }
    else if (down && right)
    {
        player->direction = DOWN_RIGHT;
        velx += 106;
        vely -= 106;
    }
    else if (down && left)
    {
        player->direction = DOWN_LEFT;
        velx -= 106;
        vely -= 106;
    }
    else if (right)
    {
        player->direction = RIGHT;
        velx += 150;
    }

    else if (left)
    {
        player->direction = LEFT;
        velx -= 150;
    }

    else if (up)
    {
        player->direction = UP;
        vely += 150;
    }

    else if (down)
    {
        player->direction = DOWN;
        vely -= 150;
    }

    // handle weapon attribute updates & bullet generation, contingent on fire mode, input, and weapon shot cooldown
    handle_player_shooting(player, shoot);

    player->entity->body->velocity[0] = velx;
    player->entity->body->velocity[1] = vely;
}

// helper to get the player from a body (if associated), used in on_hit helpers
Player *get_player_from_body(Player *player_one, Player *player_two, Body *body, bool return_other_player)
{
    if (player_one->entity->body == body)
    {
        return !return_other_player ? player_one : player_two;
    }
    else if (player_two->entity->body == body)
    {
        return !return_other_player ? player_two : player_one;
    }
    else
    {
        return NULL;
    }
}