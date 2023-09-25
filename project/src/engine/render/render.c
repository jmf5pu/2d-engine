#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../array_list.h"
#include "../global.h"
#include "../render.h"
#include "../util.h"
#include "render_internal.h"

static usize quad_id_counter = 0;
static f32 render_width = WINDOW_WIDTH * 0.25; // TODO: different if not split_screen
static f32 render_height = WINDOW_HEIGHT * 0.5;
static f32 scale = 2; // TODO: change this based on screen size

static u32 vao_quad;
static u32 vbo_quad;
static u32 ebo_quad;
static u32 vao_line;
static u32 vbo_line;
static u32 shader_default;
static u32 texture_color;
static u32 vao_batch;
static u32 vbo_batch;
static u32 ebo_batch;
static u32 shader_batch;
static Array_List *list_batch;

SDL_Window *render_init(void)
{
    SDL_Window *window = render_init_window(WINDOW_WIDTH, WINDOW_HEIGHT);

    render_init_quad(&vao_quad, &vbo_quad, &ebo_quad);
    render_init_batch_quads(&vao_batch, &vbo_batch, &ebo_batch);
    render_init_line(&vao_line, &vbo_line);
    render_init_shaders(&shader_default, &shader_batch, render_width, render_height);
    render_init_color_texture(&texture_color);

    // create transparency / semi transparent effect
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    list_batch = array_list_create(sizeof(Batch_Vertex *), 32);

    stbi_set_flip_vertically_on_load(1);

    return window;
}

// checks if texture id is already present in texture slots array (for reuse)
static i32 find_texture_slot(u32 texture_slots[32], u32 texture_id)
{
    // 1 - 8 because 0 is the reserved for the texture slot
    for (i32 i = 1; i < 32; ++i)
    {
        if (texture_slots[i] == texture_id)
        {
            return i;
        }
    }

    return -1;
}

// checks if texture id is already in use or an open slot is present, if so, returns index, returns -1 if buffer is full
static i32 try_insert_texture(u32 texture_slots[32], u32 texture_id)
{
    i32 index = find_texture_slot(texture_slots, texture_id);
    if (index > 0)
    {
        return index;
    }

    // 1 - 8 because 0 is the reserved for the texture slot
    for (i32 i = 1; i < 32; ++i)
    {
        if (texture_slots[i] == 0)
        {
            texture_slots[i] = texture_id;
            return i;
        }
    }

    return -1;
}

// used to sort by z_index. Compares z_index first, then quad_id, and finally vertex_idx to maintain ordering within quads
static int compare_vertices(const void *a, const void *b)
{
    const Batch_Vertex *vertex_a = *(const Batch_Vertex **)a;
    const Batch_Vertex *vertex_b = *(const Batch_Vertex **)b;

    if (vertex_a->z_index != vertex_b->z_index)
        return (vertex_a->z_index > vertex_b->z_index) - (vertex_a->z_index < vertex_b->z_index);
    if (vertex_a->quad_id != vertex_b->quad_id)
        return (vertex_a->quad_id > vertex_b->quad_id) - (vertex_a->quad_id < vertex_b->quad_id);
    return (vertex_a->vertex_idx > vertex_b->vertex_idx) - (vertex_a->vertex_idx < vertex_b->vertex_idx);
}

void render_begin(void)
{
    glClearColor(0.88, 0.1, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    list_batch->len = 0; // clears batch vertices buffer
}

void render_begin_left(void)
{
    glClearColor(0.88, 0.1, 0.1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    list_batch->len = 0; // clears batch vertices buffer from previous frame
    glViewport(0, 0, WINDOW_WIDTH * 0.5, WINDOW_HEIGHT);
}

void render_begin_right(void)
{
    list_batch->len = 0;
    glViewport(WINDOW_WIDTH * 0.5, 0, WINDOW_WIDTH * 0.5, WINDOW_HEIGHT);
}

static void render_batch(Batch_Vertex *vertices, usize count, u32 texture_ids[32])
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo_batch);
    // Iterate through the list_batch array list and access each Batch_Vertex instance

    qsort(list_batch->items, list_batch->len, sizeof(Batch_Vertex *), compare_vertices);

    // Calculate the total size required for copying all Batch_Vertex instances
    usize total_size = list_batch->len * sizeof(Batch_Vertex);

    // Allocate memory for a new contiguous buffer to hold all Batch_Vertex instances
    void *vertex_data = malloc(total_size);
    if (!vertex_data)
    {
        // TODO: Handle memory allocation error
        // ...
    }

    // Copy all Batch_Vertex instances' data into the new contiguous buffer
    u8 *destination = (u8 *)vertex_data;
    for (usize i = 0; i < list_batch->len; ++i)
    {
        Batch_Vertex *vertex = array_list_get(list_batch, i, "in render_batch");
        memcpy(destination, vertex, sizeof(Batch_Vertex));
        destination += sizeof(Batch_Vertex);
    }
    // Use glBufferSubData to copy the entire buffer to OpenGL
    glBufferSubData(GL_ARRAY_BUFFER, 0, total_size, vertex_data);

    // Free the allocated memory for the new buffer
    free(vertex_data);

    // bind color texture (always index 0 in texture_ids)
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_color);

    // bind 8 textures at a time
    for (u32 i = 1; i < 32; ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, texture_ids[i]);
    }

    glUseProgram(shader_batch);
    glBindVertexArray(vao_batch);

    glDrawElements(GL_TRIANGLES, (count >> 2) * 6, GL_UNSIGNED_INT, NULL);
}

