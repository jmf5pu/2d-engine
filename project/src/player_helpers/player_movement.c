#include "player_helpers.h"
#include <math.h>

void apply_player_joystick_movement(Player *player)
{
    update_entity_velocity_from_joystick_input(player->input_state->controller_input_state->left_joystick_state, player->entity, MAX_PLAYER_MOVEMENT_SPEED);
    update_entity_velocity_from_joystick_input(player->input_state->controller_input_state->right_joystick_state, player->crosshair, MAX_CROSSHAIR_MOVEMENT_SPEED);
}

void update_entity_velocity_from_joystick_input(Joystick_State input, Entity *entity, int max_velocity)
{
    float angle = atan2(input.y_axis, input.x_axis);
    float max_x_velocity = fabs(max_velocity * cos(angle));
    float max_y_velocity = fabs(max_velocity * sin(angle));

    if (INVERT_Y_AXIS)
        max_y_velocity *= -1;

    entity->body->velocity[0] = max_x_velocity * input.x_axis;
    entity->body->velocity[1] = max_y_velocity * input.y_axis;
}