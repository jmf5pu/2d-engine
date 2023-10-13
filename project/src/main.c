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
#include "engine/camera.h"
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

static u32 texture_slots[32] = {0}; // texture slots array for batch rendering
static bool should_quit = false;    // quit flag
static bool render_bodies = false;  // set to true for debugging static bodies
static bool split_screen = true;

const u8 frame_rate = 60; // frame rate

// moves all sprites in the particular vec2 direction. Used for camera movement
void update_all_positions(Map *map, vec2 shift, bool left_player_is_active)
{
    // update all bodies' positions (includes pickups, players, etc)
    Body *body;
    Array_List *body_list = get_all_bodies();
    for (u32 i = 0; i < body_list->len; ++i)
    {
        body = array_list_get(body_list, i, "in camera update\n");
        /* shift all bodies that:
         * are either not associated with a player
         * OR are not the active player (p1 is active on left, p2 is active on right)
         *
         * Additionally, we do not render p1's crosshair on the right or vice versa
         */
        bool is_active_player_body = (body == player_one->entity->body && left_player_is_active) || (body == player_two->entity->body && !left_player_is_active);
        bool is_crosshair = body == player_one->crosshair->body || body == player_two->crosshair->body;
        if (!is_active_player_body && !is_crosshair)
        {
            body->aabb.position[0] += shift[0];
            body->aabb.position[1] += shift[1];
        }
    }

    // update all static bodies' positions
    Static_Body *static_body;
    Array_List *static_body_list = get_all_static_bodies();
    for (u32 i = 0; i < static_body_list->len; ++i)
    {
        static_body = array_list_get(static_body_list, i, "in camera update\n");
        static_body->aabb.position[0] += shift[0];
        static_body->aabb.position[1] += shift[1];
    }

    // update positions of all props on the map
    for (int i = 0; i < map->num_props; i++)
    {
        Prop prop = map->props[i];
        prop.sprite->position[0] += shift[0];
        prop.sprite->position[1] += shift[1];
    }

    // spawn points are relative, no need to shift them
}

