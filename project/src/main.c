#include <glad/glad.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <assert.h>

// engine headers
#include "engine/animation.h"
#include "engine/array_list.h"
#include "engine/camera.h"
#include "engine/config.h"
#include "engine/entity.h"
#include "engine/global.h"
#include "engine/hash_map.h"
#include "engine/input/input.h"
#include "engine/physics.h"
#include "engine/render.h"
#include "engine/render/render_internal.h"
#include "engine/time.h"
#include "engine/util.h"

// game specific headers
#include "collision_behavior/collision_behavior.h"
#include "effects/effects.h"
#include "hud/hud.h"
#include "main_helpers/main_helpers.h"
#include "map_helpers/map_helpers.h"
#include "menu_helpers/menu_helpers.h"
#include "player_helpers/player_helpers.h"
#include "structs.h"
#include "weapon_types/weapon_types.h"

static u32 texture_slots[32] = {0}; // texture slots array for batch rendering
static bool should_quit = false;    // quit flag
vec4 game_color;

const u8 frame_rate = 60; // frame rate

// TODO: move this out of main.c
bool vec4_is_equal(vec4 first, vec4 second) { return first[0] == second[0] && first[1] == second[1] && first[2] == second[2] && first[3] == second[3]; }
// returns TRUE if the first RGB value is less than the second for each value in
// RGB, otherwise returns false
bool vec4_color_cmp(vec4 first, vec4 second) { return first[0] < second[0] && first[1] < second[1] && first[2] < second[2]; }

