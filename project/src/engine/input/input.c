#include "../input.h"
#include "../global.h"
#include "../types.h"

static void update_key_state(u8 current_state, Key_State *key_state)
{
    if (current_state)
    {
        if (*key_state > 0)
        {
            *key_state = KS_HELD;
        }
        else
        {
            *key_state = KS_PRESSED;
        }
    }
    else
    {
        *key_state = KS_UNPRESSED;
    }
}

void input_update()
{
    const u8 *keyboard_state = SDL_GetKeyboardState(NULL);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_L_LEFT]], &global.input.l_left);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_L_RIGHT]], &global.input.l_right);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_L_UP]], &global.input.l_up);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_L_DOWN]], &global.input.l_down);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_L_SHOOT]], &global.input.l_shoot);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_R_LEFT]], &global.input.r_left);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_R_RIGHT]], &global.input.r_right);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_R_UP]], &global.input.r_up);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_R_DOWN]], &global.input.r_down);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_R_SHOOT]], &global.input.r_shoot);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_ESCAPE]], &global.input.escape);
}