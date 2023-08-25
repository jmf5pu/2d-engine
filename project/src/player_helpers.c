#include "player_helpers.h"
#include "engine/global.h"

// updates player statuses based on frame counter associated with each playaer
void update_player_status(Player *player)
{
    // check if spawn delay is up
    if (player->status == INACTIVE && player->frames_on_status >= (player->spawn_delay * global.time.frame_rate))
    {
        // update status & reset counter
        player->status = SPAWNING;
        player->frames_on_status = 0;

        // reset location
        player->entity->body->aabb.position[0] = player->spawn_point[0];
        player->entity->body->aabb.position[1] = player->spawn_point[1];

        // reset health
        player->health = 100;

        // make player visible
        player->entity->is_active = true;
        player->entity->body->is_active = true;
    }
    // check if spawn time is up
    else if (player->status == SPAWNING && player->frames_on_status >= (player->spawn_time * global.time.frame_rate))
    {
        player->status = ACTIVE;
        player->frames_on_status = 0;
    }
    // check if health is 0
    else if (player->health <= 0 && player->status == ACTIVE)
    {
        player->status = DESPAWNING;
        player->animation_set->dying->current_frame_index = 0;
        player->frames_on_status = 0;

        // shouldn't be moving on death anim
        player->entity->body->velocity[0] = 0;
        player->entity->body->velocity[1] = 0;
    }
    // check if death animation is complete
    else if (player->status == DESPAWNING && player->frames_on_status >= (player->despawn_time * global.time.frame_rate))
    {
        player->status = INACTIVE;
        player->frames_on_status = 0;

        // hide sprites
        player->entity->is_active = false;
        player->entity->body->is_active = false;
    }

    // update weapon status
    // printf("fire cooldown: %f, %d\n", (1.0 / (player->weapon->max_fire_rate / 60.0)), global.time.frame_rate);
    if (!player->weapon->ready_to_fire && player->weapon->frames_since_last_shot >= ((1.0 / (player->weapon->max_fire_rate / 60.0)) * global.time.frame_rate))
    {
        player->weapon->ready_to_fire = true;
    }

    // update all timers
    player->frames_on_status++;
    player->weapon->frames_since_last_shot++;
}