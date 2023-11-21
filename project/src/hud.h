#ifndef HUD_H
#define HUD_H

#include "structs.h"
#include "engine/render.h"

extern HUD *hud;

void init_hud(SDL_Window *window);
void render_hud();
void free_hud(void);

#endif