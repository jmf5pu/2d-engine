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
#include "engine/render/render_internal.h"

// game specific headers
#include "structs.h"
#include "collision_behavior.h"
#include "player_helpers.h"
#include "map_helpers.h"
#include "weapon_types.h"
#include "hud.h"

static u32 texture_slots[32] = {0}; // texture slots array for batch rendering
static bool should_quit = false;    // quit flag

const u8 frame_rate = 60; // frame rate

// moves all sprites in the particular vec2 direction. Used for camera movement
void update_all_positions(Map *map, vec2 shift, bool left_player_is_active)
{
    // update all bodies' positions (includes pickups, players, etc)
    Body *body;
    Array_List *body_list = get_all_bodies();
    for (u32 i = 0; i < body_list->len; ++i)
    {
        body = array_list_get(body_list, i);

        // shift all bodies EXCEPT the active player and crosshairs
        bool is_active_player_body = (body == player_one->entity->body && left_player_is_active) || (SPLIT_SCREEN && body == player_two->entity->body && !left_player_is_active);
        bool is_crosshair = body == player_one->crosshair->entity->body || (SPLIT_SCREEN && body == player_two->crosshair->entity->body);
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
        static_body = array_list_get(static_body_list, i);
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
    time_init(frame_rate);
    config_init();
    SDL_Window *window = render_init();
    camera_init();
    physics_init();
    entity_init();
    animation_init(); // creates animation storage
    init_all_anims(); // initializes all our animations

    // define weapon types
    init_weapon_types();

    // initialize map & props
    init_map(&map);

    // init hud
    init_hud(window);

    // init player one
    player_one = malloc(sizeof(Player));
    init_player(player_one, &map, m16, 2.9, 5, 2, true);
    spawn_player(player_one, m16);

    // init player two
    if (SPLIT_SCREEN)
    {
        player_two = malloc(sizeof(Player));
        init_player(player_two, &map, base, 2.9, 5, 2, false);
        spawn_player(player_two, base);
    }

    // main gameplay loop
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

        // used to store players positions
        vec2 p1_pos_holder;
        vec2 p2_pos_holder;

        // update relative position of players and their crosshairs (transform of the position on the screen, using camera as a vector)
        if (SPLIT_SCREEN) // use left cam if screen is split
        {
            player_one->relative_position[0] = player_one->entity->body->aabb.position[0] + left_cam.position[0];
            player_one->relative_position[1] = player_one->entity->body->aabb.position[1] + left_cam.position[1];
        }
        else // otherwise use main cam TODO: perhaps make left_cam and main_cam the same object?
        {
            player_one->relative_position[0] = player_one->entity->body->aabb.position[0] + main_cam.position[0];
            player_one->relative_position[1] = player_one->entity->body->aabb.position[1] + main_cam.position[1];
        }
        player_one->crosshair->relative_position[0] = player_one->crosshair->entity->body->aabb.position[0] + left_cam.position[0];
        player_one->crosshair->relative_position[1] = player_one->crosshair->entity->body->aabb.position[1] + left_cam.position[1];

        // need to pass the RELATIVE position of the players into the physics engine to properly detect collisions
        p1_pos_holder[0] = player_one->entity->body->aabb.position[0];
        p1_pos_holder[1] = player_one->entity->body->aabb.position[1];
        player_one->entity->body->aabb.position[0] = player_one->relative_position[0];
        player_one->entity->body->aabb.position[1] = player_one->relative_position[1];

        if (SPLIT_SCREEN)
        {
            player_two->relative_position[0] = player_two->entity->body->aabb.position[0] + right_cam.position[0];
            player_two->relative_position[1] = player_two->entity->body->aabb.position[1] + right_cam.position[1];
            player_two->crosshair->relative_position[0] = player_two->crosshair->entity->body->aabb.position[0] + right_cam.position[0];
            player_two->crosshair->relative_position[1] = player_two->crosshair->entity->body->aabb.position[1] + right_cam.position[1];

            p2_pos_holder[0] = player_two->entity->body->aabb.position[0];
            p2_pos_holder[1] = player_two->entity->body->aabb.position[1];
            player_two->entity->body->aabb.position[0] = player_two->relative_position[0];
            player_two->entity->body->aabb.position[1] = player_two->relative_position[1];
        }

        // update physics bodies
        physics_update();

        // update the actual positions (saved value plus the difference generated by the physics engine)
        player_one->entity->body->aabb.position[0] = p1_pos_holder[0] + (player_one->entity->body->aabb.position[0] - player_one->relative_position[0]);
        player_one->entity->body->aabb.position[1] = p1_pos_holder[1] + (player_one->entity->body->aabb.position[1] - player_one->relative_position[1]);
        if (SPLIT_SCREEN)
        {
            player_two->entity->body->aabb.position[0] = p2_pos_holder[0] + (player_two->entity->body->aabb.position[0] - player_two->relative_position[0]);
            player_two->entity->body->aabb.position[1] = p2_pos_holder[1] + (player_two->entity->body->aabb.position[1] - player_two->relative_position[1]);
        }

        animation_update(global.time.delta);

        // need to run render loop twice if we are actively splitting the screen
        int player_count = SPLIT_SCREEN ? 2 : 1;
        for (int i = 0; i < player_count; i++)
        {
            // FIRST:
            // For the player being rendered, update render dimensions based on player status,
            // update the corresponding projection matrix, update the camera location,
            // and clear the rendering buffer to begin rendering
            // THEN:
            // handle the corresponding inputs and update statuses/directions
            // must handle player input BEFORE rendering because entities can
            // be created in `handle_player_shooting`
            if (SPLIT_SCREEN && i == 0)
            {
                set_render_dimensions(player_one->render_scale_factor, false, true);
                camera_update(&left_cam, player_one, &map);
                render_begin_left();
                handle_player_input(player_one);
                update_player_status(player_one);
                update_player_animations(player_one);
            }
            else if (SPLIT_SCREEN && i == 1)
            {
                set_render_dimensions(player_two->render_scale_factor, false, true);
                camera_update(&right_cam, player_two, &map);
                render_begin_right();
                handle_player_input(player_two);
                update_player_status(player_two);
                update_player_animations(player_two);
            }
            else // hit when screen is not being split
            {
                set_render_dimensions(player_one->render_scale_factor, false, true);
                camera_update(&main_cam, player_one, &map);
                render_begin();
                handle_player_input(player_one);
                update_player_status(player_one);
                update_player_animations(player_one);
            }

            // save aabb positions again
            p1_pos_holder[0] = player_one->entity->body->aabb.position[0];
            p1_pos_holder[1] = player_one->entity->body->aabb.position[1];

            if (SPLIT_SCREEN)
            {
                p2_pos_holder[0] = player_two->entity->body->aabb.position[0];
                p2_pos_holder[1] = player_two->entity->body->aabb.position[1];
            }

            // move all positions to relative position based on camera except for the active player and crosshairs
            if (SPLIT_SCREEN && i == 0)
            {
                player_two->entity->body->aabb.position[0] = player_two->relative_position[0];
                player_two->entity->body->aabb.position[1] = player_two->relative_position[1];
                update_all_positions(&map, (vec2){-1 * left_cam.position[0], -1 * left_cam.position[1]}, true);
            }
            else if (SPLIT_SCREEN && i == 1)
            {
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

                // for debugging
                if (RENDER_PHYSICS_BODIES)
                    render_aabb((f32 *)&entity->body->aabb, WHITE);

                // destroy any entities that are inactive or have physics bodies that are inactive and aren't associated with players, crosshairs, or pickups
                bool is_left_crosshair = entity == player_one->crosshair->entity;
                bool is_right_crosshair = SPLIT_SCREEN ? (entity == player_two->crosshair->entity) : false;
                bool is_player = SPLIT_SCREEN ? (entity == player_one->entity || entity == player_two->entity) : (entity == player_one->entity);

                bool is_pickup = false;
                for (int k = 0; k < map.num_pickups; k++)
                {
                    if (entity == map.pickups[k].entity)
                        is_pickup = true;
                }
                if ((!entity->is_active || !entity->body->is_active) && !is_player && !is_pickup && !is_left_crosshair && !is_right_crosshair)
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
            }

            // render map sprites
            for (int l = 0; l < map.num_props; l++)
            {
                Prop prop = map.props[l];

                /*
                 * Determining the props z_index based on position relative to player
                 * z_index should be below the players (0) if the lowest point of the player is under the y
                 * threshold we set OR they are above the prop entirely. Also the main background, (index 0)
                 * is rendered beneath the player no matter what
                 */
                f32 player_y_min;
                if (i == 0)
                { // rendering left side
                    player_y_min = player_one->entity->body->aabb.position[1] - player_one->entity->body->aabb.half_size[1];
                }
                else
                { // rendering right side (if it exists)
                    player_y_min = player_two->entity->body->aabb.position[1] - player_two->entity->body->aabb.half_size[1];
                }
                bool is_below_player = player_y_min < (prop.sprite->position[1] - prop.sprite->half_size[1] + prop.layer_threshold) || player_y_min > (prop.sprite->position[1] + prop.sprite->half_size[1]) || l == 0;
                i32 z_index = is_below_player ? prop.sprite->z_index : 1;
                render_sprite_sheet_frame(prop.sprite->sprite_sheet, window, prop.sprite->row, prop.sprite->column, prop.sprite->position, z_index, prop.sprite->is_flipped, RENDER_PHYSICS_BODIES ? (vec4){0.9, 0.9, 0.9, 0.9} : prop.sprite->color, texture_slots);

                // render the static bodies
                if (RENDER_PHYSICS_BODIES)
                {
                    for (int k = 0; k < prop.num_static_bodies; k++)
                    {
                        render_aabb((f32 *)&prop.static_bodies[k]->aabb, WHITE);
                    }
                }
            }

            // throw left side stuff into the rendering buffer, without performing the screen swap yet
            if (SPLIT_SCREEN && i == 0)
            {
                render_end(window, texture_slots, false);
            }

            // update the physics bodies move all positions back
            if (SPLIT_SCREEN && i == 0)
            {
                update_all_positions(&map, left_cam.position, true);
                player_two->entity->body->aabb.position[0] = p2_pos_holder[0];
                player_two->entity->body->aabb.position[1] = p2_pos_holder[1];
            }
            else if (SPLIT_SCREEN && i == 1)
            {
                update_all_positions(&map, right_cam.position, false);
                player_one->entity->body->aabb.position[0] = p1_pos_holder[0];
                player_one->entity->body->aabb.position[1] = p1_pos_holder[1];
            }
            else // not split
                update_all_positions(&map, (vec2){main_cam.position[0], main_cam.position[1]}, true);
        }
        render_end(window, texture_slots, false);

        set_render_dimensions(DEFAULT_RENDER_SCALE_FACTOR, true, true);
        render_begin_hud();
        // AABB weapon_hud_aabb;
        // weapon_hud_aabb.half_size[0] = 25;
        // weapon_hud_aabb.half_size[1] = 35;
        // weapon_hud_aabb.position[0] = 25;
        // weapon_hud_aabb.position[1] = 35;
        // AABB health_hud_aabb;
        // health_hud_aabb.half_size[0] = 50;
        // health_hud_aabb.half_size[1] = 50;
        // health_hud_aabb.position[0] = 50;
        // health_hud_aabb.position[1] = window_height - 50;
        // render_aabb((f32 *)(&weapon_hud_aabb), BLUE);
        // render_aabb((f32 *)(&health_hud_aabb), RED);
        render_hud(window, texture_slots);
        render_end(window, texture_slots, true);

        time_update_late();
    }

    free_map_attributes(&map);
    free_player(player_one);
    if (SPLIT_SCREEN)
        free_player(player_two);
    free_weapon_types();
    free_hud();
    return 0;
}
