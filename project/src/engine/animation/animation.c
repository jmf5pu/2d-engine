#include <assert.h>

#include "../util.h"
#include "../array_list.h"
#include "../animation.h"

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
    if (def == NULL)
    {
        ERROR_EXIT("Memory allocation failed\n");
    }

    def->sprite_sheet = sprite_sheet;
    def->frame_count = frame_count;

    for (u8 i = 0; i < frame_count; ++i)
    {
        def->frames[i] = (Animation_Frame){
            .column = columns[i],
            .row = rows[i],
            .duration = durations[i],
        };
    }

    if (array_list_append(animation_definition_storage, def) == (usize)-1)
    {
        free(def); // Clean up allocated memory in case of failure
        ERROR_EXIT("Could not append body to list\n");
    }

    return def;
}

Animation *animation_create(Animation_Definition *adef, bool does_loop)
{
    usize id = animation_storage->len;

    if (adef == NULL)
    {
        ERROR_EXIT("Animation Definition with address %p not found.", adef);
    }

    // check if anims are inactive, if so replace one, otherwise append to end
    for (usize i = 0; i < animation_storage->len; ++i)
    {
        Animation *animation = array_list_get(animation_storage, i, "animation_create trying to find first free slot");
        if (!animation->is_active)
        {
            id = i;
            break;
        }
    }

    if (id == animation_storage->len)
    {
        Animation *new_animation = (Animation *)malloc(sizeof(Animation));
        if (new_animation == NULL)
        {
            ERROR_EXIT("Memory allocation for Animation failed.");
        }
        *new_animation = (Animation){0}; // Initialize the allocated memory
        array_list_append(animation_storage, new_animation);
        id = animation_storage->len - 1; // Update id to the newly appended index
    }

    Animation *animation = array_list_get(animation_storage, id, "animation_create trying to find first free slot");

    // Other fields default to 0 when using field dot syntax.
    *animation = (Animation){
        .animation_definition = adef,
        .does_loop = does_loop,
        .is_active = true,
    };

    return animation;
}

void animation_destroy(usize id)
{
    Animation *animation = array_list_get(animation_storage, id, "called by animation_destroy");
    animation->is_active = false;
    array_list_remove(animation_storage, id);
}

Animation *animation_get(usize id)
{
    return array_list_get(animation_storage, id, "called by animation_get");
}

void animation_update(f32 dt)
{
    // iterate through all animations
    for (usize i = 0; i < animation_storage->len; ++i)
    {
        Animation *animation = array_list_get(animation_storage, i, "called by animation_update");
        Animation_Definition *adef = animation->animation_definition; // get associated animation definition
        animation->current_frame_time -= dt;

        if (animation->current_frame_time <= 0)
        {
            if (animation->current_frame_index < adef->frame_count)
                animation->current_frame_index += 1;

            // Loop or stay on last frame.
            if (animation->current_frame_index == adef->frame_count)
            {
                if (animation->does_loop)
                {
                    animation->current_frame_index = 0;
                }
            }

            animation->current_frame_time = adef->frames[animation->current_frame_index].duration;
        }
    }
}

void animation_render(Animation *animation, SDL_Window *window, vec2 position, i32 z_index, vec4 color, u32 texture_slots[32])
{
    Animation_Definition *adef = animation->animation_definition;
    Animation_Frame *aframe = &adef->frames[animation->current_frame_index];
    render_sprite_sheet_frame(adef->sprite_sheet, window, aframe->row, aframe->column, position, z_index, animation->is_flipped, color, texture_slots);
}
