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
#include "engine/hash_map.h"

// game specific headers
#include "structs.h"
#include "collision_behavior.h"
#include "player_helpers.h"
#include "map_helpers.h"
#include "weapon_types.h"

bool render_bodies = false; // set to true for debugging static bodies

const u8 frame_rate = 60;           // frame rate
static u32 texture_slots[16] = {0}; // texture slots array for batch rendering
static bool should_quit = false;    // quit flag

// rendering dimensions
static f32 render_width;
static f32 render_height;

// init spawn points
static vec2 spawn_point_one = {100, 200};
static vec2 spawn_point_two = {550, 200};

int main(int argc, char *argv[])
{
    time_init(frame_rate);
    config_init();
    SDL_Window *window = render_init();
    physics_init();
    entity_init();
    animation_init(); // creates animation storage
    init_all_anims(); // initializes all our animations

    // define weapon types
    init_weapon_types();

    // initialize map & props
    init_map(&map);

    // get window & render dimensions
    i32 window_width, window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    render_width = window_width / render_get_scale();
    render_height = window_height / render_get_scale();

    // init player one
    player_one = malloc(sizeof(Player));
    player_one->entity = entity_create(spawn_point_one, (vec2){36, 36}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static);
    player_one->crosshair = NULL;
    player_one->direction = RIGHT;
    player_one->weapon = &(Weapon){
        .name = m16.name,
        .fire_mode = m16.fire_mode,
        .capacity = m16.capacity,
        .current_capacity = m16.capacity,
        .max_fire_rate = m16.max_fire_rate,
        .burst_count = m16.burst_count,
        .burst_delay = m16.burst_delay,
        .burst_shots_remaining = m16.burst_count,
        .damage = m16.damage,
        .bullet_velocity = m16.bullet_velocity,
        .frames_since_last_shot = 0,
        .ready_to_fire = true,
    };
    player_one->armor = &(Armor){
        .name = "",
        .integrity = 0,

    };
    player_one->spawn_point[0] = spawn_point_one[0];
    player_one->spawn_point[1] = spawn_point_one[1];
    player_one->status = PLAYER_SPAWNING;
    player_one->despawn_time = 2.9;
    player_one->spawn_delay = 5;
    player_one->spawn_time = 2;
    player_one->frames_on_status = 0;
    player_one->health = 100;
    player_one->is_left_player = true;

    // init player two
    player_two = malloc(sizeof(Player));
    player_two->entity = entity_create(spawn_point_two, (vec2){36, 36}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static);
    player_two->crosshair = NULL;
    player_two->direction = LEFT;
    player_two->weapon = &(Weapon){
        .name = m16.name,
        .fire_mode = m16.fire_mode,
        .capacity = m16.capacity,
        .current_capacity = m16.capacity,
        .max_fire_rate = m16.max_fire_rate,
        .burst_count = m16.burst_count,
        .burst_delay = m16.burst_delay,
        .burst_shots_remaining = m16.burst_count,
        .damage = m16.damage,
        .bullet_velocity = m16.bullet_velocity,
        .frames_since_last_shot = 0,
        .ready_to_fire = true,
    };
    player_two->armor = &(Armor){
        .name = "",
        .integrity = 0,

    };
    player_two->spawn_point[0] = spawn_point_two[0];
    player_two->spawn_point[1] = spawn_point_two[1];
    player_two->status = PLAYER_SPAWNING;
    player_two->despawn_time = 2.9;
    player_two->spawn_delay = 5;
    player_two->spawn_time = 2;
    player_two->frames_on_status = 0;
    player_two->health = 100;
    player_two->is_left_player = false;

    SDL_ShowCursor(false);

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

        // update map
        update_map(&map);

        // grab current inputs
        input_update();

        // handle player inputs
        handle_player_input(player_one);
        handle_player_input(player_two);

        // update player statuses
        update_player_status(player_one);
        update_player_status(player_two);

        // update player animations
        update_player_animations(player_one);
        update_player_animations(player_two);

        physics_update();
        animation_update(global.time.delta);
        render_begin();

        // render animated entities, check if any are marked for deletion (not active OR body is not active)
        int num_entities = (int)entity_count();
        for (int i = num_entities - 1; i >= 0; --i)
        {
            Entity *entity = entity_get(i);

            // destroy any entities that are inactive or have physics bodies that are inactive and aren't associated with players or pickups bool is_pickup = false;

            bool is_pickup = false;

            for (int j = 0; j < map.num_pickups; j++)
            {
                if (entity == map.pickups[j].entity)
                    is_pickup = true;
            }
            if ((!entity->is_active || !entity->body->is_active) && entity != player_one->entity && entity != player_two->entity && !is_pickup)
            {
                entity_destroy(entity);
            }

            // skip entities with no associated animations, check if players and pickups are inactive
            if (!entity->animation || !entity->is_active || !entity->body->is_active)
            {
                continue;
            }
            animation_render(entity->animation, window, entity->body->aabb.position, 0, WHITE, texture_slots);
            if (render_bodies)
                render_aabb((f32 *)&entity->body->aabb, WHITE);
        }

        // render map sprites
        for (int i = 0; i < map.num_props; i++)
        {
            Prop prop = map.props[i];
            prop.sprite->sprite_sheet;

            /*
             * Determining the props z_index based on position relative to player
             * z_index should be below the players (0) if the lowest point of the player is under the y
             * threshold we set OR they are above the prop entirely. Also the main background, (index 0)
             * is rendered beneath the player no matter what
             */
            f32 player_y_min = player_one->entity->body->aabb.position[1] - player_one->entity->body->aabb.half_size[1];
            bool is_below_player = player_y_min < (prop.sprite->position[1] - prop.sprite->half_size[1] + prop.layer_threshold) || player_y_min > (prop.sprite->position[1] + prop.sprite->half_size[1]) || i == 0;
            i32 z_index = is_below_player ? prop.sprite->z_index : 1;
            render_sprite_sheet_frame(prop.sprite->sprite_sheet, window, prop.sprite->row, prop.sprite->column, prop.sprite->position, z_index, prop.sprite->is_flipped, render_bodies ? (vec4){0.9, 0.9, 0.9, 0.9} : prop.sprite->color, texture_slots);

            // render the static body
            if (prop.static_body && render_bodies)
            {
                render_aabb(&prop.static_body, WHITE);
            }
        }

        render_end(window, texture_slots, true);

        time_update_late();
    }

    free_map_attributes(&map);
    free(player_one);
    free(player_two);

    return 0;
}
