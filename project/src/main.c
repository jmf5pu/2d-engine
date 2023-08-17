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

static Animation_Definition *adef_soldier_running_side;
static Animation_Definition *adef_soldier_idle_side;
static Animation_Definition *adef_soldier_idle_back;
static Animation_Definition *adef_soldier_idle_front;
static Animation_Definition *adef_bullet;

static Animation *anim_soldier_running_side;
static Animation *anim_soldier_idle_side;
static Animation *anim_soldier_idle_back;
static Animation *anim_soldier_idle_front;
static Animation *anim_bullet;

// performs render_sprite_sheet_init, animation_defintion_create, and animation_create for all sprite sheets
static void init_all_anims()
{
    render_sprite_sheet_init(&sprite_sheet_soldier_running_side, "assets/soldier_1_m16_running_side.png", 42, 42);
    printf("sprite_sheet_soldier_running_side data, w: %f, h: %f\n", sprite_sheet_soldier_running_side.cell_width, sprite_sheet_soldier_running_side.height);
    render_sprite_sheet_init(&sprite_sheet_soldier_idle_side, "assets/soldier_1_m16_idle_side.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_soldier_idle_back, "assets/soldier_1_m16_idle_back.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_soldier_idle_front, "assets/soldier_1_m16_idle_front.png", 42, 42);
    render_sprite_sheet_init(&sprite_sheet_bullet, "assets/bullet_1.png", 5, 5);
    printf("sprite_sheet_soldier_running_side: %p\n", &sprite_sheet_soldier_running_side);
    adef_soldier_running_side = animation_definition_create(
        &sprite_sheet_soldier_running_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1},
        (u8[]){0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5},
        5);
    printf("adef_solder_running_side: %p\n", adef_soldier_running_side);
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
    adef_bullet = animation_definition_create(
        &sprite_sheet_bullet,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);

    anim_soldier_running_side = animation_create(adef_soldier_running_side, true);
    anim_soldier_idle_side = animation_create(adef_soldier_idle_side, false);
    anim_soldier_idle_back = animation_create(adef_soldier_idle_back, false);
    anim_soldier_idle_front = animation_create(adef_soldier_idle_front, false);
    anim_bullet = animation_create(adef_bullet, false);
    printf("anim_soldier_running_side addr: %p\n", anim_soldier_running_side);
    printf("anim_soldier_running_side attributes:\nadef: %p\ncurrent frame time: %f\nadef->spritesheet: %p\n",
           anim_soldier_running_side->animation_definition,
           anim_soldier_running_side->current_frame_time,
           anim_soldier_running_side->animation_definition->sprite_sheet);
}

