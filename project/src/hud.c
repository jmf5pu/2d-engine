#include "hud.h"

HUD *hud;

// initializes heads up display
void init_hud(SDL_Window *window)
{
    // init left side of the hud
    hud = malloc(sizeof(HUD));
    hud->window = window;

    // init right side of the hud (if there is a second player)
    if (SPLIT_SCREEN)
    {
    }
}

// renders the heads up display (should be called once per frame)
// void render_hud()
// {
//     // render health displays
//     render_sprite_sheet_frame(prop.sprite->sprite_sheet, window, prop.sprite->row, prop.sprite->column, prop.sprite->position, z_index, prop.sprite->is_flipped, RENDER_PHYSICS_BODIES ? (vec4){0.9, 0.9, 0.9, 0.9} : prop.sprite->color, texture_slots);
// }

// frees the dynamic hud memory
void free_hud(void)
{
    if (hud)
        free(hud);
}