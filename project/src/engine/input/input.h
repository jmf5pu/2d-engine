#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define MAX_CONTROLLERS 2

SDL_JoystickID open_controller_ids[MAX_CONTROLLERS];

typedef enum input_key {
    INPUT_KEY_L_LEFT,
    INPUT_KEY_L_RIGHT,
    INPUT_KEY_L_UP,
    INPUT_KEY_L_DOWN,
    INPUT_KEY_L_SHOOT,
    INPUT_KEY_L_CROUCH,
    INPUT_KEY_L_RELOAD,
    INPUT_KEY_R_LEFT,
    INPUT_KEY_R_RIGHT,
    INPUT_KEY_R_UP,
    INPUT_KEY_R_DOWN,
    INPUT_KEY_R_SHOOT,
    INPUT_KEY_R_CROUCH,
    INPUT_KEY_R_RELOAD,
    INPUT_KEY_ESCAPE,
    INPUT_KEY_UP,
    INPUT_KEY_DOWN,
    INPUT_KEY_LEFT,
    INPUT_KEY_RIGHT,
    INPUT_KEY_ENTER,
} Input_Key;

typedef enum key_state { KS_UNPRESSED, KS_PRESSED, KS_HELD } Key_State;

typedef struct input_state {
    // left player key states
    Key_State escape;
    Key_State l_left;
    Key_State l_right;
    Key_State l_up;
    Key_State l_down;
    Key_State l_shoot;
    Key_State l_crouch;
    Key_State l_reload;
    // right player key states
    Key_State r_left;
    Key_State r_right;
    Key_State r_up;
    Key_State r_down;
    Key_State r_shoot;
    Key_State r_crouch;
    Key_State r_reload;
    // menu controls
    Key_State up;
    Key_State down;
    Key_State left;
    Key_State right;
    Key_State enter;
} Input_State;

void input_update(void);

// controller methods
void init_game_controllers(void);
bool detect_game_controller_changes_and_update_state(void);
bool joystick_ids_are_identical(
    SDL_JoystickID first_guid, SDL_JoystickID second_guid);

#endif