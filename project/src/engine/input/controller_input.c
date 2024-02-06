#include "../util.h"
#include "input.h"

#define MAX_CONTROLLERS 2

static SDL_JoystickGUID controller_guids[MAX_CONTROLLERS];

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
/// previous frame
/// @param
/// @return returns true if a change in controllers/joysticks was detected from
/// the previous frame. Otherwise returns false
bool game_controller_change_detected(void)
{
    bool game_controller_change_detected = false;
    int num_joysticks = SDL_NumJoysticks();

    for (int i = 0; i < MAX_CONTROLLERS; i++) {
        SDL_JoystickGUID device_guid = SDL_JoystickGetDeviceGUID(i);
        if (!joystick_guids_are_identical(controller_guids[i], device_guid)) {
            controller_guids[i] = device_guid;
            game_controller_change_detected = true;
        }
    }

    return game_controller_change_detected;
}

bool joystick_guids_are_identical(
    SDL_JoystickGUID first_guid, SDL_JoystickGUID second_guid)
{
    return SDL_memcmp(&first_guid, &second_guid, sizeof(SDL_JoystickGUID)) == 0;
}