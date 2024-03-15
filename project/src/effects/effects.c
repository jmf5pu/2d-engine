#include "effects.h"

void init_effect_adefs(void)
{
    render_sprite_sheet_init(&sprite_sheet_brass_falling_1, "assets/wip/brass_falling_1.png", 3, 3);
    adef_brass_falling_1 = animation_definition_create(&sprite_sheet_brass_falling_1, (f32[]){0.01, 0.01, 0.01, 0.01}, (u8[]){0, 0, 0, 0}, (u8[]){0, 1, 2, 3}, 4);
}

void init_effects(void) { init_effect_adefs(); }