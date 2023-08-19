#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <assert.h>

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
#include "player.h"

typedef enum collision_layer
{
    COLLISION_LAYER_PLAYER = 1,
    COLLISION_LAYER_ENEMY = 1 << 1,
    COLLISION_LAYER_TERRIAN = 1 << 2,
    COLLISION_LAYER_BULLET = 1 << 3,
} Collision_Layer;

// collision masks
const u8 enemy_mask = COLLISION_LAYER_PLAYER | COLLISION_LAYER_TERRIAN;
const u8 player_mask = COLLISION_LAYER_ENEMY | COLLISION_LAYER_TERRIAN;
const u8 bullet_mask = COLLISION_LAYER_ENEMY | COLLISION_LAYER_TERRIAN;

static u32 texture_slots[8] = {0};
static bool should_quit = false;

Sprite_Sheet sprite_sheet_soldier_running_side;
Sprite_Sheet sprite_sheet_soldier_idle_side;
Sprite_Sheet sprite_sheet_soldier_idle_back;
Sprite_Sheet sprite_sheet_soldier_idle_front;
Sprite_Sheet sprite_sheet_bullet_1_horizontal;
Sprite_Sheet sprite_sheet_bullet_1_vertical;

static Animation_Definition *adef_soldier_running_side;
static Animation_Definition *adef_soldier_idle_side;
static Animation_Definition *adef_soldier_idle_back;
static Animation_Definition *adef_soldier_idle_front;
static Animation_Definition *adef_bullet_1_horizontal;
static Animation_Definition *adef_bullet_1_vertical;

static Animation *anim_soldier_running_side;
static Animation *anim_soldier_idle_side;
static Animation *anim_soldier_idle_back;
static Animation *anim_soldier_idle_front;
static Animation *anim_bullet_1_horizontal;
static Animation *anim_bullet_1_vertical;

// performs render_sprite_sheet_init, animation_defintion_create, and animation_create for all sprite sheets
static void init_all_anims()
{
    render_sprite_sheet_init(&sprite_sheet_soldier_running_side, "assets/soldier_1_m16_running_side.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_soldier_idle_side, "assets/soldier_1_m16_idle_side.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_soldier_idle_back, "assets/soldier_1_m16_idle_back.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_soldier_idle_front, "assets/soldier_1_m16_idle_front.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_bullet_1_horizontal, "assets/bullet_1_horizontal.png", 5, 5);
    render_sprite_sheet_init(&sprite_sheet_bullet_1_vertical, "assets/bullet_1_vertical.png", 5, 5);

    adef_soldier_running_side = animation_definition_create(
        &sprite_sheet_soldier_running_side,
        (f32[]){0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04, 0.04},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    adef_soldier_idle_side = animation_definition_create(
        &sprite_sheet_soldier_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
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

    anim_soldier_running_side = animation_create(adef_soldier_running_side, true);
    anim_soldier_idle_side = animation_create(adef_soldier_idle_side, false);
    anim_soldier_idle_back = animation_create(adef_soldier_idle_back, false);
    anim_soldier_idle_front = animation_create(adef_soldier_idle_front, false);
    anim_bullet_1_horizontal = animation_create(adef_bullet_1_horizontal, false);
    anim_bullet_1_vertical = animation_create(adef_bullet_1_vertical, false);
}

// on hit methods
void player_on_hit(Body *self, Body *other, Hit hit)
{
    if (other->collision_layer == COLLISION_LAYER_ENEMY)
    {
    }
}

void player_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
}

void bullet_on_hit(Body *self, Body *other, Hit hit)
{
    // mark for body (and entity) for destruction
    self->is_active = false;
}

void bullet_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
    // mark for body (and entity) for destruction
    self->is_active = false;
}

void enemy_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
    if (hit.normal[0] > 0)
    {
        self->velocity[0] = 400;
    }
    if (hit.normal[0] < 0)
    {
        self->velocity[0] = -400;
    }
}

static void input_handle(Player *player)
{
    if (global.input.escape)
    {
        should_quit = true;
    }

    f32 velx = 0;
    f32 vely = 0;

    if (global.input.right)
    {
        player->direction = RIGHT;
        velx += 150;
    }

    if (global.input.left)
    {
        player->direction = LEFT;
        velx -= 150;
    }

    if (global.input.up)
    {
        player->direction = UP;
        vely += 200;
    }

    if (global.input.down)
    {
        player->direction = DOWN;
        vely -= 200;
    }
    if (global.input.space == KS_PRESSED)
    {
        // TODO: pull all this to a helper method
        // create bullet entity, define animation
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
        player->entity->animation = anim_soldier_idle_front;
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

    Entity *entity_a = entity_create((vec2){200, 200}, (vec2){25, 25}, (vec2){400, 0}, COLLISION_LAYER_ENEMY, enemy_mask, NULL, enemy_on_hit_static);
    Entity *entity_b = entity_create((vec2){300, 300}, (vec2){25, 25}, (vec2){400, 0}, 0, enemy_mask, NULL, enemy_on_hit_static);

    // init player
    Player player_one =
        {
            .entity = entity_create((vec2){100, 200}, (vec2){42, 42}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static),
            .direction = RIGHT,
            .weapon = RIFLE,
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
        input_handle(&player_one);
        update_player_animations(&player_one);
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
        render_aabb((f32 *)(entity_a->body), WHITE);
        render_aabb((f32 *)(entity_b->body), WHITE);

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

            // if (player_one.entity->body->velocity[0] < 0)
            // {
            //     player_one.entity->animation->is_flipped = true;
            // }
            // else if (player_one.entity->body->velocity[0] > 0)
            // {
            //     player_one.entity->animation->is_flipped = false;
            // }
            animation_render(entity->animation, entity->body->aabb.position, WHITE, texture_slots);
        }

        render_end(window, texture_slots);
        time_update_late();
    }

    return 0;
}
