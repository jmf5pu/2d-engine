#include "../structs.h"
#include "map_helpers.h"

void teleporter_update_state(Entity *entity, StateEnum *state)
{
    static u32 frames_on_state = 0;
    const u32 active_frames = 600; // FRAME_RATE * (0.1 * 8);

    printf("%d\n", state->teleporter_state_enum);

    switch (state->teleporter_state_enum) {
    case ACTIVE:
        if (frames_on_state == 0) {
            animation_destroy(entity->animation);
            entity->animation = animation_create(adef_teleporter_active, true);
            Entity *teleporter_glow = entity_create((vec2){150, 108}, (vec2){TELEPORTER_GLOW_DIMENSIONS[0], TELEPORTER_GLOW_DIMENSIONS[1]}, (vec2){0, 0}, 0, 0, NULL, NULL);
            teleporter_glow->animation = animation_create(adef_teleporter_glow, false);
            teleporter_glow->destroy_on_anim_completion = true;
            // TODO: trigger an enemy spawn here
        }
        else if (frames_on_state >= active_frames) {
            frames_on_state = 0;
            state->teleporter_state_enum = INACTIVE;
        }
    case INACTIVE:
        animation_destroy(entity->animation);
        entity->animation = animation_create(adef_teleporter_inactive, false);
    case SPINNING_UP: // TODO: add logic for a button press to trigger this
    case SPINNING_DOWN:
    default:
        break;
    };

    frames_on_state++;
}