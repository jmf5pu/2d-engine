#ifndef INPUT_H
#define INPUT_H

#include "../types.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_CONTROLLERS 2
#define JOYSTICK_DEADZONE_THRESHOLD 0.1

SDL_JoystickID open_controller_ids[MAX_CONTROLLERS];

typedef enum input_key {
    INPUT_KEY_UP,
    INPUT_KEY_DOWN,
    INPUT_KEY_LEFT,
    INPUT_KEY_RIGHT,
    INPUT_KEY_SHOOT,
    INPUT_KEY_RELOAD,
    INPUT_KEY_USE,
    INPUT_KEY_PAUSE,
} Input_Key;

typedef enum key_state { KS_UNPRESSED, KS_PRESSED, KS_HELD } Key_State;

typedef struct menu_input_state {
    Key_State select;
    Key_State up;
    Key_State down;
    Key_State escape;
} Menu_Input_State;

typedef struct joystick_state {
    float x_axis;
    float y_axis;
} Joystick_State;

typedef struct controller_button_state {
    Key_State left_trigger;
    Key_State left_bumper;
    Key_State right_trigger;
    Key_State right_bumper;
    Key_State left_joystick;
    Key_State right_joystick;
    Key_State dpad_up;
    Key_State dpad_down;
    Key_State dpad_left;
    Key_State dpad_right;
    Key_State y_button;
    Key_State a_button;
    Key_State x_button;
    Key_State b_button;
    Key_State menu_button;
    Key_State view_button;
    Key_State share_button;
} Controller_Button_State;

typedef struct controller_input_state {
    SDL_JoystickID controller_id; // controller id associated last associated with these inputs, defaults to -1
    Joystick_State left_joystick_state;
    Joystick_State right_joystick_state;
    Controller_Button_State button_state;
} Controller_Input_State;

typedef struct input_state {
    Key_State left;
    Key_State right;
    Key_State up;
    Key_State down;
    Key_State shoot;
    Key_State reload;
    Key_State use;
    Key_State pause;
} Input_State;

void update_bound_key_states(void);

// controller methods
void init_game_controllers(void);
bool detect_game_controller_changes_and_update_state(void);
bool joystick_ids_are_identical(SDL_JoystickID first_guid, SDL_JoystickID second_guid);
float get_normalized_joystick_axis(int16_t axis);
void update_key_state(u8 current_state, Key_State *key_state);

#endif