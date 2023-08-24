#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <assert.h>

// engine headers
#include "engine/global.h"
#include "engine/config.h"
#include "engine/input.h"
#include "engine/time.h"
#include "engine/physics.h"
#include "engine/util.h"
#include "engine/entity.h"
#include "engine/render.h"
#include "engine/animation.h"
#include "engine/array_list.h"

// game specific headers
#include "structs.h"
#include "collision_behavior.h"

const u8 frame_rate = 30;          // frame rate
static u32 texture_slots[8] = {0}; // texture slots array for batch rendering
static bool should_quit = false;   // quit flag

// rendering dimensions
static f32 render_width;
static f32 render_height;

// player 1 sprites & anims
Sprite_Sheet p1_sprite_sheet_soldier_idle_side;
Sprite_Sheet p1_sprite_sheet_soldier_running_side;
Sprite_Sheet p1_sprite_sheet_soldier_idle_back;
Sprite_Sheet p1_sprite_sheet_soldier_running_back;
Sprite_Sheet p1_sprite_sheet_soldier_idle_front;
Sprite_Sheet p1_sprite_sheet_soldier_running_front;
Sprite_Sheet p1_sprite_sheet_soldier_spawning_side;
Sprite_Sheet p1_sprite_sheet_soldier_dying_side;

static Animation_Definition *p1_adef_soldier_idle_side;
static Animation_Definition *p1_adef_soldier_running_side;
static Animation_Definition *p1_adef_soldier_idle_back;
static Animation_Definition *p1_adef_soldier_running_back;
static Animation_Definition *p1_adef_soldier_idle_front;
static Animation_Definition *p1_adef_soldier_running_front;
static Animation_Definition *p1_adef_soldier_spawning_side;
static Animation_Definition *p1_adef_soldier_dying_side;

static Animation *p1_anim_soldier_idle_side;
static Animation *p1_anim_soldier_running_side;
static Animation *p1_anim_soldier_idle_back;
static Animation *p1_anim_soldier_running_back;
static Animation *p1_anim_soldier_idle_front;
static Animation *p1_anim_soldier_running_front;
static Animation *p1_anim_soldier_spawning_side;
static Animation *p1_anim_soldier_dying_side;

// player 2 sprites & anims
Sprite_Sheet p2_sprite_sheet_soldier_idle_side;
Sprite_Sheet p2_sprite_sheet_soldier_running_side;
Sprite_Sheet p2_sprite_sheet_soldier_idle_back;
Sprite_Sheet p2_sprite_sheet_soldier_running_back;
Sprite_Sheet p2_sprite_sheet_soldier_idle_front;
Sprite_Sheet p2_sprite_sheet_soldier_running_front;
Sprite_Sheet p2_sprite_sheet_soldier_spawning_side;
Sprite_Sheet p2_sprite_sheet_soldier_dying_side;

static Animation_Definition *p2_adef_soldier_idle_side;
static Animation_Definition *p2_adef_soldier_running_side;
static Animation_Definition *p2_adef_soldier_idle_back;
static Animation_Definition *p2_adef_soldier_running_back;
static Animation_Definition *p2_adef_soldier_idle_front;
static Animation_Definition *p2_adef_soldier_running_front;
static Animation_Definition *p2_adef_soldier_spawning_side;
static Animation_Definition *p2_adef_soldier_dying_side;

static Animation *p2_anim_soldier_idle_side;
static Animation *p2_anim_soldier_running_side;
static Animation *p2_anim_soldier_idle_back;
static Animation *p2_anim_soldier_running_back;
static Animation *p2_anim_soldier_idle_front;
static Animation *p2_anim_soldier_running_front;
static Animation *p2_anim_soldier_spawning_side;
static Animation *p2_anim_soldier_dying_side;

// bullet sprites & anims
Sprite_Sheet sprite_sheet_bullet_1_horizontal;
Sprite_Sheet sprite_sheet_bullet_1_vertical;

static Animation_Definition *adef_bullet_1_horizontal;
static Animation_Definition *adef_bullet_1_vertical;

static Animation *anim_bullet_1_horizontal;
static Animation *anim_bullet_1_vertical;

// prop sprites & anims
Sprite_Sheet sprite_sheet_shipping_container_red;

// declare players
static Player player_one;
static Player player_two;

// init spawn points
const vec2 spawn_point_one = {100, 200};
const vec2 spawn_point_two = {550, 200};

