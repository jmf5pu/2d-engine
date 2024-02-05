#include "../config.h"
#include "../global.h"
#include "../input/input.h"
#include "../io.h"
#include "../util.h"

static const char *CONFIG_DEFAULT = "[controls]\n"
                                    "l_left = A\n"
                                    "l_right = D\n"
                                    "l_up = W\n"
                                    "l_down = S\n"
                                    "l_shoot = Space\n"
                                    "l_crouch = Left Ctrl\n"
                                    "l_reload = R\n"
                                    "r_left = J\n"
                                    "r_right = L\n"
                                    "r_up = I\n"
                                    "r_down = K\n"
                                    "r_shoot = ,\n"
                                    "r_crouch = N\n"
                                    "r_reload = P\n"
                                    "menu_up = Up\n"
                                    "menu_down = Down\n"
                                    "menu_left = Left\n"
                                    "menu_right = Right\n"
                                    "escape = Escape\n"
                                    "enter = Return\n";

static char tmp_buffer[20] = {
    0}; // must be able to hold the longest line in config.ini

static char *config_get_value(const char *config_buffer, const char *value)
{
    char *line = strstr(config_buffer, value);
    if (!line) {
        ERROR_EXIT(
            "Could not find config value: %s. Try deleting config.ini "
            "and restarting.\n",
            value);
    }

    size_t len = strlen(line);
    char *end = line + len;

    char *curr = line;
    char *tmp_ptr = &tmp_buffer[0];
    // Move pointer to '='
    while (*curr != '=' && curr != end) {
        ++curr;
    }
    // Consume '='
    ++curr;
    // Consume any spaces.
    while (*curr == ' ') {
        ++curr;
    }
    // Get characters until the end of the line
    while (*curr != '\n' && *curr != 0 && curr != end) {
        *tmp_ptr++ = *curr++;
    }

    *tmp_ptr = '\0'; // null terminate char *

    return tmp_buffer;
}

static void load_controls(const char *config_buffer)
{
    // left player keybinds
    config_key_bind(
        INPUT_KEY_L_LEFT, config_get_value(config_buffer, "l_left"));
    config_key_bind(
        INPUT_KEY_L_RIGHT, config_get_value(config_buffer, "l_right"));
    config_key_bind(INPUT_KEY_L_UP, config_get_value(config_buffer, "l_up"));
    config_key_bind(
        INPUT_KEY_L_DOWN, config_get_value(config_buffer, "l_down"));
    config_key_bind(
        INPUT_KEY_L_SHOOT, config_get_value(config_buffer, "l_shoot"));
    config_key_bind(
        INPUT_KEY_L_CROUCH, config_get_value(config_buffer, "l_crouch"));
    config_key_bind(
        INPUT_KEY_L_RELOAD, config_get_value(config_buffer, "l_reload"));

    // right player keybinds
    config_key_bind(
        INPUT_KEY_R_LEFT, config_get_value(config_buffer, "r_left"));
    config_key_bind(
        INPUT_KEY_R_RIGHT, config_get_value(config_buffer, "r_right"));
    config_key_bind(INPUT_KEY_R_UP, config_get_value(config_buffer, "r_up"));
    config_key_bind(
        INPUT_KEY_R_DOWN, config_get_value(config_buffer, "r_down"));
    config_key_bind(
        INPUT_KEY_R_SHOOT, config_get_value(config_buffer, "r_shoot"));
    config_key_bind(
        INPUT_KEY_R_CROUCH, config_get_value(config_buffer, "r_crouch"));
    config_key_bind(
        INPUT_KEY_R_RELOAD, config_get_value(config_buffer, "r_reload"));

    // menu inputs
    config_key_bind(INPUT_KEY_UP, config_get_value(config_buffer, "menu_up"));
    config_key_bind(
        INPUT_KEY_DOWN, config_get_value(config_buffer, "menu_down"));
    config_key_bind(
        INPUT_KEY_LEFT, config_get_value(config_buffer, "menu_left"));
    config_key_bind(
        INPUT_KEY_RIGHT, config_get_value(config_buffer, "menu_right"));
    config_key_bind(
        INPUT_KEY_ESCAPE, config_get_value(config_buffer, "escape"));
    config_key_bind(INPUT_KEY_ENTER, config_get_value(config_buffer, "enter"));
}

static int config_load(void)
{
    File file_config = io_file_read("./config.ini");
    if (!file_config.is_valid) {
        return 1;
    }

    load_controls(file_config.data);

    free(file_config.data);

    return 0;
}

void config_init(void)
{
    if (config_load() == 0) {
        return;
    }

    io_file_write(
        (void *)CONFIG_DEFAULT, strlen(CONFIG_DEFAULT), "./config.ini");

    if (config_load() != 0) {
        ERROR_EXIT("Could not create or load config file.\n");
    }
}
void config_key_bind(Input_Key key, const char *key_name)
{
    SDL_Scancode scan_code = SDL_GetScancodeFromName(key_name);
    if (scan_code == SDL_SCANCODE_UNKNOWN) {
        printf("ERROR: Invalid scan code when binding key: %s\n", key_name);
        return;
    }

    global.config.keybinds[key] = scan_code;
}