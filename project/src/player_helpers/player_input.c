#include "../engine/input/input.h"
#include "../engine/render.h"
#include "player_helpers.h"

/// @brief Assigns a controller to each player. -1 indicates no associated controller
/// @param
void assign_player_input_devices(void)
{
    player_one->input_state->controller_input_state->controller_id = open_controller_ids[0];
    if (SPLIT_SCREEN)
        player_two->input_state->controller_input_state->controller_id = open_controller_ids[1];
}

/// @brief Always pull the controller inputs (if they exists) to update the players keystates. If we are looking at player one (left player), always override with keyboard inputs
/// if they exist
/// @param player
void handle_player_input(Player *player)
{
    update_player_input_state_from_joysticks(player);
    if (player->is_left_player) {
        update_player_input_state_from_keyboard(player);
    }

    apply_player_joystick_movement(player);
    apply_player_input_state(player);
}

/// @brief Updates the player's input state via controller sdl event. Can be called multiple times per frame (for
/// each controller event). If this is called on a given frame, update update_player_input_state_from_keyboard should not also be called on the same frame
/// @param player relevant player
/// @param event SDL_JOYBUTTONDOWN or SDL_JOYBUTTONUP sdl event
void update_player_input_state_via_controller(Player *player, SDL_Event *event)
{
    printf("event cbutton.button: %d\n", event->cbutton.button);
    switch (event->cbutton.button) {
    case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
        printf("trigger\n");
        break;
    case SDL_CONTROLLER_BUTTON_A:
        printf("A\n");
        break;
    case SDL_CONTROLLER_BUTTON_B:
        printf("B\n");
        break;
    case SDL_CONTROLLER_BUTTON_X:
        printf("X\n");
        break;
    case SDL_CONTROLLER_BUTTON_Y:
        printf("Y\n");
        break;
    }
}

/// @brief Checks for joystick movements and updates the player's input state accordingly. Called once per frame for each player
void update_player_input_state_from_joysticks(Player *player)
{
    if (player->input_state->controller_input_state->controller_id != -1) {
        SDL_GameController *controller = SDL_GameControllerFromInstanceID(player->input_state->controller_input_state->controller_id);

        // Update left joystick axes
        player->input_state->controller_input_state->left_joystick_state.x_axis = get_normalized_joystick_axis(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX));
        player->input_state->controller_input_state->left_joystick_state.y_axis = get_normalized_joystick_axis(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY));

        // Update right joystick axes
        player->input_state->controller_input_state->right_joystick_state.x_axis = get_normalized_joystick_axis(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTX));
        player->input_state->controller_input_state->right_joystick_state.y_axis = get_normalized_joystick_axis(SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_RIGHTY));
    }
}

/// @brief Updates the player's input state via keyboard inputs
/// @param player the relevant player
void update_player_input_state_from_keyboard(Player *player)
{
    player->input_state->key_state->up = global.input.up;
    player->input_state->key_state->down = global.input.down;
    player->input_state->key_state->left = global.input.left;
    player->input_state->key_state->right = global.input.right;
    player->input_state->key_state->shoot = global.input.shoot;
    player->input_state->key_state->reload = global.input.reload;
    player->input_state->key_state->use = global.input.use;
    player->input_state->key_state->pause = global.input.pause;
}

/// @brief Update the menu input state struct. Menu input states are only modified by the keyboard inputs
/// @param menu_input_state
void update_menu_input_state(Menu_Input_State menu_input_state)
{
    // TODO: Pull keyboard inputs
}