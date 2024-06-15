#include <assert.h>

#include "../animation.h"
#include "../array_list.h"
#include "../util.h"

static Array_List *animation_definition_storage;
static Array_List *animation_storage;

void animation_init(void)
{
    animation_definition_storage = array_list_create(sizeof(struct Animation_Definition *), 0);
    animation_storage = array_list_create(sizeof(struct Animation *), 0);
}

Animation_Definition *animation_definition_create(Sprite_Sheet *sprite_sheet, f32 *durations, u8 *rows, u8 *columns, u8 frame_count)
{
    assert(frame_count <= MAX_FRAMES);

    Animation_Definition *def = (Animation_Definition *)malloc(sizeof(Animation_Definition));
    if (def == NULL) {
        ERROR_EXIT("Memory allocation failed\n");
    }

    def->sprite_sheet = sprite_sheet;
    def->frame_count = frame_count;

    for (u8 i = 0; i < frame_count; ++i) {
        def->frames[i] = (Animation_Frame){
            .column = columns[i],
            .row = rows[i],
            .duration = durations[i],
        };
    }

    if (array_list_append(animation_definition_storage, def) == (usize)-1) {
        free(def); // Clean up allocated memory in case of failure
        ERROR_EXIT("Could not append body to list\n");
    }

    return def;
}

Animation *animation_create(Animation_Definition *adef, bool does_loop)
{
    usize id = animation_storage->len;

    if (adef == NULL) {
        ERROR_EXIT("Animation Definition with address %p not found.", adef);
    }

    // check if anims are inactive, if so replace one, otherwise append to
    // end for (usize i = 0; i < animation_storage->len; ++i)
    // {
    //     Animation *animation = array_list_get(animation_storage, i);
    //     if (!animation->is_active)
    //     {
    //         id = i;
    //         break;
    //     }
    // }

    if (id == animation_storage->len) {
        Animation *new_animation = (Animation *)malloc(sizeof(Animation));
        if (new_animation == NULL) {
            ERROR_EXIT("Memory allocation for Animation failed.");
        }
        *new_animation = (Animation){0}; // Initialize the allocated memory
        array_list_append(animation_storage, new_animation);
        id = animation_storage->len - 1; // Update id to the newly appended index
    }

    Animation *animation = array_list_get(animation_storage, id);

    // Other fields default to 0 when using field dot syntax.
    // mark anims that don't loop as inactive
    *animation = (Animation){
        .animation_definition = adef,
        .does_loop = does_loop,
        .is_active = true,
        .z_index = 0,
        .reset_count = 0,
        .current_frame_index = 0,
        .current_frame_time = adef->frames[0].duration,
    };

    return animation;
}

usize animation_get_id(Animation *target_animation)
{
    for (usize i = 0; i < animation_storage->len; ++i) {
        if (animation_get(i) == target_animation) {
            return i;
        }
    }
    ERROR_EXIT("ERROR: Could not find the specified animation in the Array_List\n");
}

usize animation_definition_get_id(Animation_Definition *target_adef)
{
    for (usize i = 0; i < animation_definition_storage->len; ++i) {
        if (array_list_get(animation_definition_storage, i) == target_adef) {
            return i;
        }
    }
    ERROR_EXIT("ERROR: Could not find the specified animation definition in the Array_List\n");
}

void animation_destroy(Animation *animation)
{
    usize id = animation_get_id(animation);
    array_list_remove(animation_storage, id);
    free(animation);
}

void animation_definition_destroy(Animation_Definition *adef)
{
    usize id = animation_definition_get_id(adef);
    array_list_remove(animation_definition_storage, id);
    free(adef);
}

Animation *animation_get(usize id) { return array_list_get(animation_storage, id); }

void animation_update(f32 dt)
{
    // iterate through all animations
    for (usize i = 0; i < animation_storage->len; ++i) {
        Animation *animation = array_list_get(animation_storage, i);
        if (animation->is_active) {
            Animation_Definition *adef = animation->animation_definition; // get associated
                                                                          // animation definition
            animation->current_frame_time -= dt;

            if (animation->current_frame_time <= 0) {
                animation->current_frame_index += 1;

                // Loop or stay on last frame.
                if (animation->current_frame_index == adef->frame_count) {
                    if (animation->does_loop) {
                        animation->current_frame_index = 0;
                        animation->reset_count += 1;
                    }
                    else {
                        animation->current_frame_index -= 1;
                    }
                }

                animation->current_frame_time = adef->frames[animation->current_frame_index].duration;
            }
        }
    }
}

void animation_render(Animation *animation, SDL_Window *window, vec2 position, vec4 color, u32 texture_slots[BATCH_SIZE])
{
    animation->is_active = true;
    Animation_Definition *adef = animation->animation_definition;
    Animation_Frame *aframe = &adef->frames[animation->current_frame_index];
    render_sprite_sheet_frame(adef->sprite_sheet, window, aframe->row, aframe->column, position, animation->z_index, animation->is_flipped, color, texture_slots);
}

void clear_animation_list(void) { array_list_clear(animation_storage, true); }

void clear_animation_definition_list(void) { array_list_clear(animation_definition_storage, true); }