Player *get_player_from_body(Body *body)
{
    if (player_one.entity->body == body)
    {
        return &player_one;
    }
    else if (player_two.entity->body == body)
    {
        return &player_two;
    }
    else
    {
        return NULL;
    }
}

void player_on_hit(Body *self, Body *other, Hit hit)
{
    Player *player = get_player_from_body(self);
    if (other->collision_layer == COLLISION_LAYER_BULLET && other->is_active && self->is_active)
    {
        player->health -= 50;
        other->is_active = false; // always mark bullet as inactive
    }
}
// performs render_sprite_sheet_init, animation_defintion_create, and animation_create for all sprite sheets
static void init_all_anims()
{
    // player_one stuff
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_idle_side, "assets/soldier_1_m16_idle_side.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_running_side, "assets/soldier_1_m16_running_side.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_idle_back, "assets/soldier_1_m16_idle_back.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_running_back, "assets/soldier_1_m16_running_back.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_idle_front, "assets/soldier_1_m16_idle_front.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_running_front, "assets/soldier_1_m16_running_front.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_spawning_side, "assets/soldier_1_spawning_side.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_dying_side, "assets/soldier_1_m16_dying_side.png", 42, 42);

    p1_adef_soldier_idle_side = animation_definition_create(
        &p1_sprite_sheet_soldier_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_running_side = animation_definition_create(
        &p1_sprite_sheet_soldier_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    p1_adef_soldier_idle_back = animation_definition_create(
        &p1_sprite_sheet_soldier_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_running_back = animation_definition_create(
        &p1_sprite_sheet_soldier_running_back,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    p1_adef_soldier_idle_front = animation_definition_create(
        &p1_sprite_sheet_soldier_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_running_front = animation_definition_create(
        &p1_sprite_sheet_soldier_running_front,
        (f32[]){0.04, 0.04, 0.05, 0.04, 0.04, 0.04, 0.05, 0.04},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
    p1_adef_soldier_spawning_side = animation_definition_create(
        &p1_sprite_sheet_soldier_spawning_side,
        (f32[]){0.25, 0.25},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    p1_adef_soldier_dying_side = animation_definition_create(
        &p1_sprite_sheet_soldier_dying_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.25, 0.25, 0.25, 0.25, 0.25},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);

    p1_anim_soldier_idle_side = animation_create(p1_adef_soldier_idle_side, false);
    p1_anim_soldier_running_side = animation_create(p1_adef_soldier_running_side, true);
    p1_anim_soldier_idle_back = animation_create(p1_adef_soldier_idle_back, false);
    p1_anim_soldier_running_back = animation_create(p1_adef_soldier_running_back, true);
    p1_anim_soldier_idle_front = animation_create(p1_adef_soldier_idle_front, false);
    p1_anim_soldier_running_front = animation_create(p1_adef_soldier_running_front, true);
    p1_anim_soldier_spawning_side = animation_create(p1_adef_soldier_spawning_side, true);
    p1_anim_soldier_dying_side = animation_create(p1_adef_soldier_dying_side, true);

    // player_two stuff
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_idle_side, "assets/soldier_1_m16_idle_side.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_running_side, "assets/soldier_1_m16_running_side.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_idle_back, "assets/soldier_1_m16_idle_back.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_running_back, "assets/soldier_1_m16_running_back.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_idle_front, "assets/soldier_1_m16_idle_front.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_running_front, "assets/soldier_1_m16_running_front.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_spawning_side, "assets/soldier_1_spawning_side.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_dying_side, "assets/soldier_1_m16_dying_side.png", 42, 42);

    p2_adef_soldier_idle_side = animation_definition_create(
        &p2_sprite_sheet_soldier_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_running_side = animation_definition_create(
        &p2_sprite_sheet_soldier_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    p2_adef_soldier_idle_back = animation_definition_create(
        &p2_sprite_sheet_soldier_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_running_back = animation_definition_create(
        &p2_sprite_sheet_soldier_running_back,
        (f32[]){0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    p2_adef_soldier_idle_front = animation_definition_create(
        &p2_sprite_sheet_soldier_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_running_front = animation_definition_create(
        &p2_sprite_sheet_soldier_running_front,
        (f32[]){0.02, 0.02, 0.025, 0.02, 0.02, 0.02, 0.025, 0.02},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
    p2_adef_soldier_spawning_side = animation_definition_create(
        &p2_sprite_sheet_soldier_spawning_side,
        (f32[]){0.25, 0.25},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);

    p2_adef_soldier_dying_side = animation_definition_create(
        &p2_sprite_sheet_soldier_dying_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.25, 0.25, 0.25, 0.25, 0.25},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);

    p2_anim_soldier_idle_side = animation_create(p2_adef_soldier_idle_side, false);
    p2_anim_soldier_running_side = animation_create(p2_adef_soldier_running_side, true);
    p2_anim_soldier_idle_back = animation_create(p2_adef_soldier_idle_back, false);
    p2_anim_soldier_running_back = animation_create(p2_adef_soldier_running_back, true);
    p2_anim_soldier_idle_front = animation_create(p2_adef_soldier_idle_front, false);
    p2_anim_soldier_running_front = animation_create(p2_adef_soldier_running_front, true);
    p2_anim_soldier_spawning_side = animation_create(p2_adef_soldier_spawning_side, true);
    p2_anim_soldier_dying_side = animation_create(p2_adef_soldier_dying_side, true);

    // bullet stuff
    render_sprite_sheet_init(&sprite_sheet_bullet_1_horizontal, "assets/bullet_1_horizontal.png", 5, 5);
    render_sprite_sheet_init(&sprite_sheet_bullet_1_vertical, "assets/bullet_1_vertical.png", 5, 5);
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

    // props / map stuff
    render_sprite_sheet_init(&sprite_sheet_shipping_container_red, "assets/shipping_container_red.png", 80, 130);
}

static void handle_player_shooting(Player *player)
{
    if (player->weapon->current_capacity > 0) // only generate bullet if weapon is loaded
    {
        vec2 bullet_position = {player->entity->body->aabb.position[0], player->entity->body->aabb.position[1]};
        vec2 bullet_velocity = {0, 0};
        Animation *bullet_anim = anim_bullet_1_horizontal;
        if (player->direction == UP)
        {
            bullet_position[1] += 25;
            bullet_velocity[1] = 1200;
            bullet_anim = anim_bullet_1_vertical;
        }
        else if (player->direction == RIGHT)
        {
            bullet_position[0] += 25;
            bullet_velocity[0] = 1200;
        }
        else if (player->direction == DOWN)
        {
            bullet_position[1] -= 25;
            bullet_velocity[1] = -1200;
            bullet_anim = anim_bullet_1_vertical;
        }
        else if (player->direction == LEFT)
        {
            bullet_position[0] -= 25;
            bullet_velocity[0] = -1200;
        }
        else
        {
            ERROR_EXIT(NULL, "Player direction not recognized");
        }
        Entity *bullet = entity_create(bullet_position, (vec2){5, 5}, (vec2){0, 0}, COLLISION_LAYER_BULLET, bullet_mask, bullet_on_hit, bullet_on_hit_static);
        bullet->animation = bullet_anim;
        bullet->body->velocity[0] = bullet_velocity[0];
        bullet->body->velocity[1] = bullet_velocity[1];

        // decrement weapon capacity
        player->weapon->current_capacity -= 1;
    }
}

static void input_handle_left_side(Player *player)
{
    f32 velx = 0;
    f32 vely = 0;
    if (global.input.l_right)
    {
        player->direction = RIGHT;
        velx += 150;
    }

    if (global.input.l_left)
    {
        player->direction = LEFT;
        velx -= 150;
    }

    if (global.input.l_up)
    {
        player->direction = UP;
        vely += 150;
    }

    if (global.input.l_down)
    {
        player->direction = DOWN;
        vely -= 150;
    }
    if (global.input.l_shoot == KS_PRESSED)
    {
        // handle weapon attribute updates & bullet generation
        handle_player_shooting(player);
    }
    player->entity->body->velocity[0] = velx;
    player->entity->body->velocity[1] = vely;
}

static void input_handle_right_side(Player *player)
{
    f32 velx = 0;
    f32 vely = 0;
    if (global.input.r_right)
    {
        player->direction = RIGHT;
        velx += 150;
    }

    if (global.input.r_left)
    {
        player->direction = LEFT;
        velx -= 150;
    }

    if (global.input.r_up)
    {
        player->direction = UP;
        vely += 150;
    }

    if (global.input.r_down)
    {
        player->direction = DOWN;
        vely -= 150;
    }
    if (global.input.r_shoot == KS_PRESSED)
    {
        // handle weapon attribute updates & bullet generation
        handle_player_shooting(player);
    }
    player->entity->body->velocity[0] = velx;
    player->entity->body->velocity[1] = vely;
}

// updates player animations based on direction
static void update_player_animations(Player *player)
{
    if (player->status == ACTIVE)
    {
        if (player->direction == RIGHT || player->direction == LEFT)
        {
            player->entity->animation = player->entity->body->velocity[0] != 0 ? player->animation_set->side_moving : player->animation_set->side_idle; // anim_soldier_running_side : anim_soldier_idle_side;
            player->entity->animation->is_flipped = player->direction == LEFT ? true : false;
        }
        else if (player->direction == UP)
        {
            player->entity->animation = player->entity->body->velocity[1] != 0 ? player->animation_set->up_moving : player->animation_set->up_idle; // anim_soldier_running_back : anim_soldier_idle_back;
        }
        else if (player->direction == DOWN)
        {
            player->entity->animation = player->entity->body->velocity[1] != 0 ? player->animation_set->down_moving : player->animation_set->down_idle; // anim_soldier_running_front : anim_soldier_idle_front;
        }
        else
        {
            ERROR_EXIT(-1, "Player direction not recognized");
        }
    }
    else if (player->status == SPAWNING)
    {
        player->entity->animation = player->animation_set->spawning;
    }
    else if (player->status == DESPAWNING)
    {
        player->entity->animation = player->animation_set->dying;
    }
}

// updates player statuses based on frame counter associated with each playaer
static void update_player_status(Player *player)
{
    // check if spawn delay is up
    if (player->status == INACTIVE && player->frames_on_status >= (player->spawn_delay * global.time.frame_rate))
    {
        player->status = SPAWNING;
        player->frames_on_status = 0;

        // TODO: eventually figure out anther way to figure out where spawn point should be
        // reset location
        player->entity->body->aabb.position[0] = spawn_point_one[0];
        player->entity->body->aabb.position[1] = spawn_point_one[1];

        // reset health
        player->health = 100;

        // show sprites
        player->entity->is_active = true;
        player->entity->body->is_active = true;
    }
    // check if spawn time is up
    else if (player->status == SPAWNING && player->frames_on_status >= (player->spawn_time * global.time.frame_rate))
    {
        player->status = ACTIVE;
        player->frames_on_status = 0;
    }
    // check if health is 0
    else if (player->health <= 0 && player->status == ACTIVE)
    {
        player->status = DESPAWNING;
        player->frames_on_status = 0;
    }
    // check if death animation is complete
    else if (player->status == DESPAWNING && player->frames_on_status >= (player->despawn_time * global.time.frame_rate))
    {
        player->status = INACTIVE;
        player->frames_on_status = 0;

        // hide sprites
        player->entity->is_active = false;
        player->entity->body->is_active = false;
    }
}

int main(int argc, char *argv[])
{
    time_init(frame_rate);
    config_init();
    SDL_Window *window = render_init();
    physics_init();
    entity_init();
    animation_init(); // creates animation storage
    init_all_anims(); // initializes all our animations

    // get window & render dimensions
    i32 window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    render_width = window_width / render_get_scale();
    render_height = window_height / render_get_scale();

    // init player one
    player_one.entity = entity_create(spawn_point_one, (vec2){42, 42}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static);
    player_one.animation_set = &(Animation_Set){
        .down_idle = p1_anim_soldier_idle_front,
        .down_moving = p1_anim_soldier_running_front,
        .up_idle = p1_anim_soldier_idle_back,
        .up_moving = p1_anim_soldier_running_back,
        .side_idle = p1_anim_soldier_idle_side,
        .side_moving = p1_anim_soldier_running_side,
        .spawning = p1_anim_soldier_spawning_side,
        .dying = p1_anim_soldier_dying_side};
    player_one.direction = RIGHT;
    player_one.weapon = &(Weapon){
        .name = RIFLE,
        .capacity = 30,
        .current_capacity = 30,
        .max_fire_rate = 10,
    };
    player_one.status = SPAWNING;
    player_one.despawn_time = 1.5;
    player_one.spawn_delay = 5;
    player_one.spawn_time = 2;
    player_two.frames_on_status = 0;
    player_one.health = 100;

    // init player two
    player_two.entity = entity_create(spawn_point_two, (vec2){42, 42}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static);
    player_two.animation_set = &(Animation_Set){
        .down_idle = p2_anim_soldier_idle_front,
        .down_moving = p2_anim_soldier_running_front,
        .up_idle = p2_anim_soldier_idle_back,
        .up_moving = p2_anim_soldier_running_back,
        .side_idle = p2_anim_soldier_idle_side,
        .side_moving = p2_anim_soldier_running_side,
        .spawning = p2_anim_soldier_spawning_side,
        .dying = p2_anim_soldier_dying_side};
    player_two.direction = LEFT;
    player_two.weapon = &(Weapon){
        .name = RIFLE,
        .capacity = 30,
        .current_capacity = 30,
        .max_fire_rate = 10,
    };
    player_two.status = SPAWNING;
    player_two.despawn_time = 1.5;
    player_two.spawn_delay = 5;
    player_two.spawn_time = 2;
    player_two.frames_on_status = 0;
    player_two.health = 100;

    SDL_ShowCursor(false);

    Static_Body *static_body_a = physics_static_body_create((vec2){render_width * 0.5 - 12.5, render_height - 12.5}, (vec2){render_width - 25, 25}, COLLISION_LAYER_TERRIAN);
    Static_Body *static_body_b = physics_static_body_create((vec2){render_width - 12.5, render_height * 0.5 + 12.5}, (vec2){25, render_height - 25}, COLLISION_LAYER_TERRIAN);
    Static_Body *static_body_c = physics_static_body_create((vec2){render_width * 0.5 + 12.5, 12.5}, (vec2){render_width - 25, 25}, COLLISION_LAYER_TERRIAN);
    Static_Body *static_body_d = physics_static_body_create((vec2){12.5, render_height * 0.5 - 12.5}, (vec2){25, render_height - 25}, COLLISION_LAYER_TERRIAN);
    Static_Body *static_body_e = physics_static_body_create((vec2){render_width * 0.5, render_height * 0.5}, (vec2){62.5, 62.5}, COLLISION_LAYER_TERRIAN);

    // Entity *entity_a = entity_create((vec2){200, 200}, (vec2){25, 25}, (vec2){400, 0}, COLLISION_LAYER_ENEMY, enemy_mask, enemy_on_hit, enemy_on_hit_static);
    //  Entity *entity_b = entity_create((vec2){300, 300}, (vec2){25, 25}, (vec2){400, 0}, COLLISION_LAYER_ENEMY, enemy_mask, enemy_on_hit, enemy_on_hit_static);
    // entity_a->animation = p1_anim_soldier_dying_side;
    //  entity_b->animation = anim_soldier_idle_front;

    // main loop
    while (!should_quit)
    {
        // check for game exit
        if (global.input.escape)
        {
            should_quit = true;
        }

        time_update();
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                should_quit = true;
                break;
            default:
                break;
            }
        }
        input_update(); // grab current inputs

        // handle left and right player inputs
        if (player_one.status == ACTIVE)
        {
            input_handle_left_side(&player_one);
        }
        if (player_two.status == ACTIVE)
        {
            input_handle_right_side(&player_two);
        }

        update_player_animations(&player_one);
        update_player_animations(&player_two);

        physics_update();
        animation_update(global.time.delta);
        render_begin();

        // rendering walls
        render_aabb((f32 *)static_body_a, WHITE);
        render_aabb((f32 *)static_body_b, WHITE);
        render_aabb((f32 *)static_body_c, WHITE);
        render_aabb((f32 *)static_body_d, WHITE);
        // render_aabb((f32 *)static_body_e, WHITE);

        // render map
        render_sprite_sheet_frame(&sprite_sheet_shipping_container_red, window, 0, 0, (vec2){render_width / 2.0, render_height / 2.0}, 3, false, WHITE, texture_slots);

        // rendering enemies
        // render_aabb((f32 *)(entity_a->body), WHITE);
        // render_aabb((f32 *)(entity_b->body), WHITE);

        // render animated entities, check if any are marked for deletion (not active OR body is not active)
        int num_entities = (int)entity_count();
        for (int i = num_entities - 1; i >= 0; --i) // TODO: figure out if it is better to use entity_count() directly here;
        {
            Entity *entity = entity_get(i);

            // destroy any entities that are inactive or have physics bodies that are inactive
            if (entity == NULL)
            {
                continue;
            }

            if (entity->body == NULL)
            {
                continue;
            }

            if (!entity->is_active || !entity->body->is_active)
            {
                continue;
            }

            // skip entities with no associated animations
            if (entity->animation == NULL)
            {
                continue;
            }

            // TODO: debug overlaps - order here seems to affect this
            animation_render(entity->animation, window, entity->body->aabb.position, 1, WHITE, texture_slots);
        }

        render_end(window, texture_slots);

        // update each player status
        update_player_status(&player_one);
        update_player_status(&player_two);

        // update frame counters on both players
        player_one.frames_on_status++;
        player_two.frames_on_status++;

        time_update_late();
    }

    return 0;
}
