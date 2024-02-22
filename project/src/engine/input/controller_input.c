#include "../util.h"
#include "input.h"

/// @brief one time game controller setup, call SDL_Init and enable related
/// event states so we don't have to call update methods manually. Also
/// initializes open_controller_ids array
/// @param
void init_game_controllers(void)
{
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
        ERROR_EXIT("Could not init SDL: %s\n", SDL_GetError());
    }

    SDL_JoystickEventState(SDL_ENABLE);
    SDL_GameControllerEventState(SDL_ENABLE);

    for (int i = 0; i < MAX_CONTROLLERS; i++) {
        open_controller_ids[i] = -1;
    }
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
        if (i < num_joysticks) {
            SDL_JoystickID device_joystick_id = SDL_JoystickGetDeviceInstanceID(i);
            if (!joystick_ids_are_identical(open_controller_ids[i], device_joystick_id)) {
                SDL_GameController *old_joystick = SDL_GameControllerFromInstanceID(open_controller_ids[i]);
                SDL_GameControllerClose(old_joystick);
                SDL_GameControllerOpen(i);
                open_controller_ids[i] = device_joystick_id;
                game_controller_change_detected = true;
            }
        }
        else {
            open_controller_ids[i] = -1; // assign default value of -1 to slots with no associated
                                         // joystick/controller
        }
    }

    return game_controller_change_detected;
}

bool joystick_ids_are_identical(SDL_JoystickID first_guid, SDL_JoystickID second_guid) { return SDL_memcmp(&first_guid, &second_guid, sizeof(SDL_JoystickID)) == 0; }

/// @brief normalizes a joystick axis by converting the 16 bit signed int into a float representation between 0 and 1. Rounds off values close to 0 to 0 for when the controller
/// joystick is near center
/// @param axis
/// @return normalized float representation of the axis input
float get_normalized_joystick_axis(int16_t axis)
{
    float normalized_axis = axis / 32767.0f;
    return fabs(normalized_axis) > JOYSTICK_DEADZONE_THRESHOLD ? normalized_axis : 0.0f;
}