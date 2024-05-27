#include "../structs.h"
#include "map_helpers.h"

void teleporter_update_state(Entity *entity, StateEnum *state)
{
    static u32 frames_on_state = 0;
    const u8 spinning_adef_frames = 8;
    const u8 active_adef_frames = 8;
    const f32 spin_slow = 0.08;
    const f32 spin_med = 0.06;
    const f32 spin_fast = 0.04;
    const u32 active_frames = FRAME_RATE * (spin_fast * active_adef_frames);

    switch (state->teleporter_state_enum) {
    case ACTIVE:
        if (frames_on_state == 1) {
            animation_destroy(entity->animation);
            entity->animation = animation_create(adef_teleporter_active, true);
            Entity *teleporter_glow = entity_create((vec2){150, 108}, (vec2){TELEPORTER_GLOW_DIMENSIONS[0], TELEPORTER_GLOW_DIMENSIONS[1]}, (vec2){0, 0}, 0, 0, NULL, NULL);
            teleporter_glow->animation = animation_create(adef_teleporter_glow, false);
            teleporter_glow->destroy_on_anim_completion = true;
            // TODO: trigger an enemy spawn here
        }
        else if (frames_on_state >= active_frames) {
            frames_on_state = 0;
            state->teleporter_state_enum = SPINNING_DOWN;
        }
        break;
    case INACTIVE:
        entity->animation->does_loop = false;
        break;
    case SPINNING_UP: // TODO: add logic for a button press to trigger this
        teleporter_spin_up_and_down_states(entity, &state->teleporter_state_enum, &frames_on_state, ACTIVE, spin_slow, spin_med, spin_fast);
        break;
    case SPINNING_DOWN:
        teleporter_spin_up_and_down_states(entity, &state->teleporter_state_enum, &frames_on_state, INACTIVE, spin_fast, spin_med, spin_slow);
        break;
    default:
        break;
    };

    frames_on_state++;
}

/// @brief Helper method for logic between active and inactive states for the teleporter
/// @param entity
/// @param teleporter_state_enum
/// @param frames_on_state
/// @param next_state
/// @param first_duration
/// @param second_duration
/// @param third_duration
void teleporter_spin_up_and_down_states(
    Entity *entity, TeleporterStateEnum *teleporter_state_enum, u32 *frames_on_state, TeleporterStateEnum next_state, f32 first_duration, f32 second_duration, f32 third_duration)
{
    const u8 adef_frame_count = adef_teleporter_spinning->frame_count;
    const u32 total_frames = FRAME_RATE * 2 * ((first_duration * adef_frame_count) + (second_duration * adef_frame_count) + (third_duration * adef_frame_count));
    if (*frames_on_state == 1) {
        animation_destroy(entity->animation);
        entity->animation = animation_create(adef_teleporter_spinning, true);
        entity->animation->z_index = -1;
        update_adef_frame_durations(entity->animation->animation_definition, first_duration);
    }
    else if (*frames_on_state == (u32)total_frames / 3)
        update_adef_frame_durations(entity->animation->animation_definition, second_duration);
    else if (*frames_on_state == (u32)2 * total_frames / 3)
        update_adef_frame_durations(entity->animation->animation_definition, third_duration);
    else if (*frames_on_state >= total_frames) {
        *frames_on_state = 0;
        *teleporter_state_enum = next_state;
    }
}

/// @brief Updates all the frame durations of the provided animation definiton
/// @param adef
/// @param duration
void update_adef_frame_durations(Animation_Definition *adef, f32 duration)
{
    for (int i = 0; i < adef->frame_count; i++)
        adef->frames[i].duration = duration;
}