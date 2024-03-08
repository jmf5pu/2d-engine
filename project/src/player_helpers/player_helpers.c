#include "player_helpers.h"
#include "../collision_behavior/collision_behavior.h"
#include "../engine/camera.h"
#include "../engine/global.h"
#include "../engine/util.h"
#include "../weapon_types/weapon_types.h"
#include <math.h>

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

    insert(player_anim_map, "player_mock_1", anim_player_mock_1);
    insert(player_anim_map, "player_mock_2", anim_player_mock_2);
    insert(player_anim_map, "player_mock_3", anim_player_mock_3);
    insert(player_anim_map, "player_mock_4", anim_player_mock_4);
}

// sets up animations for players and bullets
void init_all_anims()
{
    // TODO: separate player and non-player anims to separate methods
    // init placeholder anims
    render_sprite_sheet_init(&sprite_sheet_player_placeholder, "assets/question_mark.png", 36, 36);
    adef_player_placeholder = animation_definition_create(&sprite_sheet_player_placeholder, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_player_placeholder = animation_create(adef_player_placeholder, false);

    // init crosshair anims
    render_sprite_sheet_init(&sprite_sheet_player_1_crosshair, "assets/wip/crosshair_mock.png", 11, 11);
    adef_player_1_crosshair = animation_definition_create(&sprite_sheet_player_1_crosshair, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_player_2_crosshair, "assets/wip/crosshair_mock.png", 11, 11);
    adef_player_2_crosshair = animation_definition_create(&sprite_sheet_player_2_crosshair, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_p1_crosshair = animation_create(adef_player_1_crosshair, false);
    anim_p2_crosshair = animation_create(adef_player_2_crosshair, false);

    // init bullet anims
    render_sprite_sheet_init(&sprite_sheet_bullet_0, "assets/bullet_0.png", 3, 1);
    adef_bullet_0 = animation_definition_create(&sprite_sheet_bullet_0, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_0 = animation_create(adef_bullet_0, false);
    render_sprite_sheet_init(&sprite_sheet_bullet_1, "assets/bullet_1.png", 3, 2);
    adef_bullet_1 = animation_definition_create(&sprite_sheet_bullet_1, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_1 = animation_create(adef_bullet_1, false);
    render_sprite_sheet_init(&sprite_sheet_bullet_2, "assets/bullet_2.png", 3, 3);
    adef_bullet_2 = animation_definition_create(&sprite_sheet_bullet_2, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_2 = animation_create(adef_bullet_2, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_3, "assets/bullet_3.png", 2, 3);
    adef_bullet_3 = animation_definition_create(&sprite_sheet_bullet_3, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_3 = animation_create(adef_bullet_3, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_4, "assets/bullet_4.png", 1, 3);
    adef_bullet_4 = animation_definition_create(&sprite_sheet_bullet_4, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_4 = animation_create(adef_bullet_4, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_5, "assets/bullet_5.png", 2, 3);
    adef_bullet_5 = animation_definition_create(&sprite_sheet_bullet_5, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_5 = animation_create(adef_bullet_5, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_6, "assets/bullet_6.png", 3, 3);
    adef_bullet_6 = animation_definition_create(&sprite_sheet_bullet_6, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_6 = animation_create(adef_bullet_6, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_7, "assets/bullet_7.png", 3, 2);
    adef_bullet_7 = animation_definition_create(&sprite_sheet_bullet_7, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_7 = animation_create(adef_bullet_7, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_8, "assets/bullet_8.png", 3, 1);
    adef_bullet_8 = animation_definition_create(&sprite_sheet_bullet_8, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_8 = animation_create(adef_bullet_8, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_9, "assets/bullet_9.png", 3, 2);
    adef_bullet_9 = animation_definition_create(&sprite_sheet_bullet_9, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_9 = animation_create(adef_bullet_9, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_10, "assets/bullet_10.png", 3, 3);
    adef_bullet_10 = animation_definition_create(&sprite_sheet_bullet_10, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_10 = animation_create(adef_bullet_10, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_11, "assets/bullet_11.png", 2, 3);
    adef_bullet_11 = animation_definition_create(&sprite_sheet_bullet_11, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_11 = animation_create(adef_bullet_11, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_12, "assets/bullet_12.png", 1, 3);
    adef_bullet_12 = animation_definition_create(&sprite_sheet_bullet_12, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_12 = animation_create(adef_bullet_12, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_13, "assets/bullet_13.png", 2, 3);
    adef_bullet_13 = animation_definition_create(&sprite_sheet_bullet_13, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_13 = animation_create(adef_bullet_13, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_14, "assets/bullet_14.png", 3, 3);
    adef_bullet_14 = animation_definition_create(&sprite_sheet_bullet_14, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_14 = animation_create(adef_bullet_14, false);

    render_sprite_sheet_init(&sprite_sheet_bullet_15, "assets/bullet_15.png", 3, 2);
    adef_bullet_15 = animation_definition_create(&sprite_sheet_bullet_15, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_bullet_15 = animation_create(adef_bullet_15, false);

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

    init_bullet_anim_hashmap();
    init_player_anim_hashmap();
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
void update_player_animations(Player *player)
{
    // cache old anim to check if we are SWITCHING anims
    Animation *prev_anim = player->entity->animation;

    char *anim_name = calloc(50, sizeof(char));
    strcat(anim_name, "player_mock_");

    char *direction;

    // choose correct animation for player's direction
    f32 crosshair_angle = atan2(
        player->crosshair->body->aabb.position[1] - player->entity->body->aabb.position[1], player->crosshair->body->aabb.position[0] - player->entity->body->aabb.position[0]);
    if (crosshair_angle > -1 * M_PI / 4 && crosshair_angle <= M_PI / 4) {
        direction = "1";
    }
    else if (crosshair_angle > M_PI / 4 && crosshair_angle <= 3 * M_PI / 4) {
        direction = "2";
    }
    else if (crosshair_angle > 3 * M_PI / 4 || crosshair_angle <= -3 * M_PI / 4) {
        direction = "3";
    }
    else if (crosshair_angle > -3 * M_PI / 4 && crosshair_angle < -1 * M_PI / 4) {
        direction = "4";
    }
    else {
        printf("got unexpected crosshair angle: %f\n", crosshair_angle);
    }
    strcat(anim_name, direction);
    strcat(anim_name, "\0");

    Animation *player_anim = get(player_anim_map, anim_name);
    if (player_anim)
        player->entity->animation = player_anim;
    else
        player->entity->animation = anim_player_placeholder;

    // ensure we are starting new anims at the first frame
    if (player->entity->animation != prev_anim)
        player->entity->animation->current_frame_index = 0;

    free(anim_name);
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
        f32 cx = 0;
        f32 cy = 0;
        f32 px = player->entity->body->aabb.position[0];
        f32 py = player->entity->body->aabb.position[1];
        vec2 bullet_position = {px, py};
        vec2 bullet_velocity = {0, 0};

        // shoot bullet at crosshair
        cx = player->crosshair->body->aabb.position[0];
        cy = player->crosshair->body->aabb.position[1];

        // since the player's position is relative to the glviewport, while the crosshair's is to the window
        if (player == player_two)
            cx -= 0.5 * window_width;

        // Calculate angle using atan2
        f32 dx = cx - px;
        f32 dy = cy - py;
        f32 angle = atan2(dy, dx);

        // Calculate bullet starting position using angle
        f32 bullet_x = BULLET_DISTANCE_FROM_PLAYER * cos(angle);
        f32 bullet_y = BULLET_DISTANCE_FROM_PLAYER * sin(angle);

        // Calculate starting position using angle
        bullet_position[0] = player->relative_position[0] + bullet_x;
        bullet_position[1] = player->relative_position[1] + bullet_y;

        // Calculate velocity using angle
        f32 vx = player->weapon->bullet_velocity * cos(angle);
        f32 vy = player->weapon->bullet_velocity * sin(angle);
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
        if (angle >= 6.1 || angle < 0.2) {
            bullet_anim_name = "bullet_0";
        }
        else if (angle >= 0.2 && angle < 0.59) {
            bullet_anim_name = "bullet_1";
        }
        else if (angle >= 0.59 && angle < 0.983) {
            bullet_anim_name = "bullet_2";
        }
        else if (angle >= 0.983 && angle < 1.375) {
            bullet_anim_name = "bullet_3";
        }
        else if (angle >= 1.375 && angle < 1.769) {
            bullet_anim_name = "bullet_4";
        }
        else if (angle >= 1.769 && angle < 2.163) {
            bullet_anim_name = "bullet_5";
        }
        else if (angle >= 2.163 && angle < 2.557) {
            bullet_anim_name = "bullet_6";
        }
        else if (angle >= 2.557 && angle < 2.95) {
            bullet_anim_name = "bullet_7";
        }
        else if (angle >= 2.95 && angle < 3.344) {
            bullet_anim_name = "bullet_8";
        }
        else if (angle >= 3.344 && angle < 3.738) {
            bullet_anim_name = "bullet_9";
        }
        else if (angle >= 3.738 && angle < 4.131) {
            bullet_anim_name = "bullet_10";
        }
        else if (angle >= 4.131 && angle < 4.525) {
            bullet_anim_name = "bullet_11";
        }
        else if (angle >= 4.525 && angle < 4.919) {
            bullet_anim_name = "bullet_12";
        }
        else if (angle >= 4.919 && angle < 5.313) {
            bullet_anim_name = "bullet_13";
        }
        else if (angle >= 5.313 && angle < 5.706) {
            bullet_anim_name = "bullet_14";
        }
        else if (angle >= 5.706 && angle < 6.1) {
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

        if (player->weapon->fire_mode == BURST) {
            player->weapon->burst_shots_remaining -= 1;
        }

        // restart rounds per minute timer
        player->weapon->ready_to_fire = false;
        player->weapon->frames_since_last_shot = 0;
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
    free(player->crosshair);
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

// parent function for all the necessary player updates made each frame
void player_per_frame_updates(Player *player)
{
    handle_player_input(player);
    update_player_status(player);
    if (player->status != PLAYER_INACTIVE)
        update_player_animations(player);
}