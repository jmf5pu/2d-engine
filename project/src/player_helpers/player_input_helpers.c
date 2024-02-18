#include "../engine/input/input.h"
#include "../engine/render.h"
#include "player_helpers.h"

/// @brief Assigns a controller to each player. -1 indicates no associated controller
/// @param
void assign_player_input_devices(void)
{
    player_one->input_state->controller_id = open_controller_ids[0];
    if (SPLIT_SCREEN)
        player_two->input_state->controller_id = open_controller_ids[1];

    printf("player_one->controller_id: %d\n", player_one->input_state->controller_id);
    printf("player_two->controller_id: %d\n", player_two->input_state->controller_id);
}

/// @brief Updates the player's input state via controller sdl event. This updates the has_been_updated_this_frame flag in the struct. Can be called multiple times per frame (for
/// each controller event). If this is called on a given frame, update update_player_input_state_via_keyboard should not also be called on the same frame
/// @param player relevant player
/// @param event SDL_JOYBUTTONDOWN or SDL_JOYBUTTONUP sdl event
void update_player_input_state_via_controller(Player *player, SDL_Event *event)
{
    // SDL_GameController* controller = SDL_GameControllerOpen(0);
    // char* mappingString = SDL_GameControllerMapping(controller);
    // printf("Controller Mapping:\n%s\n", mappingString);
    // SDL_free(mappingString);

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
    
    player->input_state->has_been_updated_this_frame = true;
}

/// @brief Updates the player's input state via keyboard inputs. This will only be called on a given frame if has_been_updated_this_frame is false
/// @param player the relevant player
void update_player_input_state_via_keyboard(Player *player) {}

/// @brief Update the menu input state struct. Menu input states are only modified by the keyboard inputs
/// @param menu_input_state
void update_menu_input_state(Menu_Input_State menu_input_state)
{
    // TODO: Pull keyboard inputs
}