int main(int argc, char *argv[])
{
    time_init(frame_rate);
    config_init();
    SDL_Window *window = render_init();
    physics_init();
    entity_init();
    animation_init();        // creates animation storage
    init_all_player_anims(); // initializes all our animations
    game_state = GS_RUNNING;
    init_weapon_types();
    init_map(&map);
    init_hud(window);
    init_menus();
    init_game_controllers();
    init_effects();

    // init game color
    vec4_dup(game_color, WHITE);

    // MAIN GAMEPLAY LOOP
    while (!should_quit) {
        time_update();

        // needed for controller support:
        if (player_one)
            maintain_controller_keypresses(player_one);
        if (player_two)
            maintain_controller_keypresses(player_two);

        // grab current inputs
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                should_quit = true;
                break;
            case SDL_JOYBUTTONDOWN:
            case SDL_JOYBUTTONUP:
                if (player_one && event.cbutton.which == player_one->input_state->controller_input_state->controller_id)
                    update_player_input_state_via_controller(player_one, &event);
                if (player_two && event.cbutton.which == player_two->input_state->controller_input_state->controller_id)
                    update_player_input_state_via_controller(player_two, &event);
                break;
            default:
                break;
            }
        }

        update_bound_key_states();

        animation_update(global.time.delta);

        switch (game_state) {
        case GS_MAIN_MENU:
            // free_players(); // reset players when exit back to main menu.
            //  Important so that we don't malloc twice if we go
            //  from menu -> running -> menu -> running
            render_begin();
            update_menu(main_menu, global.input);
            render_main_menu(window, texture_slots);
            render_end(window, texture_slots, true);
            break;
        case GS_GAME_MODE_MENU:
            render_begin();
            update_menu(mode_menu, global.input);
            render_mode_menu(window, texture_slots);
            render_end(window, texture_slots, true);
            break;
        case GS_SURVIVAL_MENU:
            render_begin();
            update_menu(survival_menu, global.input);
            render_survival_menu(window, texture_slots);
            render_end(window, texture_slots, true);
            break;
        case GS_PAUSE_MENU:
        case GS_RUNNING:
            // grey everything out if game is paused
            update_game_color(game_color);

            // init players and camera and spawn players if game is
            // just starting up
            if (!player_one) {
                if (SPLIT_SCREEN)
                    set_render_dimensions(
                        DEFAULT_RENDER_SCALE_FACTOR,
                        false,
                        false); // update the render width
                                // if split screen so that
                                // players will be centered
                                // correctly
                camera_init();

                player_one = malloc(sizeof(Player));
                init_player(player_one, &map, m16, 2.9, 5, 2, true);
                spawn_player(player_one, m16);
                update_player_anims(player_one);
            }

            if (SPLIT_SCREEN && !player_two) {
                player_two = malloc(sizeof(Player));
                init_player(player_two, &map, m16, 2.9, 5, 2, false);
                spawn_player(player_two, m16);
                update_player_anims(player_two);
            }

            // check if pause was hit, update game state
            if (game_state == GS_RUNNING && global.input.pause) {
                game_state = GS_PAUSE_MENU;
            }

            // update controller assignments if a change was detected
            if (detect_game_controller_changes_and_update_state())
                assign_player_input_devices();

            // update map
            update_map(&map);

            // used to store players positions
            vec2 p1_pos_holder;
            vec2 p2_pos_holder;

            // update relative position of players and their
            // crosshairs (transform of the position on the screen,
            // using camera as a vector)
            if (SPLIT_SCREEN) // use left cam if screen is split
            {
                player_one->relative_position[0] = player_one->entity->body->aabb.position[0] + left_cam.position[0];
                player_one->relative_position[1] = player_one->entity->body->aabb.position[1] + left_cam.position[1];
            }
            else // otherwise use main cam TODO: perhaps make
                 // left_cam and main_cam the same object?
            {
                player_one->relative_position[0] = player_one->entity->body->aabb.position[0] + main_cam.position[0];
                player_one->relative_position[1] = player_one->entity->body->aabb.position[1] + main_cam.position[1];
            }

            // need to pass the RELATIVE position of the players
            // into the physics engine to properly detect collisions
            p1_pos_holder[0] = player_one->entity->body->aabb.position[0];
            p1_pos_holder[1] = player_one->entity->body->aabb.position[1];
            player_one->entity->body->aabb.position[0] = player_one->relative_position[0];
            player_one->entity->body->aabb.position[1] = player_one->relative_position[1];

            if (SPLIT_SCREEN) {
                player_two->relative_position[0] = player_two->entity->body->aabb.position[0] + right_cam.position[0];
                player_two->relative_position[1] = player_two->entity->body->aabb.position[1] + right_cam.position[1];

                p2_pos_holder[0] = player_two->entity->body->aabb.position[0];
                p2_pos_holder[1] = player_two->entity->body->aabb.position[1];
                player_two->entity->body->aabb.position[0] = player_two->relative_position[0];
                player_two->entity->body->aabb.position[1] = player_two->relative_position[1];
            }

            // update physics bodies
            if (game_state == GS_RUNNING)
                physics_update();

            // update the actual positions (saved value plus the
            // difference generated by the physics engine)
            player_one->entity->body->aabb.position[0] = p1_pos_holder[0] + (player_one->entity->body->aabb.position[0] - player_one->relative_position[0]);
            player_one->entity->body->aabb.position[1] = p1_pos_holder[1] + (player_one->entity->body->aabb.position[1] - player_one->relative_position[1]);
            if (SPLIT_SCREEN) {
                player_two->entity->body->aabb.position[0] = p2_pos_holder[0] + (player_two->entity->body->aabb.position[0] - player_two->relative_position[0]);
                player_two->entity->body->aabb.position[1] = p2_pos_holder[1] + (player_two->entity->body->aabb.position[1] - player_two->relative_position[1]);
            }

            set_render_dimensions(DEFAULT_RENDER_SCALE_FACTOR, false, true);

            // need to run render loop twice if we are actively
            // splitting the screen
            int player_count = SPLIT_SCREEN ? 2 : 1;
            for (int i = 0; i < player_count; i++) {
                // FIRST:
                // For the player being rendered, update render
                // dimensions based on player status, update the
                // corresponding projection matrix, update the
                // camera location, and clear the rendering
                // buffer to begin rendering THEN: handle the
                // corresponding inputs and update
                // statuses/directions must handle player input
                // BEFORE rendering because entities can be
                // created in `handle_player_shooting`
                if (SPLIT_SCREEN && i == 0) {
                    camera_update(player_one, &map);
                    render_begin_left();
                    if (game_state == GS_RUNNING)
                        player_per_frame_updates(player_one);
                }
                else if (SPLIT_SCREEN && i == 1) {
                    camera_update(player_two, &map);
                    render_begin_right();
                    if (game_state == GS_RUNNING)
                        player_per_frame_updates(player_two);
                }
                else // hit when screen is not being split
                {
                    camera_update(player_one, &map);
                    render_begin();
                    if (game_state == GS_RUNNING)
                        player_per_frame_updates(player_one);
                }

                // save aabb positions again
                p1_pos_holder[0] = player_one->entity->body->aabb.position[0];
                p1_pos_holder[1] = player_one->entity->body->aabb.position[1];

                if (SPLIT_SCREEN) {
                    p2_pos_holder[0] = player_two->entity->body->aabb.position[0];
                    p2_pos_holder[1] = player_two->entity->body->aabb.position[1];
                }

                // move all positions to relative position based
                // on camera except for the active player and
                // crosshairs
                if (SPLIT_SCREEN && i == 0) {
                    player_two->entity->body->aabb.position[0] = player_two->relative_position[0];
                    player_two->entity->body->aabb.position[1] = player_two->relative_position[1];
                    update_all_positions(&map, (vec2){-1 * left_cam.position[0], -1 * left_cam.position[1]}, true);
                }
                else if (SPLIT_SCREEN && i == 1) {
                    player_one->entity->body->aabb.position[0] = player_one->relative_position[0];
                    player_one->entity->body->aabb.position[1] = player_one->relative_position[1];
                    update_all_positions(&map, (vec2){-1 * right_cam.position[0], -1 * right_cam.position[1]}, false);
                }
                else // not split
                    update_all_positions(&map, (vec2){-1 * main_cam.position[0], -1 * main_cam.position[1]}, true);

                // render player's anims (characters + weapons)
                render_player_anims(player_one, window, texture_slots, game_color);
                if (SPLIT_SCREEN)
                    render_player_anims(player_two, window, texture_slots, game_color);

                // render all other animated entities
                render_all_non_player_entities_with_animations(window, texture_slots, game_color);

                // render map sprites
                for (int l = 0; l < map.num_props; l++) {
                    Prop prop = map.props[l];

                    /*
                     * Determining the props z_index based
                     * on position relative to player
                     * z_index should be below the players
                     * (0) if the lowest point of the player
                     * is under the y threshold we set OR
                     * they are above the prop entirely.
                     * Also the main background, (index 0)
                     * is rendered beneath the player no
                     * matter what
                     */
                    f32 player_y_min;
                    if (i == 0) { // rendering left side
                        player_y_min = player_one->entity->body->aabb.position[1] - player_one->entity->body->aabb.half_size[1];
                    }
                    else { // rendering right side (if it
                           // exists)
                        player_y_min = player_two->entity->body->aabb.position[1] - player_two->entity->body->aabb.half_size[1];
                    }
                    bool is_below_player = player_y_min < (prop.sprite->position[1] - prop.sprite->half_size[1] + prop.layer_threshold) ||
                                           player_y_min > (prop.sprite->position[1] + prop.sprite->half_size[1]) || l == 0;
                    i32 z_index = is_below_player ? prop.sprite->z_index : 1;
                    render_sprite_sheet_frame(
                        prop.sprite->sprite_sheet,
                        window,
                        prop.sprite->row,
                        prop.sprite->column,
                        prop.sprite->position,
                        z_index,
                        prop.sprite->is_flipped,
                        RENDER_PHYSICS_BODIES ? SEMI_TRANSPARENT : game_color,
                        texture_slots);

                    // render the static bodies
                    if (RENDER_PHYSICS_BODIES) {
                        for (int k = 0; k < prop.num_static_bodies; k++) {
                            render_aabb((f32 *)&prop.static_bodies[k]->aabb, WHITE);
                        }
                    }
                }

                // throw left side stuff into the rendering
                // buffer, without performing the screen swap
                // yet
                if (SPLIT_SCREEN && i == 0) {
                    render_end(window, texture_slots, false);
                }

                // update the physics bodies move all positions
                // back
                if (SPLIT_SCREEN && i == 0) {
                    update_all_positions(&map, left_cam.position, true);
                    player_two->entity->body->aabb.position[0] = p2_pos_holder[0];
                    player_two->entity->body->aabb.position[1] = p2_pos_holder[1];
                }
                else if (SPLIT_SCREEN && i == 1) {
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
            render_hud(window, texture_slots, game_color);

            // PAUSE MENU
            if (game_state == GS_PAUSE_MENU) {
                update_menu(pause_menu, global.input);
                render_pause_menu(window, texture_slots);
            }
            render_end(window, texture_slots, true);

            // destroy any entities that need to be destroyed:
            destroy_all_marked_entities(&map);
            update_entity_movements();

            break;
        case GS_EXITING:
            should_quit = true;
            break;
        default:
            printf("game state not specified");
        }

        time_update_late();
    }

    if (&map)
        free_map_attributes(&map);
    free_players();
    free_weapon_types();
    free_hud();
    free_menus();
    free_all_entities_and_clear_array_list();
    clear_animation_definition_list();
    clear_animation_list();
    SDL_Quit();
    return 0;
}
