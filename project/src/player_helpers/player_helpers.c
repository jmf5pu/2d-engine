#include "player_helpers.h"
#include "../collision_behavior/collision_behavior.h"
#include "../effects/effects.h"
#include "../engine/camera.h"
#include "../engine/global.h"
#include "../engine/util.h"
#include "../main_helpers/main_helpers.h"
#include "../weapon_types/weapon_types.h"
#include <math.h>

// declare players
Player *player_one;
Player *player_two;

// animation hash maps
static Hash_Map *bullet_adef_map;
static Hash_Map *player_anim_map;
static Hash_Map *weapon_anim_map;
static Hash_Map *explosion_adef_map;

void init_explosion_animation_definitions(void)
{
    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_0, "assets/wip/muzzle_flash_v3_0.png", 19, 19);
    adef_muzzle_flash_0 =
        animation_definition_create(&sprite_sheet_muzzle_flash_0, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_1, "assets/wip/muzzle_flash_v3_1.png", 19, 19);
    adef_muzzle_flash_1 =
        animation_definition_create(&sprite_sheet_muzzle_flash_1, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_2, "assets/wip/muzzle_flash_v3_2.png", 19, 19);
    adef_muzzle_flash_2 =
        animation_definition_create(&sprite_sheet_muzzle_flash_2, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_3, "assets/wip/muzzle_flash_v3_3.png", 19, 19);
    adef_muzzle_flash_3 =
        animation_definition_create(&sprite_sheet_muzzle_flash_3, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_4, "assets/wip/muzzle_flash_v3_4.png", 19, 19);
    adef_muzzle_flash_4 =
        animation_definition_create(&sprite_sheet_muzzle_flash_4, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_5, "assets/wip/muzzle_flash_v3_5.png", 19, 19);
    adef_muzzle_flash_5 =
        animation_definition_create(&sprite_sheet_muzzle_flash_5, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_6, "assets/wip/muzzle_flash_v3_6.png", 19, 19);
    adef_muzzle_flash_6 =
        animation_definition_create(&sprite_sheet_muzzle_flash_6, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_7, "assets/wip/muzzle_flash_v3_7.png", 19, 19);
    adef_muzzle_flash_7 =
        animation_definition_create(&sprite_sheet_muzzle_flash_7, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_8, "assets/wip/muzzle_flash_v3_8.png", 19, 19);
    adef_muzzle_flash_8 =
        animation_definition_create(&sprite_sheet_muzzle_flash_8, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_9, "assets/wip/muzzle_flash_v3_9.png", 19, 19);
    adef_muzzle_flash_9 =
        animation_definition_create(&sprite_sheet_muzzle_flash_9, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_10, "assets/wip/muzzle_flash_v3_10.png", 19, 19);
    adef_muzzle_flash_10 =
        animation_definition_create(&sprite_sheet_muzzle_flash_10, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_11, "assets/wip/muzzle_flash_v3_11.png", 19, 19);
    adef_muzzle_flash_11 =
        animation_definition_create(&sprite_sheet_muzzle_flash_11, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_12, "assets/wip/muzzle_flash_v3_12.png", 19, 19);
    adef_muzzle_flash_12 =
        animation_definition_create(&sprite_sheet_muzzle_flash_12, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_13, "assets/wip/muzzle_flash_v3_13.png", 19, 19);
    adef_muzzle_flash_13 =
        animation_definition_create(&sprite_sheet_muzzle_flash_13, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_14, "assets/wip/muzzle_flash_v3_14.png", 19, 19);
    adef_muzzle_flash_14 =
        animation_definition_create(&sprite_sheet_muzzle_flash_14, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);

    render_sprite_sheet_init(&sprite_sheet_muzzle_flash_15, "assets/wip/muzzle_flash_v3_15.png", 19, 19);
    adef_muzzle_flash_15 =
        animation_definition_create(&sprite_sheet_muzzle_flash_15, (f32[]){0.005, 0.005, 0.005, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
}

// init bullet animation hash_map
void init_bullet_adef_hashmap()
{
    bullet_adef_map = create_hash_map(BULLET_ADEF_COUNT);
    insert(bullet_adef_map, "bullet_0", adef_bullet_0);
}

// init player animation hash_map
void init_player_anim_hashmap()
{
    player_anim_map = create_hash_map(PLAYER_ANIM_COUNT);

    insert(player_anim_map, "player_mock_1", anim_player_mock_1);
    insert(player_anim_map, "player_mock_2", anim_player_mock_2);
    insert(player_anim_map, "player_mock_3", anim_player_mock_3);
    insert(player_anim_map, "player_mock_4", anim_player_mock_4);
}

void init_weapon_anim_hashmap()
{
    weapon_anim_map = create_hash_map(WEAPON_COUNT * ANGLES);

    insert(weapon_anim_map, "m16_with_hands_0", anim_m16_with_hands0);
    insert(weapon_anim_map, "m16_with_hands_1", anim_m16_with_hands1);
    insert(weapon_anim_map, "m16_with_hands_2", anim_m16_with_hands2);
    insert(weapon_anim_map, "m16_with_hands_3", anim_m16_with_hands3);
    insert(weapon_anim_map, "m16_with_hands_4", anim_m16_with_hands4);
    insert(weapon_anim_map, "m16_with_hands_5", anim_m16_with_hands5);
    insert(weapon_anim_map, "m16_with_hands_6", anim_m16_with_hands6);
    insert(weapon_anim_map, "m16_with_hands_7", anim_m16_with_hands7);
    insert(weapon_anim_map, "m16_with_hands_8", anim_m16_with_hands8);
    insert(weapon_anim_map, "m16_with_hands_9", anim_m16_with_hands9);
    insert(weapon_anim_map, "m16_with_hands_10", anim_m16_with_hands10);
    insert(weapon_anim_map, "m16_with_hands_11", anim_m16_with_hands11);
    insert(weapon_anim_map, "m16_with_hands_12", anim_m16_with_hands12);
    insert(weapon_anim_map, "m16_with_hands_13", anim_m16_with_hands13);
    insert(weapon_anim_map, "m16_with_hands_14", anim_m16_with_hands14);
    insert(weapon_anim_map, "m16_with_hands_15", anim_m16_with_hands15);
}

void init_explosion_adef_hashmap()
{
    explosion_adef_map = create_hash_map(EXPLOSION_COUNT * ANGLES);

    insert(explosion_adef_map, "muzzle_flash_1_0", adef_muzzle_flash_0);
    insert(explosion_adef_map, "muzzle_flash_1_1", adef_muzzle_flash_1);
    insert(explosion_adef_map, "muzzle_flash_1_2", adef_muzzle_flash_2);
    insert(explosion_adef_map, "muzzle_flash_1_3", adef_muzzle_flash_3);
    insert(explosion_adef_map, "muzzle_flash_1_4", adef_muzzle_flash_4);
    insert(explosion_adef_map, "muzzle_flash_1_5", adef_muzzle_flash_5);
    insert(explosion_adef_map, "muzzle_flash_1_6", adef_muzzle_flash_6);
    insert(explosion_adef_map, "muzzle_flash_1_7", adef_muzzle_flash_7);
    insert(explosion_adef_map, "muzzle_flash_1_8", adef_muzzle_flash_8);
    insert(explosion_adef_map, "muzzle_flash_1_9", adef_muzzle_flash_9);
    insert(explosion_adef_map, "muzzle_flash_1_10", adef_muzzle_flash_10);
    insert(explosion_adef_map, "muzzle_flash_1_11", adef_muzzle_flash_11);
    insert(explosion_adef_map, "muzzle_flash_1_12", adef_muzzle_flash_12);
    insert(explosion_adef_map, "muzzle_flash_1_13", adef_muzzle_flash_13);
    insert(explosion_adef_map, "muzzle_flash_1_14", adef_muzzle_flash_14);
    insert(explosion_adef_map, "muzzle_flash_1_15", adef_muzzle_flash_15);
}

// sets up animations for players and bullets
void init_all_anims()
{
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

    // init bullet anims
    render_sprite_sheet_init(&sprite_sheet_bullet_0, "assets/wip/bullet_v2.png", 4, 4);
    adef_bullet_0 = animation_definition_create(&sprite_sheet_bullet_0, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);

    // NEW PLAYER ANIMS 3/4/24:
    render_sprite_sheet_init(&sprite_sheet_player_mock_1, "assets/wip/player_mock_1.png", 20, 22);
    adef_player_mock_1 = animation_definition_create(&sprite_sheet_player_mock_1, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_player_mock_1 = animation_create(adef_player_mock_1, false);
    render_sprite_sheet_init(&sprite_sheet_player_mock_2, "assets/wip/player_mock_2.png", 20, 22);
    adef_player_mock_2 = animation_definition_create(&sprite_sheet_player_mock_2, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_player_mock_2 = animation_create(adef_player_mock_2, false);
    render_sprite_sheet_init(&sprite_sheet_player_mock_3, "assets/wip/player_mock_3.png", 20, 22);
    adef_player_mock_3 = animation_definition_create(&sprite_sheet_player_mock_3, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_player_mock_3 = animation_create(adef_player_mock_3, false);
    render_sprite_sheet_init(&sprite_sheet_player_mock_4, "assets/wip/player_mock_4.png", 20, 22);
    adef_player_mock_4 = animation_definition_create(&sprite_sheet_player_mock_4, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_player_mock_4 = animation_create(adef_player_mock_4, false);
    // END NEW PLAYER ANIMS

    // NEW WEAPON ANIMS 3/8/24:
    render_sprite_sheet_init(&sprite_sheet_m16_with_hands0, "assets/wip/m16_360_with_hands0.png", 25, 25);
    adef_m16_with_hands0 = animation_definition_create(&sprite_sheet_m16_with_hands0, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands0 = animation_create(adef_m16_with_hands0, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands1, "assets/wip/m16_360_with_hands1.png", 25, 25);
    adef_m16_with_hands1 = animation_definition_create(&sprite_sheet_m16_with_hands1, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands1 = animation_create(adef_m16_with_hands1, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands2, "assets/wip/m16_360_with_hands2.png", 25, 25);
    adef_m16_with_hands2 = animation_definition_create(&sprite_sheet_m16_with_hands2, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands2 = animation_create(adef_m16_with_hands2, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands3, "assets/wip/m16_360_with_hands3.png", 25, 25);
    adef_m16_with_hands3 = animation_definition_create(&sprite_sheet_m16_with_hands3, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands3 = animation_create(adef_m16_with_hands3, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands4, "assets/wip/m16_360_with_hands4.png", 25, 25);
    adef_m16_with_hands4 = animation_definition_create(&sprite_sheet_m16_with_hands4, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands4 = animation_create(adef_m16_with_hands4, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands5, "assets/wip/m16_360_with_hands5.png", 25, 25);
    adef_m16_with_hands5 = animation_definition_create(&sprite_sheet_m16_with_hands5, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands5 = animation_create(adef_m16_with_hands5, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands6, "assets/wip/m16_360_with_hands6.png", 25, 25);
    adef_m16_with_hands6 = animation_definition_create(&sprite_sheet_m16_with_hands6, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands6 = animation_create(adef_m16_with_hands6, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands7, "assets/wip/m16_360_with_hands7.png", 25, 25);
    adef_m16_with_hands7 = animation_definition_create(&sprite_sheet_m16_with_hands7, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands7 = animation_create(adef_m16_with_hands7, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands8, "assets/wip/m16_360_with_hands8.png", 25, 25);
    adef_m16_with_hands8 = animation_definition_create(&sprite_sheet_m16_with_hands8, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands8 = animation_create(adef_m16_with_hands8, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands9, "assets/wip/m16_360_with_hands9.png", 25, 25);
    adef_m16_with_hands9 = animation_definition_create(&sprite_sheet_m16_with_hands9, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands9 = animation_create(adef_m16_with_hands9, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands10, "assets/wip/m16_360_with_hands10.png", 25, 25);
    adef_m16_with_hands10 = animation_definition_create(&sprite_sheet_m16_with_hands10, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands10 = animation_create(adef_m16_with_hands10, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands11, "assets/wip/m16_360_with_hands11.png", 25, 25);
    adef_m16_with_hands11 = animation_definition_create(&sprite_sheet_m16_with_hands11, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands11 = animation_create(adef_m16_with_hands11, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands12, "assets/wip/m16_360_with_hands12.png", 25, 25);
    adef_m16_with_hands12 = animation_definition_create(&sprite_sheet_m16_with_hands12, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands12 = animation_create(adef_m16_with_hands12, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands13, "assets/wip/m16_360_with_hands13.png", 25, 25);
    adef_m16_with_hands13 = animation_definition_create(&sprite_sheet_m16_with_hands13, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands13 = animation_create(adef_m16_with_hands13, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands14, "assets/wip/m16_360_with_hands14.png", 25, 25);
    adef_m16_with_hands14 = animation_definition_create(&sprite_sheet_m16_with_hands14, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands14 = animation_create(adef_m16_with_hands14, false);

    render_sprite_sheet_init(&sprite_sheet_m16_with_hands15, "assets/wip/m16_360_with_hands15.png", 25, 25);
    adef_m16_with_hands15 = animation_definition_create(&sprite_sheet_m16_with_hands15, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_m16_with_hands15 = animation_create(adef_m16_with_hands15, false);
    // END NEW WEAPON ANIMS

    init_explosion_animation_definitions();

    init_bullet_adef_hashmap();
    init_player_anim_hashmap();
    init_weapon_anim_hashmap();
    init_explosion_adef_hashmap();
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

// initializes the player struct
void init_player(Player *player, Map *map, Weapon_Type *starting_weapon, f32 despawn_time, f32 spawn_delay, f32 spawn_time, bool is_left_player)
{
    player->entity =
        entity_create((vec2){render_width * 0.5, render_height * 0.5}, (vec2){40, 75}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static);
    player->entity->body->parent = player;
    player->crosshair = malloc(sizeof(Entity));
    player->crosshair = entity_create(
        (vec2){player->entity->body->aabb.position[0] + 150, player->entity->body->aabb.position[1] + 150},
        (vec2){CROSSHAIR_SIZE, CROSSHAIR_SIZE},
        (vec2){0, 0},
        COLLISION_LAYER_CROSSHAIR,
        crosshair_mask,
        crosshair_on_hit,
        crosshair_on_hit_static);
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
    player->weapon->burst_delay = starting_weapon->burst_delay;
    player->weapon->frames_since_last_shot = 0;
    player->weapon->ready_to_fire = true;
    player->weapon->hud_ammo_icon = starting_weapon->hud_ammo_icon;
    // TODO: initialize weapon's character_anim

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
    vec2_dup(weapon_position, player->entity->body->aabb.position);
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

static void update_player_character_anim(Player *player)
{
    // cache old anim to check if we are SWITCHING anims
    Animation *prev_anim = player->entity->animation;

    char *anim_name = calloc(50, sizeof(char));
    strcat(anim_name, "player_mock_");

    char *direction;

    // choose correct animation for player's direction
    if (player->crosshair_angle > -1 * M_PI / 4 && player->crosshair_angle <= M_PI / 4) {
        direction = "1";
    }
    else if (player->crosshair_angle > M_PI / 4 && player->crosshair_angle <= 3 * M_PI / 4) {
        direction = "2";
    }
    else if (player->crosshair_angle > 3 * M_PI / 4 || player->crosshair_angle <= -3 * M_PI / 4) {
        direction = "3";
    }
    else if (player->crosshair_angle > -3 * M_PI / 4 && player->crosshair_angle < -1 * M_PI / 4) {
        direction = "4";
    }
    else {
        printf("got unexpected crosshair angle: %f\n", player->crosshair_angle);
    }
    strcat(anim_name, direction);
    strcat(anim_name, "\0");

    Animation *player_anim = get(player_anim_map, anim_name);
    if (player_anim)
        player->entity->animation = player_anim;
    else
        player->entity->animation = missing_anim_placeholder;

    // ensure we are starting new anims at the first frame
    if (player->entity->animation != prev_anim)
        player->entity->animation->current_frame_index = 0;

    free(anim_name);
}

static void update_player_weapon_anim(Player *player)
{
    // cache old anim to check if we are SWITCHING anims
    Animation *prev_anim = player->weapon->character_anim;

    char *anim_name = calloc(50, sizeof(char));
    strcat(anim_name, "m16_with_hands_");

    char *direction = calloc(5, sizeof(char));

    get_direction_from_angle(player->crosshair_angle, direction);

    strcat(anim_name, direction);
    strcat(anim_name, "\0");

    Animation *weapon_character_anim = get(weapon_anim_map, anim_name);
    free(direction);
    free(anim_name);

    if (weapon_character_anim)
        player->weapon->character_anim = weapon_character_anim;
    else
        player->weapon->character_anim = missing_anim_placeholder;

    // ensure we are starting new anims at the first frame
    if (player->weapon->character_anim != prev_anim)
        player->weapon->character_anim->current_frame_index = 0;
}

static void update_player_crosshair_angle(Player *player)
{
    player->crosshair_angle = atan2(
        player->crosshair->body->aabb.position[1] - player->entity->body->aabb.position[1], player->crosshair->body->aabb.position[0] - player->entity->body->aabb.position[0]);
}

void create_muzzle_flash_entity(f32 angle, vec2 position, vec2 size, u8 collision_layer, u8 collision_mask, On_Hit on_hit, On_Hit_Static on_hit_static)
{
    Entity *entity = entity_create(position, size, (vec2){0, 0}, collision_layer, collision_mask, on_hit, on_hit_static);

    char *adef_key = calloc(50, sizeof(char));
    strcat(adef_key, "muzzle_flash_1_");

    char *direction = calloc(5, sizeof(char));

    get_direction_from_angle(angle, direction);

    strcat(adef_key, direction);
    strcat(adef_key, "\0");
    free(direction);

    Animation_Definition *adef = get(explosion_adef_map, adef_key);
    free(adef_key);

    entity->animation = animation_create(adef, false);
    entity->destroy_on_anim_completion = true;
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
        vec2 bullet_position = {player->relative_position[0], player->relative_position[1]};
        vec2 bullet_velocity = {0, 0};

        // since the player's position is relative to the glviewport, while the crosshair's is to the window TODO: may need to readd this logic (3/12/24)

        // Calculate starting position using angle
        vec2 bullet_start_offset = {0, 0};
        get_xy_components_from_vector(BULLET_DISTANCE_FROM_PLAYER, player->crosshair_angle, bullet_start_offset);
        vec2_add(bullet_position, bullet_position, bullet_start_offset);

        // Calculate velocity using angle
        get_xy_components_from_vector(player->weapon->bullet_velocity, player->crosshair_angle, bullet_velocity);

        // check which of 16 buckets it falls into, assign animation
        char *bullet_adef_name;
        bullet_adef_name = "bullet_0";

        // create bullet struct and calculated anim and velocity
        Bullet *bullet = malloc(sizeof(Bullet));
        bullet->entity = entity_create(bullet_position, (vec2){5, 5}, (vec2){0, 0}, COLLISION_LAYER_BULLET, bullet_mask, bullet_on_hit, bullet_on_hit_static);
        bullet->damage = player->weapon->damage;
        bullet->entity->animation = animation_create(get(bullet_adef_map, bullet_adef_name), false);

        vec2_dup(bullet->entity->body->velocity, bullet_velocity);
        bullet->entity->body->parent = bullet;

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
        vec2_add(muzzle_flash_position, player->relative_position, muzzle_flash_offset);
        create_muzzle_flash_entity(player->crosshair_angle, muzzle_flash_position, (vec2){15, 15}, 0, 0, NULL, NULL);

        // ccalculate brass offset from the player and create brass effect entity
        vec2 brass_position = {0, 0};
        vec2_dup(brass_position, player->relative_position);
        vec2 brass_offset = {0, 0};
        get_xy_components_from_vector(BRASS_EJECT_DISTANCE_FROM_PLAYER, player->crosshair_angle, brass_offset);
        vec2_add(brass_position, brass_position, brass_offset);
        create_brass_entity(brass_position, adef_brass_falling_1);
    }
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