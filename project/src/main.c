#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glad/glad.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "engine/global.h"
#include "engine/config.h"
#include "engine/input.h"
#include "engine/time.h"
#include "engine/physics.h"
#include "engine/util.h"
#include "engine/entity.h"
#include "engine/render.h"
#include "engine/animation.h"

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
Sprite_Sheet sprite_sheet_bullet;

static usize adef_solder_running_side_id;
static usize adef_soldier_idle_side_id;
static usize adef_soldier_idle_back_id;
static usize adef_soldier_idle_front_id;
static usize adef_bullet_id;

static usize anim_soldier_running_side_id;
static usize anim_soldier_idle_side_id;
static usize anim_soldier_idle_back_id;
static usize anim_soldier_idle_front_id;
static usize anim_bullet_id;

// performs render_sprite_sheet_init, animation_defintion_create, and animation_create for all sprite sheets
static void init_all_anims()
{
    render_sprite_sheet_init(&sprite_sheet_soldier_running_side, "assets/soldier_1_m16_running_side.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_soldier_idle_side, "assets/soldier_1_m16_idle_side.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_soldier_idle_back, "assets/soldier_1_m16_idle_back.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_soldier_idle_front, "assets/soldier_1_m16_idle_front.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_bullet, "assets/bullet_1.png", 5, 5);

    adef_solder_running_side_id = animation_definition_create(
        &sprite_sheet_soldier_running_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1},
        (u8[]){0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5},
        5);
    adef_soldier_idle_side_id = animation_definition_create(
        &sprite_sheet_soldier_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    adef_soldier_idle_back_id = animation_definition_create(
        &sprite_sheet_soldier_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    adef_soldier_idle_front_id = animation_definition_create(
        &sprite_sheet_soldier_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    adef_bullet_id = animation_definition_create(
        &sprite_sheet_bullet,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);

    anim_soldier_running_side_id = animation_create(adef_solder_running_side_id, true);
    anim_soldier_idle_side_id = animation_create(adef_soldier_idle_side_id, false);
    anim_soldier_idle_back_id = animation_create(adef_soldier_idle_back_id, false);
    anim_soldier_idle_front_id = animation_create(adef_soldier_idle_front_id, false);
    anim_bullet_id = animation_create(adef_bullet_id, false);
}

static void input_handle(Entity *player_entity)
{
    Body *player_body = physics_body_get(player_entity->body_id);

    if (global.input.escape)
    {
        should_quit = true;
    }

    f32 velx = 0;
    f32 vely = 0;

    if (global.input.right)
    {
        velx += 100;
    }

    if (global.input.left)
    {
        velx -= 100;
    }

    if (global.input.up)
    {
        vely += 100;
    }

    if (global.input.down)
    {
        vely -= 100;
    }
    if (global.input.space == KS_PRESSED)
    {
        // TODO: pull all this to a helper method
        // create bullet entity, define animation
        usize bullet_entity_id = entity_create((vec2){player_body->aabb.position[0] + 25, player_body->aabb.position[1]}, (vec2){5, 5}, (vec2){0, 0}, COLLISION_LAYER_BULLET, bullet_mask, NULL, NULL);
        Entity *bullet_entity = entity_get(bullet_entity_id);
        bullet_entity->animation_id = anim_bullet_id;

        // set bullet velocity
        Body *bullet_body = physics_body_get(bullet_entity->body_id);
        bullet_body->velocity[0] = 800;
        bullet_body->velocity[1] = 0; // TODO: remove this, already set to 0
    }

    player_body->velocity[0] = velx;
    player_body->velocity[1] = vely;
}

void player_on_hit(Body *self, Body *other, Hit hit)
{
    if (other->collision_layer = COLLISION_LAYER_ENEMY)
    {
    }
}

void player_on_hit_static(Body *self, Static_Body *other, Hit hit)
{
    if (hit.normal[1] > 0)
    {
    }
}

void bullet_on_hit(Body *self, Body *other, Hit hit)
{
}

void bullet_on_static(Body *self, Static_Body *other, Hit hit)
{
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

int main(int argc, char *argv[])
{
    time_init(60);
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

    u32 static_body_a_id = physics_static_body_create((vec2){width * 0.5 - 12.5, height - 12.5}, (vec2){width - 25, 25}, COLLISION_LAYER_TERRIAN);
    u32 static_body_b_id = physics_static_body_create((vec2){width - 12.5, height * 0.5 + 12.5}, (vec2){25, height - 25}, COLLISION_LAYER_TERRIAN);
    u32 static_body_c_id = physics_static_body_create((vec2){width * 0.5 + 12.5, 12.5}, (vec2){width - 25, 25}, COLLISION_LAYER_TERRIAN);
    u32 static_body_d_id = physics_static_body_create((vec2){12.5, height * 0.5 - 12.5}, (vec2){25, height - 25}, COLLISION_LAYER_TERRIAN);
    u32 static_body_e_id = physics_static_body_create((vec2){width * 0.5, height * 0.5}, (vec2){62.5, 62.5}, COLLISION_LAYER_TERRIAN);

    usize entity_a_id = entity_create((vec2){200, 200}, (vec2){25, 25}, (vec2){400, 0}, COLLISION_LAYER_ENEMY, enemy_mask, NULL, enemy_on_hit_static);
    usize entity_b_id = entity_create((vec2){300, 300}, (vec2){25, 25}, (vec2){400, 0}, 0, enemy_mask, NULL, enemy_on_hit_static);

    // init player
    usize player_id = entity_create((vec2){100, 200}, (vec2){42, 42}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static);
    Entity *player = entity_get(player_id);
    player->animation_id = anim_soldier_idle_side_id;

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

        Entity *player = entity_get(player_id);
        Body *body_player = physics_body_get(player->body_id);

        if (body_player->velocity[0] != 0)
        {
            player->animation_id = anim_soldier_running_side_id;
        }
        else if (body_player->velocity[1] > 0)
        {
            player->animation_id = anim_soldier_idle_back_id;
        }
        else if (body_player->velocity[1] < 0)
        {
            player->animation_id = anim_soldier_idle_front_id;
        }
        else
        {
            player->animation_id = anim_soldier_idle_side_id;
        }

        Static_Body *static_body_a = physics_static_body_get(static_body_a_id);
        Static_Body *static_body_b = physics_static_body_get(static_body_b_id);
        Static_Body *static_body_c = physics_static_body_get(static_body_c_id);
        Static_Body *static_body_d = physics_static_body_get(static_body_d_id);
        Static_Body *static_body_e = physics_static_body_get(static_body_e_id);

        input_update();
        input_handle(player);
        physics_update();
        animation_update(global.time.delta);

        render_begin();

        render_aabb((f32 *)static_body_a, WHITE);
        render_aabb((f32 *)static_body_b, WHITE);
        render_aabb((f32 *)static_body_c, WHITE);
        render_aabb((f32 *)static_body_d, WHITE);
        render_aabb((f32 *)static_body_e, WHITE);

        render_aabb((f32 *)physics_body_get(entity_get(entity_a_id)->body_id), WHITE);
        render_aabb((f32 *)physics_body_get(entity_get(entity_b_id)->body_id), WHITE);

        entity_destroy(player_id);
        printf("entity_count: %d", entity_count());
        // render animated entities
        for (usize i = 0; i < entity_count(); ++i)
        {
            Entity *entity = entity_get(i);

            if (!entity->is_active)
            {
                continue;
            }

            if (entity->animation_id == (usize)-1)
            {
                continue;
            }

            Body *body = physics_body_get(entity->body_id);
            Animation *anim = animation_get(entity->animation_id);

            if (body->velocity[0] < 0)
            {
                anim->is_flipped = true;
            }
            else if (body->velocity[0] > 0)
            {
                anim->is_flipped = false;
            }
            animation_render(anim, body->aabb.position, WHITE, texture_slots);
        }

        render_end(window, texture_slots);

        time_update_late();
    }

    return 0;
}
