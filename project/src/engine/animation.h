#ifndef ANIMATION_H
#define ANIMATION_H

#include "render.h"

#define MAX_FRAMES 64

typedef struct animation_frame {
    f32 duration;
    u8 row;
    u8 column;
} Animation_Frame;

typedef struct animation_definition {
    Sprite_Sheet *sprite_sheet;
    Animation_Frame frames[MAX_FRAMES];
    u8 frame_count;
} Animation_Definition;

typedef struct animation {
    Animation_Definition *animation_definition;
    f32 current_frame_time;
    u8 current_frame_index;
    bool does_loop;
    bool is_active;
    bool is_flipped;
} Animation;

void animation_init(void);
Animation_Definition *animation_definition_create(Sprite_Sheet *sprite_sheet, f32 *durations, u8 *rows, u8 *columns, u8 frame_count);
Animation *animation_create(Animation_Definition *adef, bool does_loop);
void animation_destroy(usize id);
Animation *animation_get(usize id);
void animation_update(f32 dt);
void animation_render(Animation *animation, SDL_Window *window, vec2 position, i32 z_index, vec4 color, u32 texture_slots[32]);

#endif