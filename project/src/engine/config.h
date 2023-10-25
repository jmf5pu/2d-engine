#ifndef CONFIG_H
#define CONFIG_H

#include "input.h"
#include "types.h"

typedef struct config
{
    u8 keybinds[13];
} Config_State;

void config_init(void);
void config_key_bind(Input_Key key, const char *key_name);

#endif