#include "../util.h"
#include "input.h"

#define MAX_CONTROLLERS 2

static SDL_JoystickID controller_joystick_ids[MAX_CONTROLLERS];

/// @brief one time game controller setup, call SDL_Init and enable related
/// event states so we don't have to call update methods manually
/// @param
void init_game_controllers(void)
{
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
        ERROR_EXIT("Could not init SDL: %s\n", SDL_GetError());
    }

    SDL_JoystickEventState(SDL_ENABLE);
    SDL_GameControllerEventState(SDL_ENABLE);
}

/// @brief compares current game controllers/joysticks with the ones from the
/// previous frame. Closes old joysticks and opens new ones.
/// @param
/// @return returns true if a change in controllers/joysticks was detected from
/// the previous frame. Otherwise returns false
bool detect_game_controller_changes_and_update_state(void)
{
    bool game_controller_change_detected = false;
    int num_joysticks = SDL_NumJoysticks();

    for (int i = 0; i < MAX_CONTROLLERS; i++) {
        SDL_JoystickID device_joystick_id = SDL_JoystickGetDeviceInstanceID(i);
        if (!joystick_ids_are_identical(
                controller_joystick_ids[i], device_joystick_id)) {
            SDL_Joystick *old_joystick =
                SDL_JoystickFromInstanceID(controller_joystick_ids[i]);
            SDL_JoystickClose(old_joystick);
            SDL_JoystickOpen(i);
            controller_joystick_ids[i] = device_joystick_id;
            game_controller_change_detected = true;
        }
    }

    return game_controller_change_detected;
}

bool joystick_ids_are_identical(
    SDL_JoystickID first_guid, SDL_JoystickID second_guid)
{
    return SDL_memcmp(&first_guid, &second_guid, sizeof(SDL_JoystickID)) == 0;
}