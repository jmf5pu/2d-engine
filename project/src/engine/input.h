#ifndef INPUT_H
#define INPUT_H

typedef enum input_key
{
    INPUT_KEY_L_LEFT,
    INPUT_KEY_L_RIGHT,
    INPUT_KEY_L_UP,
    INPUT_KEY_L_DOWN,
    INPUT_KEY_L_SHOOT,
    INPUT_KEY_R_LEFT,
    INPUT_KEY_R_RIGHT,
    INPUT_KEY_R_UP,
    INPUT_KEY_R_DOWN,
    INPUT_KEY_R_SHOOT,
    INPUT_KEY_ESCAPE
} Input_Key;

typedef enum key_state
{
    KS_UNPRESSED,
    KS_PRESSED,
    KS_HELD
} Key_State;

typedef struct input_state
{
    Key_State escape;
    Key_State l_left;
    Key_State l_right;
    Key_State l_up;
    Key_State l_down;
    Key_State l_shoot;
    Key_State r_left;
    Key_State r_right;
    Key_State r_up;
    Key_State r_down;
    Key_State r_shoot;
} Input_State;

void input_update(void);

#endif