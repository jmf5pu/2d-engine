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

static u32 texture_slots[8] = {0};
static bool should_quit = false;

Sprite_Sheet sprite_sheet_soldier_idle_side;
Sprite_Sheet sprite_sheet_soldier_running_side;
Sprite_Sheet sprite_sheet_soldier_idle_back;
Sprite_Sheet sprite_sheet_soldier_idle_front;
Sprite_Sheet sprite_sheet_soldier_running_front;
Sprite_Sheet sprite_sheet_bullet_1_horizontal;
Sprite_Sheet sprite_sheet_bullet_1_vertical;

static Animation_Definition *adef_soldier_idle_side;
static Animation_Definition *adef_soldier_running_side;
static Animation_Definition *adef_soldier_idle_back;
static Animation_Definition *adef_soldier_idle_front;
static Animation_Definition *adef_soldier_running_front;
static Animation_Definition *adef_bullet_1_horizontal;
static Animation_Definition *adef_bullet_1_vertical;

static Animation *anim_soldier_idle_side;
static Animation *anim_soldier_running_side;
static Animation *anim_soldier_idle_back;
static Animation *anim_soldier_idle_front;
static Animation *anim_soldier_running_front;
static Animation *anim_bullet_1_horizontal;
static Animation *anim_bullet_1_vertical;

// performs render_sprite_sheet_init, animation_defintion_create, and animation_create for all sprite sheets
static void init_all_anims()
{
    render_sprite_sheet_init(&sprite_sheet_soldier_idle_side, "assets/soldier_1_m16_idle_side.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_soldier_running_side, "assets/soldier_1_m16_running_side.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_soldier_idle_back, "assets/soldier_1_m16_idle_back.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_soldier_idle_front, "assets/soldier_1_m16_idle_front.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_soldier_running_front, "assets/soldier_1_m16_running_front.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_bullet_1_horizontal, "assets/bullet_1_horizontal.png", 5, 5);
    render_sprite_sheet_init(&sprite_sheet_bullet_1_vertical, "assets/bullet_1_vertical.png", 5, 5);

    adef_soldier_idle_side = animation_definition_create(
        &sprite_sheet_soldier_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    adef_soldier_running_side = animation_definition_create(
        &sprite_sheet_soldier_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    adef_soldier_idle_back = animation_definition_create(
        &sprite_sheet_soldier_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    adef_soldier_idle_front = animation_definition_create(
        &sprite_sheet_soldier_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    adef_soldier_running_front = animation_definition_create(
        &sprite_sheet_soldier_running_front,
        (f32[]){0.04, 0.04, 0.05, 0.04, 0.04, 0.04, 0.05, 0.04},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
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

    anim_soldier_idle_side = animation_create(adef_soldier_idle_side, false);
    anim_soldier_running_side = animation_create(adef_soldier_running_side, true);
    anim_soldier_idle_back = animation_create(adef_soldier_idle_back, false);
    anim_soldier_idle_front = animation_create(adef_soldier_idle_front, false);
    anim_soldier_running_front = animation_create(adef_soldier_running_front, true);
    anim_bullet_1_horizontal = animation_create(adef_bullet_1_horizontal, false);
    anim_bullet_1_vertical = animation_create(adef_bullet_1_vertical, false);
}

handle_player_shooting(Player *player)
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
    if (global.input.escape)
    {
        should_quit = true;
    }
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
    if (player->direction == RIGHT || player->direction == LEFT)
    {
        player->entity->animation = player->entity->body->velocity[0] != 0 ? anim_soldier_running_side : anim_soldier_idle_side;
        player->entity->animation->is_flipped = player->direction == LEFT ? true : false;
    }
    else if (player->direction == UP)
    {
        player->entity->animation = anim_soldier_idle_back;
    }
    else if (player->direction == DOWN)
    {
        player->entity->animation = player->entity->body->velocity[1] != 0 ? anim_soldier_running_front : anim_soldier_idle_front;
    }
    else
    {
        ERROR_EXIT(-1, "Player direction not recognized");
    }
}

int main(int argc, char *argv[])
{
    time_init(30);
    config_init();
    SDL_Window *window = render_init();
    physics_init();
    entity_init();
    animation_init(); // creates animation storage
    init_all_anims(); // initiatilizes all our animations

    SDL_ShowCursor(false);

    i32 window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    f32 width = window_width / render_get_scale();
    f32 height = window_height / render_get_scale();

    Static_Body *static_body_a = physics_static_body_create((vec2){width * 0.5 - 12.5, height - 12.5}, (vec2){width - 25, 25}, COLLISION_LAYER_TERRIAN);
    Static_Body *static_body_b = physics_static_body_create((vec2){width - 12.5, height * 0.5 + 12.5}, (vec2){25, height - 25}, COLLISION_LAYER_TERRIAN);
    Static_Body *static_body_c = physics_static_body_create((vec2){width * 0.5 + 12.5, 12.5}, (vec2){width - 25, 25}, COLLISION_LAYER_TERRIAN);
    Static_Body *static_body_d = physics_static_body_create((vec2){12.5, height * 0.5 - 12.5}, (vec2){25, height - 25}, COLLISION_LAYER_TERRIAN);
    Static_Body *static_body_e = physics_static_body_create((vec2){width * 0.5, height * 0.5}, (vec2){62.5, 62.5}, COLLISION_LAYER_TERRIAN);

    Entity *entity_a = entity_create((vec2){200, 200}, (vec2){25, 25}, (vec2){400, 0}, COLLISION_LAYER_ENEMY, enemy_mask, enemy_on_hit, enemy_on_hit_static);
    // Entity *entity_b = entity_create((vec2){300, 300}, (vec2){25, 25}, (vec2){400, 0}, COLLISION_LAYER_ENEMY, enemy_mask, enemy_on_hit, enemy_on_hit_static);
    entity_a->animation = anim_soldier_idle_side;
    // entity_b->animation = anim_soldier_idle_front;

    // init players
    Player player_one = {
        .entity = entity_create((vec2){100, 200}, (vec2){42, 42}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static),
        .direction = RIGHT,
        .weapon = &(Weapon){
            .name = RIFLE,
            .capacity = 30,
            .current_capacity = 30,
            .max_fire_rate = 10,
        },
        .health = 100};

    Player player_two = {
        .entity = entity_create((vec2){100, 200}, (vec2){42, 42}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static),
        .direction = LEFT,
        .weapon = &(Weapon){
            .name = RIFLE,
            .capacity = 30,
            .current_capacity = 30,
            .max_fire_rate = 10,
        },
        .health = 100};

    // main loop
    while (!should_quit)
    {
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

        input_update();

        // handle left and right player inputs
        input_handle_right_side(&player_two);
        input_handle_left_side(&player_one);

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
        render_aabb((f32 *)static_body_e, WHITE);

        // rendering enemies
        // render_aabb((f32 *)(entity_a->body), WHITE);
        // render_aabb((f32 *)(entity_b->body), WHITE);

        // render animated entities, check if any are marked for deletion (not active OR body is not active)
        usize num_entities = entity_count();
        for (usize i = num_entities - 1; i > 0; --i) // TODO: figure out if it is better to use entity_count() directly here;
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
                // entity_destroy(entity);
                continue;
            }

            // skip entities with no associated animations
            if (entity->animation == NULL)
            {
                continue;
            }

            animation_render(entity->animation, entity->body->aabb.position, WHITE, texture_slots);
        }

        render_end(window, texture_slots);
        time_update_late();
    }

    return 0;
}
