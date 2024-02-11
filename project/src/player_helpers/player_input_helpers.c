#include "../engine/input/input.h"
#include "../engine/render.h"
#include "player_helpers.h"

/// @brief Assigns a controller to each player. -1 indicates no associated controller
/// @param
void assign_player_input_devices(void)
{
    player_one->controller_id = open_controller_ids[0];
    if (SPLIT_SCREEN)
        player_two->controller_id = open_controller_ids[1];

    printf("player_one->controller_id: %d\n", player_one->controller_id);
    printf("player_two->controller_id: %d\n", player_two->controller_id);
}

/// @brief Updates the input state for the provided player, if a controller is associated with this player, those inputs will take precedence over keyboard inputs. Keyboard inputs
/// are always assocaited with the left side player
/// @param player
void update_player_input_state(Player *player)
{
    if (player->controller_id != -1) {
        // TODO: Pull controller inputs here
    }
    else if (player->is_left_player) {
        // TODO: Pull keyboard inputs
    }
    else {
        // TODO: Update player statust to indicate controller needs to be plugged in
    }
}

/// @brief Update the menu input state struct. Menu input states are only modified by the keyboard inputs
/// @param menu_input_state
void update_menu_input_state(Menu_Input_State menu_input_state)
{
    // TODO: Pull keyboard inputs
}