void render_end(SDL_Window *window, u32 batch_texture_ids[32], bool swap_window)
{
    render_batch(list_batch->items, list_batch->len, batch_texture_ids);
    if (swap_window)
        SDL_GL_SwapWindow(window); // updates opengl window
    glDisable(GL_SCISSOR_TEST);
}

void render_quad(vec2 pos, vec2 size, vec4 color)
{
    glUseProgram(shader_default);

    mat4x4 model;
    mat4x4_identity(model);

    mat4x4_translate(model, pos[0], pos[1], 0);
    mat4x4_scale_aniso(model, model, size[0], size[1], 1);

    glUniformMatrix4fv(glGetUniformLocation(shader_default, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform4fv(glad_glGetUniformLocation(shader_default, "color"), 1, color);

    glBindVertexArray(vao_quad);

    glBindTexture(GL_TEXTURE_2D, texture_color);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

    glBindVertexArray(0);
}

static void append_quad(vec2 position, vec2 size, vec4 texture_coordinates, i32 z_index, vec4 color, f32 texture_slot)
{
    vec4 uvs = {0, 0, 1, 1};

    if (texture_coordinates != NULL)
    {
        memcpy(uvs, texture_coordinates, sizeof(vec4));
    }

    // Allocate memory for the Batch_Vertex instances
    Batch_Vertex *vertices[4];
    for (int i = 0; i < 4; ++i)
    {
        vertices[i] = malloc(sizeof(Batch_Vertex));
        if (!vertices[i])
        {
            ERROR_RETURN(NULL, "Could not allocate memory for vertices\n");
        }
    }

    usize quad_id = quad_id_counter++;

    // Initialize and append each vertex to the list_batch
    *vertices[0] = (Batch_Vertex){
        .position = {position[0], position[1]},
        .uvs = {uvs[0], uvs[1]},
        .color = {color[0], color[1], color[2], color[3]},
        .texture_slot = texture_slot,
        .z_index = z_index,
        .quad_id = quad_id,
        .vertex_idx = 0};
    usize id1 = array_list_append(list_batch, vertices[0]);

    *vertices[1] = (Batch_Vertex){
        .position = {position[0] + size[0], position[1]},
        .uvs = {uvs[2], uvs[1]},
        .color = {color[0], color[1], color[2], color[3]},
        .texture_slot = texture_slot,
        .z_index = z_index,
        .quad_id = quad_id,
        .vertex_idx = 1};
    usize id2 = array_list_append(list_batch, vertices[1]);

    *vertices[2] = (Batch_Vertex){
        .position = {position[0] + size[0], position[1] + size[1]},
        .uvs = {uvs[2], uvs[3]},
        .color = {color[0], color[1], color[2], color[3]},
        .texture_slot = texture_slot,
        .z_index = z_index,
        .quad_id = quad_id,
        .vertex_idx = 2};
    usize id3 = array_list_append(list_batch, vertices[2]);

    *vertices[3] = (Batch_Vertex){
        .position = {position[0], position[1] + size[1]},
        .uvs = {uvs[0], uvs[3]},
        .color = {color[0], color[1], color[2], color[3]},
        .texture_slot = texture_slot,
        .z_index = z_index,
        .quad_id = quad_id,
        .vertex_idx = 3};
    usize id4 = array_list_append(list_batch, vertices[3]);
    // TODO: free batch vertexes somewhere
}

void render_line_segment(vec2 start, vec2 end, vec4 color)
{
    glUseProgram(shader_default);
    glLineWidth(3);

    f32 x = end[0] - start[0];
    f32 y = end[1] - start[1];
    f32 line[6] = {0, 0, 0, x, y, 0};

    mat4x4 model;
    mat4x4_translate(model, start[0], start[1], 0);

    glUniformMatrix4fv(glGetUniformLocation(shader_default, "model"), 1, GL_FALSE, &model[0][0]);
    glUniform4fv(glGetUniformLocation(shader_default, "color"), 1, color);

    glBindTexture(GL_TEXTURE_2D, texture_color);
    glBindVertexArray(vao_line);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_line);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(line), line);
    glDrawArrays(GL_LINES, 0, 2);

    glBindVertexArray(0);
}

