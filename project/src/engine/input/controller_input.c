#include "input.h"
#include <SDL2/SDL.h>

void update_joysticks_and_print(void)
{
    SDL_JoystickEventState(SDL_ENABLE);
    SDL_JoystickUpdate();
    int num_joysticks = SDL_NumJoysticks();
    printf("%d\n", num_joysticks);
}