int main(int argc, char *argv[])
{
    int render_width = split_screen ? WINDOW_WIDTH * 0.25 : WINDOW_WIDTH * 0.5; // half width if split screen is active
    int render_height = WINDOW_HEIGHT * 0.5;

    time_init(frame_rate);
    config_init();
    SDL_Window *window = render_init(render_width, render_height);
    physics_init();
    entity_init();
    animation_init(); // creates animation storage
    init_all_anims(); // initializes all our animations

    // create camera structs
    Camera main_cam = (Camera){
        .position = {0, 0},
        .buffer = {50, render_width - 50, 50, render_height - 50}, // Buffers: Left, Right, Bottom, Top (actual screen coords, NOT relative)
    };

    // half way to the left of the screen, buffers the center instead of the right side
    Camera left_cam = (Camera){
        .position = {0, 0},
        .buffer = {50, render_width - 50, 50, render_height - 50},
    };

    // half way to the right of the screen, buffers the center instead of the left side
    Camera right_cam = (Camera){
        .position = {render_width, 0}, // essentially bump everything to the right by half the screen width right off the bat
        .buffer = {50, render_width - 50, 50, render_height - 50},
    };

    // define weapon types
    init_weapon_types();

    // initialize map & props
    init_map(&map);

    // init player one
    player_one = malloc(sizeof(Player));
    player_one->entity = entity_create(map.player_one_spawn_points[0], (vec2){36, 36}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static);
    player_one->crosshair = entity_create((vec2){player_one->entity->body->aabb.position[0], player_one->entity->body->aabb.position[1]}, (vec2){27, 27}, (vec2){0, 0}, COLLISION_LAYER_CROSSHAIR, crosshair_mask, crosshair_on_hit, crosshair_on_hit_static);
    player_one->crosshair->is_active = false;
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
    player_one->spawn_point[0] = map.player_one_spawn_points[0][0];
    player_one->spawn_point[1] = map.player_one_spawn_points[0][1];
    player_one->relative_position[0] = player_one->entity->body->aabb.position[0];
    player_one->relative_position[1] = player_one->entity->body->aabb.position[1];
    player_one->status = PLAYER_SPAWNING;
    player_one->despawn_time = 2.9;
    player_one->spawn_delay = 5;
    player_one->spawn_time = 2;
    player_one->frames_on_status = 0;
    player_one->health = 100;
    player_one->is_left_player = true;

    // init player two
    player_two = malloc(sizeof(Player));
    player_two->entity = entity_create((vec2){map.player_two_spawn_points[0][1], map.player_two_spawn_points[0][1]}, (vec2){36, 36}, (vec2){0, 0}, COLLISION_LAYER_PLAYER, player_mask, player_on_hit, player_on_hit_static);
    player_two->crosshair = entity_create((vec2){player_two->entity->body->aabb.position[0], player_two->entity->body->aabb.position[1]}, (vec2){27, 27}, (vec2){0, 0}, COLLISION_LAYER_CROSSHAIR, crosshair_mask, crosshair_on_hit, crosshair_on_hit_static);
    player_two->crosshair->is_active = false;
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
    player_two->spawn_point[0] = map.player_two_spawn_points[0][0];
    player_two->spawn_point[1] = map.player_two_spawn_points[0][1];
    player_two->relative_position[0] = player_two->entity->body->aabb.position[0];
    player_two->relative_position[1] = player_two->entity->body->aabb.position[1];
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

        // update relative position of players (transform of the position on the screen, using camera as a vector)
        player_one->relative_position[0] = player_one->entity->body->aabb.position[0] + left_cam.position[0];
        player_one->relative_position[1] = player_one->entity->body->aabb.position[1] + left_cam.position[1];
        player_two->relative_position[0] = player_two->entity->body->aabb.position[0] + right_cam.position[0];
        player_two->relative_position[1] = player_two->entity->body->aabb.position[1] + right_cam.position[1];

        // need to pass the RELATIVE position of the players into the physics engine to properly detect collisions
        vec2 p1_pos_holder = {player_one->entity->body->aabb.position[0], player_one->entity->body->aabb.position[1]};
        player_one->entity->body->aabb.position[0] = player_one->relative_position[0];
        player_one->entity->body->aabb.position[1] = player_one->relative_position[1];

        vec2 p2_pos_holder = {player_two->entity->body->aabb.position[0], player_two->entity->body->aabb.position[1]};
        player_two->entity->body->aabb.position[0] = player_two->relative_position[0];
        player_two->entity->body->aabb.position[1] = player_two->relative_position[1];

        // update physics bodies
        physics_update();

        // update the actual positions (saved value plus the difference generated by the physics engine)
        player_one->entity->body->aabb.position[0] = p1_pos_holder[0] + (player_one->entity->body->aabb.position[0] - player_one->relative_position[0]);
        player_one->entity->body->aabb.position[1] = p1_pos_holder[1] + (player_one->entity->body->aabb.position[1] - player_one->relative_position[1]);

        player_two->entity->body->aabb.position[0] = p2_pos_holder[0] + (player_two->entity->body->aabb.position[0] - player_two->relative_position[0]);
        player_two->entity->body->aabb.position[1] = p2_pos_holder[1] + (player_two->entity->body->aabb.position[1] - player_two->relative_position[1]);

        animation_update(global.time.delta);
        // printf("left_cam pos: %f, %f\n", left_cam.position[0], left_cam.position[1]);
        // printf("right_cam pos: %f, %f\n", right_cam.position[0], right_cam.position[1]);
        // printf("player_one pos: %f, %f\n", player_one->entity->body->aabb.position[0], player_one->entity->body->aabb.position[1]);
        // printf("player_one relative position: %f, %f\n", player_one->relative_position[0], player_one->relative_position[1]);
        // printf("player_two pos: %f, %f\n", player_two->entity->body->aabb.position[0], player_two->entity->body->aabb.position[1]);
        // printf("player_two relative position: %f, %f\n", player_two->relative_position[0], player_two->relative_position[1]);

        if (split_screen)
        {
            camera_update(&left_cam, player_one->entity->body, &map);
            camera_update(&right_cam, player_two->entity->body, &map);
        }
        else
            camera_update(&main_cam, player_one->entity->body, &map);

        // need to run render loop twice if we are actively splitting the screen
        int render_count = split_screen ? 2 : 1;
        for (int i = 0; i < render_count; i++)
        {
            if (split_screen && i == 0)
            {
                render_begin_left(); // render left side
            }
            else if (split_screen && i == 1)
            {
                render_begin_right(); // render_right side
            }
            else // hit when screen is not being split
            {
                render_begin();
            }

            // handle the corresponding inputs and update statuses/directions
            // must handle player input BEFORE rendering because entities can
            // be created in `handle_player_shooting`
            if (split_screen && i == 0)
            {
                handle_player_input(player_one);
                update_player_status(player_one);
                update_player_animations(player_one);
            }
            else if (split_screen && i == 1)
            {
                handle_player_input(player_two);
                update_player_status(player_two);
                update_player_animations(player_two);
            }
            else
            {
                // handle player inputs
                handle_player_input(player_one);
                handle_player_input(player_two);

                // update player statuses
                update_player_status(player_one);
                update_player_status(player_two);

                // update player animations
                update_player_animations(player_one);
                update_player_animations(player_two);
            }

            vec2 p1_pos_holder_2 = {player_one->entity->body->aabb.position[0], player_one->entity->body->aabb.position[1]};
            vec2 p2_pos_holder_2 = {player_two->entity->body->aabb.position[0], player_two->entity->body->aabb.position[1]};

            if (split_screen && i == 0)
            {
                player_two->entity->body->aabb.position[0] = player_two->relative_position[0];
                player_two->entity->body->aabb.position[1] = player_two->relative_position[1];
                update_all_positions(&map, (vec2){-1 * left_cam.position[0], -1 * left_cam.position[1]}, true);
            }
            else if (split_screen && i == 1)
            { // i == 1 TODO: will need to be updated when we merge cameras
                player_one->entity->body->aabb.position[0] = player_one->relative_position[0];
                player_one->entity->body->aabb.position[1] = player_one->relative_position[1];
                update_all_positions(&map, (vec2){-1 * right_cam.position[0], -1 * right_cam.position[1]}, false);
            }
            else // not split
                update_all_positions(&map, (vec2){-1 * main_cam.position[0], -1 * main_cam.position[1]}, true);

            // render animated entities, check if any are marked for deletion (not active OR body is not active)
            int num_entities = (int)entity_count();
            for (int j = num_entities - 1; j >= 0; --j)
            {
                Entity *entity = entity_get(j);

                // destroy any entities that are inactive or have physics bodies that are inactive and aren't associated with players, crosshairs, or pickups
                bool is_left_crosshair = entity == player_one->crosshair;
                bool is_right_crosshair = entity == player_two->crosshair;
                bool is_pickup = false;
                for (int k = 0; k < map.num_pickups; k++)
                {
                    if (entity == map.pickups[k].entity)
                        is_pickup = true;
                }
                if ((!entity->is_active || !entity->body->is_active) && entity != player_one->entity && entity != player_two->entity && !is_pickup && !is_left_crosshair && !is_right_crosshair)
                {
                    entity_destroy(entity);
                }

                // skip entities with no associated animations, check if players and pickups are inactive
                if (!entity->animation || !entity->is_active || !entity->body->is_active || i == 0 && is_right_crosshair || i == 1 && is_left_crosshair)
                {
                    continue;
                }

                // render the entity's animation
                animation_render(entity->animation, window, entity->body->aabb.position, 0, WHITE, texture_slots);

                // for debugging collisions
                if (render_bodies)
                    render_aabb((f32 *)&entity->body->aabb, WHITE);
            }

            // render map sprites
            for (int l = 0; l < map.num_props; l++)
            {
                Prop prop = map.props[l];
                prop.sprite->sprite_sheet;

                /*
                 * Determining the props z_index based on position relative to player
                 * z_index should be below the players (0) if the lowest point of the player is under the y
                 * threshold we set OR they are above the prop entirely. Also the main background, (index 0)
                 * is rendered beneath the player no matter what
                 */
                f32 player_y_min = player_one->entity->body->aabb.position[1] - player_one->entity->body->aabb.half_size[1];
                bool is_below_player = player_y_min < (prop.sprite->position[1] - prop.sprite->half_size[1] + prop.layer_threshold) || player_y_min > (prop.sprite->position[1] + prop.sprite->half_size[1]) || l == 0;
                i32 z_index = is_below_player ? prop.sprite->z_index : 1;
                render_sprite_sheet_frame(prop.sprite->sprite_sheet, window, prop.sprite->row, prop.sprite->column, prop.sprite->position, z_index, prop.sprite->is_flipped, render_bodies ? (vec4){0.9, 0.9, 0.9, 0.9} : prop.sprite->color, texture_slots);

                // render the static body
                if (prop.static_body && render_bodies)
                {
                    render_aabb(&prop.static_body, WHITE);
                }
            }

            // throw left side stuff into the rendering buffer, without performing the screen swap yet
            if (split_screen && i == 0)
            {
                render_end(window, texture_slots, false);
            }

            // update the physics bodies move all positions back
            if (split_screen && i == 0)
            {
                update_all_positions(&map, left_cam.position, true);
                player_two->entity->body->aabb.position[0] = p2_pos_holder_2[0];
                player_two->entity->body->aabb.position[1] = p2_pos_holder_2[1];
            }
            else if (split_screen && i == 1)
            {
                update_all_positions(&map, right_cam.position, false);
                player_one->entity->body->aabb.position[0] = p1_pos_holder_2[0];
                player_one->entity->body->aabb.position[1] = p1_pos_holder_2[1];
            }
            else // not split
                update_all_positions(&map, (vec2){main_cam.position[0], main_cam.position[1]}, true);
        }
        render_end(window, texture_slots, true);

        time_update_late();
    }

    free_map_attributes(&map);
    free(player_one);
    free(player_two);

    return 0;
}
