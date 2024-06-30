#ifndef RENDER_H
#define RENDER_H

#define SPLIT_SCREEN false
#define RENDER_PHYSICS_BODIES false
#define RENDER_FULLSCREEN false
#define DEFAULT_RENDER_SCALE_FACTOR 0.25
#define FRAME_RATE 60

#define BATCH_SIZE 32
#define MAX_BATCH_VERTICES 40000
#define MAX_BATCH_ELEMENTS 60000

#include "physics.h"
#include <SDL2/SDL.h>
#include <linmath.h>
#include <stdbool.h>

#include "types.h"

// defined in render.c
extern f32 window_width;
extern f32 window_height;
extern f32 render_width;
extern f32 render_height;

typedef struct batch_vertex {
    vec2 position;
    vec2 uvs;
    vec4 color;
    f32 texture_slot;
    i32 z_index;
    u32 quad_id;    // Identifier of the quad
    u32 vertex_idx; // Index of the vertex within the quad (0 to 3)
} Batch_Vertex;

typedef struct quad_vertices {
    Batch_Vertex *v1;
    Batch_Vertex *v2;
    Batch_Vertex *v3;
    Batch_Vertex *v4;
    i32 z_index;
} Quad_Vertices;

typedef struct sprite_sheet {
    f32 width;
    f32 height;
    f32 cell_width;
    f32 cell_height;
    u32 texture_id;
} Sprite_Sheet;

typedef struct sprite_sheet_frame {
    Sprite_Sheet *sprite_sheet;
    f32 row;
    f32 column;
    vec2 position; // 2d position
    vec2 half_size;
    i32 z_index; // for layering sprites
    bool is_flipped;
    vec4 color;
} Sprite_Sheet_Frame;

SDL_Window *render_init(void);
void set_render_dimensions(f32 scale_factor, bool rendering_hud, bool update_shaders);
void render_begin(void);
void render_begin_left(void);
void render_begin_right(void);
void render_end(SDL_Window *window, u32 batch_texture_ids[32], bool swap_window);
void render_quad(vec2 pos, vec2 state, vec4 color);
void render_line_segment(vec2 start, vec2 end, vec4 color);
void render_quad_line(vec2 pos, vec2 size, vec4 color);
void render_aabb(AABB *aabb, vec4 color);
f32 render_get_scale();

void render_sprite_sheet_init(Sprite_Sheet *sprite_sheet, const char *path, f32 cell_width, f32 cell_height);
void render_sprite_sheet_frame(
    Sprite_Sheet *sprite_sheet, SDL_Window *window, f32 row, f32 column, vec2 position, i32 z_index, bool is_flipped, vec4 color, u32 texture_slots[BATCH_SIZE]);

#endif