// on hit methods
void player_on_hit(Body *self, Body *other, Hit hit)
{
    if (other->collision_layer = COLLISION_LAYER_ENEMY)
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

static void input_handle(Entity *player_entity)
{
    assert(player_entity);
    assert(player_entity->body);
    Body *player_body = player_entity->body;
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
        Entity *bullet_entity = entity_create((vec2){player_body->aabb.position[0] + 25, player_body->aabb.position[1]}, (vec2){5, 5}, (vec2){0, 0}, COLLISION_LAYER_BULLET, bullet_mask, bullet_on_hit, bullet_on_hit_static);

        bullet_entity->animation = anim_bullet;

        // set bullet velocity
        Body *bullet_body = bullet_entity->body;

        bullet_body->velocity[0] = 800;
        bullet_body->velocity[1] = 0; // TODO: remove this, already set to 0
    }

    player_body->velocity[0] = velx;
    player_body->velocity[1] = vely;
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

    Static_Body *static_body_a = physics_static_body_create((vec2){width * 0.5 - 12.5, height - 12.5}, (vec2){width - 25, 25}, COLLISION_LAYER_TERRIAN);
    Static_Body *static_body_b = physics_static_body_create((vec2){width - 12.5, height * 0.5 + 12.5}, (vec2){25, height - 25}, COLLISION_LAYER_TERRIAN);
    Static_Body *static_body_c = physics_static_body_create((vec2){width * 0.5 + 12.5, 12.5}, (vec2){width - 25, 25}, COLLISION_LAYER_TERRIAN);
    Static_Body *static_body_d = physics_static_body_create((vec2){12.5, height * 0.5 - 12.5}, (vec2){25, height - 25}, COLLISION_LAYER_TERRIAN);
    Static_Body *static_body_e = physics_static_body_create((vec2){width * 0.5, height * 0.5}, (vec2){62.5, 62.5}, COLLISION_LAYER_TERRIAN);

    printf("\ncreating entity_a\n");
    Entity *entity_a = entity_create((vec2){200, 200}, (vec2){25, 25}, (vec2){400, 0}, COLLISION_LAYER_ENEMY, enemy_mask, NULL, enemy_on_hit_static);
    printf("\ncreating entity_b\n");
    Entity *entity_b = entity_create((vec2){300, 300}, (vec2){25, 25}, (vec2){400, 0}, 0, enemy_mask, NULL, enemy_on_hit_static);

    // init player
    printf("\ncreating player entity\n");
    Entity *player = entity_create((vec2){100, 200}, (vec2){42, 42}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static);

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
        player->animation = anim_soldier_running_side;
        // printf("player sprite data: %p\n", player->animation->animation_definition->sprite_sheet);

        // if (player->body->velocity[0] != 0)
        // {
        //     player->animation = anim_soldier_running_side;
        // }
        // else if (player->body->velocity[1] > 0)
        // {
        //     player->animation = anim_soldier_idle_back;
        // }
        // else if (player->body->velocity[1] < 0)
        // {
        //     player->animation = anim_soldier_idle_front;
        // }
        // else
        // {
        //     player->animation = anim_soldier_idle_side;
        // }

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

        render_aabb((f32 *)(entity_a->body), WHITE);
        render_aabb((f32 *)(entity_b->body), WHITE);
        render_aabb((f32 *)(player->body), WHITE);

        // render test sprite sheet
        printf("rendering sprite sheet\n");
        render_sprite_sheet_frame(&sprite_sheet_soldier_idle_side, 1, 1, player->body->aabb.position, false, WHITE, texture_slots);

        // render animated entities, check if any are marked for deletion (not active OR body is not active)
        usize num_entities = entity_count();
        printf("num_entities: %zd\n", num_entities);
        for (usize i = 0; i < num_entities; ++i)
        {
            Entity *entity = entity_get(i);
            // destroy any entities that are inactive or have physics bodies that are inactive
            // if (!entity->is_active || !entity->body->is_active)
            // {
            //     entity_destroy(entity);
            //     continue;
            // }

            if (entity->animation == NULL)
            {
                printf("no anim associated, continuing\n");
                continue;
            }
            Body *body = entity->body;
            // Animation *anim = animation_get(entity->animation_id);

            // if (body->velocity[0] < 0)
            // {
            //     anim->is_flipped = true;
            // }
            // else if (body->velocity[0] > 0)
            // {
            //     anim->is_flipped = false;
            // }
            animation_render(entity->animation, body->aabb.position, WHITE, texture_slots);
        }
        // printf("\n\nanimation render args:\nanim address: %p\nplayer body aabb position (x,y): %f, %f\n, texture_slots[0]: %u\n", anim_soldier_running_side, player->body->aabb.position[0], player->body->aabb.position[1], texture_slots[0]);

        // animation_render(anim_soldier_running_side, player->body->aabb.position, WHITE, texture_slots);
        // destroy any inactive physics bodies
        // usize num_physics_bodies = physics_body_count();

        // for (usize i = num_physics_bodies - 1; i > 0; --i)
        // {
        //     if (!physics_body_get(i)->is_active)
        //     {
        //         physics_body_destroy(i);
        //     }
        // }

        render_end(window, texture_slots);
        time_update_late();
    }

    return 0;
}
