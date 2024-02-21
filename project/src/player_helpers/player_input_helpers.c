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

    printf("player_one->controller_id: %d\n", player_one->input_state->controller_input_state->controller_id);
    printf("player_two->controller_id: %d\n", player_two->input_state->controller_input_state->controller_id);
}

/// @brief Updates the player's input state via controller sdl event. This updates the input_updated_this_frame flag in the struct. Can be called multiple times per frame (for
/// each controller event). If this is called on a given frame, update update_player_input_state_via_keyboard should not also be called on the same frame
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

    player->input_state->input_updated_this_frame = true;
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
    printf("joystick state left x: %f\n", player->input_state->controller_input_state->left_joystick_state.x_axis);
    printf("joystick state left y: %f\n", player->input_state->controller_input_state->left_joystick_state.y_axis);
    printf("joystick state right x: %f\n", player->input_state->controller_input_state->right_joystick_state.x_axis);
    printf("joystick state right y: %f\n", player->input_state->controller_input_state->right_joystick_state.y_axis);
}

/// @brief Updates the player's input state via keyboard inputs. This will only be called on a given frame if input_updated_this_frame is false
/// @param player the relevant player
void update_player_input_state_via_keyboard(Player *player) {}

/// @brief Update the menu input state struct. Menu input states are only modified by the keyboard inputs
/// @param menu_input_state
void update_menu_input_state(Menu_Input_State menu_input_state)
{
    // TODO: Pull keyboard inputs
}