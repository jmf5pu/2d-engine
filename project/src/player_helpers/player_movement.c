#include "player_helpers.h"
#include <math.h>

void handle_player_joystick_movement(Player *player)
{
    Controller_Input_State *controller_input_state = player->input_state->controller_input_state;
    float angle = atan2(controller_input_state->left_joystick_state.y_axis, controller_input_state->left_joystick_state.x_axis);
    float max_x_velocity = fabs(MAX_PLAYER_MOVEMENT_SPEED * cos(angle));
    float max_y_velocity = fabs(MAX_PLAYER_MOVEMENT_SPEED * sin(angle));

    if (INVERT_Y_AXIS)
        max_y_velocity *= -1;

    player->entity->body->velocity[0] = max_x_velocity * controller_input_state->left_joystick_state.x_axis;
    player->entity->body->velocity[1] = max_y_velocity * controller_input_state->left_joystick_state.y_axis;
}