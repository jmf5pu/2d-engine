#include "../enemy_helpers/enemy_helpers.h"
#include "../structs.h"
#include "map_helpers.h"

/// @brief state machine for teleporter
/// @param entity
/// @param state
void teleporter_update_state(DynamicProp *prop)
{
    const u8 spinning_adef_frames = 8;
    const u8 active_adef_frames = 8;
    const f32 spin_slow = 0.08;
    const f32 spin_med = 0.06;
    const f32 spin_fast = 0.04;
    const u32 active_frames = FRAME_RATE * (spin_fast * active_adef_frames);

    switch (prop->state.teleporter_state_enum) {
    case ACTIVE:
        if (prop->frames_on_state == 1) {
            animation_destroy(prop->entity->animation);
            prop->entity->animation = animation_create(adef_teleporter_active, true);

            vec2 teleporter_pos;
            vec2_dup(teleporter_pos, prop->entity->body->aabb.position);

            Entity *teleporter_glow = entity_create(
                (vec2){teleporter_pos[0], teleporter_pos[1] + 8}, (vec2){TELEPORTER_GLOW_DIMENSIONS[0], TELEPORTER_GLOW_DIMENSIONS[1]}, (vec2){0, 0}, 0, 0, NULL, NULL);
            teleporter_glow->animation = animation_create(adef_teleporter_glow, false);
            teleporter_glow->destroy_on_anim_completion = true;
        }
        else if (prop->frames_on_state == active_frames / 2) {
            create_enemy(prop->entity->body->aabb.position);
        }
        else if (prop->frames_on_state >= active_frames) {
            prop->state.teleporter_state_enum = SPINNING_DOWN;
            prop->frames_on_state = 0;
        }
        break;
    case INACTIVE:
        prop->entity->animation->does_loop = false;
        if (prop->frames_on_state == 1) {
            for (int i = 0; i < map.num_dynamic_props; i++) {
                if (map.dynamic_props[i]->type == TELEPORTER_BUTTON) {
                    map.dynamic_props[i]->state.button_state_enum = UNPRESSED;
                    map.dynamic_props[i]->frames_on_state = 0;
                }
            }
        }
        break;
    case SPINNING_UP:
        teleporter_spin_up_and_down_states(prop->entity, &prop->state.teleporter_state_enum, &prop->frames_on_state, ACTIVE, spin_slow, spin_med, spin_fast);
        break;
    case SPINNING_DOWN:
        teleporter_spin_up_and_down_states(prop->entity, &prop->state.teleporter_state_enum, &prop->frames_on_state, INACTIVE, spin_fast, spin_med, spin_slow);
        break;
    default:
        break;
    };
    prop->frames_on_state++;
}

/// @brief Checks the button state and assigns the appropriate animation to the entity
/// @param entity
/// @param state
void teleporter_button_update_state(DynamicProp *prop)
{
    switch (prop->state.button_state_enum) {
    case PRESSED:
        if (prop->frames_on_state == 0) {
            animation_destroy(prop->entity->animation);
            prop->entity->animation = animation_create(adef_teleporter_button_pressed, false);
        }
        break;
    case UNPRESSED:
        if (prop->frames_on_state == 0) {
            animation_destroy(prop->entity->animation);
            prop->entity->animation = animation_create(adef_teleporter_button_unpressed, true);
        }
        break;
    default:
        break;
    }
    prop->frames_on_state++;
}

void weapon_pickup_update_state(DynamicProp *prop)
{
    printf("%d\n", prop->state.pickup_state_enum);

    // This logic could be buggy if props *can* have collisions with other bodies aside from players as a collisio
    if (!prop->entity->body->is_being_hit) {
        prop->colliding_player = NULL;
    }

    switch (prop->state.pickup_state_enum) {
    case NORMAL:
        break;
    case HIGHLIGHTING:
        if (prop->entity->body->first_frame_being_hit) {
            Entity *pickup_highlight = entity_create(prop->entity->body->aabb.position, (vec2){7, 9}, (vec2){0, 0}, 0, 0, NULL, NULL);
            pickup_highlight->animation = animation_create(adef_glock_pickup_highlight, false);
            pickup_highlight->animation->z_index = 1;
            pickup_highlight->destroy_on_anim_completion = true;
        }
        if (prop->colliding_player->input_state->key_state->use == KS_HELD) {
            prop->state.pickup_state_enum = INTERACTING;
        }
        break;
    case INTERACTING:
        if (prop->colliding_player && prop->colliding_player->input_state->key_state->use == KS_UNPRESSED) {
            prop->state.pickup_state_enum = NORMAL;
        }
        break;
    default:
        break;
    }
    // vec2 interact_bar_position = {player->relative_position[0], player->relative_position[1] + 15};
    // bool can_reload = player->weapon->capacity < player->weapon->max_capacity;

    // if (player->status != PLAYER_RELOADING && player->input_state->key_state->reload == KS_HELD && can_reload) {
    //     player->status = PLAYER_RELOADING;
    //     player->frames_on_status = 0;
    //     if (player->interact_bar->animation != NULL) {
    //         animation_destroy(player->interact_bar->animation);
    //         player->interact_bar->animation = NULL;
    //     }
    //     player->interact_bar->animation = animation_create(adef_interact_bar_open, false);
    //     player->interact_bar->is_active = true;
    // }
    // else if (player->status == PLAYER_RELOADING && player->input_state->key_state->reload == KS_UNPRESSED) {
    //     player->status = PLAYER_ACTIVE;
    //     player->frames_on_status = 0;
    //     if (player->interact_bar->animation != NULL) {
    //         animation_destroy(player->interact_bar->animation);
    //         player->interact_bar->animation = NULL;
    //     }
    // }
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