void render_quad_line(vec2 pos, vec2 size, vec4 color)
{
    vec2 points[4] = {
        {pos[0] - size[0] * 0.5, pos[1] - size[1] * 0.5},
        {pos[0] + size[0] * 0.5, pos[1] - size[1] * 0.5},
        {pos[0] + size[0] * 0.5, pos[1] + size[1] * 0.5},
        {pos[0] - size[0] * 0.5, pos[1] + size[1] * 0.5},
    };
    // TODO: crashes somewhere in here when entity_destroy() is called in main.c
    render_line_segment(points[0], points[1], color);
    render_line_segment(points[1], points[2], color);
    render_line_segment(points[2], points[3], color);
    render_line_segment(points[3], points[0], color);
}

void render_aabb(f32 *aabb, vec4 color)
{
    vec2 size;
    vec2_scale(size, &aabb[2], 2);
    render_quad_line(&aabb[0], size, color);
}

f32 render_get_scale()
{
    return scale;
}

void render_sprite_sheet_init(Sprite_Sheet *sprite_sheet, const char *path, f32 cell_width, f32 cell_height)
{
    glGenTextures(1, &sprite_sheet->texture_id);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, sprite_sheet->texture_id);

    // nearest neighbor scaling:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, channel_count;
    u8 *image_data = stbi_load(path, &width, &height, &channel_count, 0);
    if (!image_data)
    {
        ERROR_EXIT("Failed to load image: %s\n", path);
    }

    // sends texture data to gpu
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    stbi_image_free(image_data); // on gpu, no longer needed on cpu

    sprite_sheet->width = (f32)width;
    sprite_sheet->height = (f32)height;
    sprite_sheet->cell_width = cell_width;
    sprite_sheet->cell_height = cell_height;
}

static void calculate_sprite_texture_coordinates(vec4 result, f32 row, f32 column, f32 texture_width, f32 texture_height, f32 cell_width, f32 cell_height)
{
    // texture coordinates are always a range from 0 - 1
    f32 w = 1.0 / (texture_width / cell_width);
    f32 h = 1.0 / (texture_height / cell_height);
    f32 x = column * w;
    f32 y = row * h;
    result[0] = x;
    result[1] = y;
    result[2] = x + w;
    result[3] = y + h;
}

void render_sprite_sheet_frame(Sprite_Sheet *sprite_sheet, SDL_Window *window, f32 row, f32 column, vec2 position, i32 z_index, bool is_flipped, vec4 color, u32 texture_slots[32])
{
    vec4 uvs;
    calculate_sprite_texture_coordinates(uvs, row, column, sprite_sheet->width, sprite_sheet->height, sprite_sheet->cell_width, sprite_sheet->cell_height);

    if (is_flipped)
    {
        f32 tmp = uvs[0];
        uvs[0] = uvs[2];
        uvs[2] = tmp;
    }

    vec2 size = {sprite_sheet->cell_width, sprite_sheet->cell_height};
    vec2 bottom_left = {position[0] - size[0] * 0.5, position[1] - size[1] * 0.5};

    i32 texture_slot = try_insert_texture(texture_slots, sprite_sheet->texture_id);

    // check if buffer is full, is so, flush buffer and try again TODO: implement some sort of LRU here
    if (texture_slot == -1)
    {
        render_end(window, texture_slots, false); // render all the batched frames before resetting for another write
        array_list_clear(list_batch);             // free old batch vertices

        // flush texture_slots array
        memset(texture_slots, 0, sizeof(u32) * 32);

        // try to insert it again
        texture_slot = try_insert_texture(texture_slots, sprite_sheet->texture_id);
        if (texture_slot == -1)
        {
            // TODO: add warning here
            printf("couldn't insert texture\n");
        }
    }
    append_quad(bottom_left, size, uvs, z_index, color, (f32)texture_slot);
}