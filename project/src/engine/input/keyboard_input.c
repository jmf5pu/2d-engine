#include "../global.h"
#include "../types.h"
#include "input.h"

static void update_key_state(u8 current_state, Key_State *key_state)
{
    if (current_state) {
        if (*key_state > 0) {
            *key_state = KS_HELD;
        }
        else {
            *key_state = KS_PRESSED;
        }
    }
    else {
        *key_state = KS_UNPRESSED;
    }
}

void update_bound_key_states(void)
{
    const u8 *keyboard_state = SDL_GetKeyboardState(NULL);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_UP]], &global.input.up);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_DOWN]], &global.input.down);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_LEFT]], &global.input.left);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_RIGHT]], &global.input.right);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_SHOOT]], &global.input.shoot);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_RELOAD]], &global.input.reload);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_USE]], &global.input.use);
    update_key_state(keyboard_state[global.config.keybinds[INPUT_KEY_PAUSE]], &global.input.pause);
}
