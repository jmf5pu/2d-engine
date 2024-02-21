#include "player_helpers.h"
#include <math.h>

void handle_player_joystick_movement(Player *player)
{
    Controller_Input_State *controller_input_state = player->input_state->controller_input_state;
    float angle;
    if (controller_input_state->left_joystick_state.x_axis != 0.0f) {
        angle = tan(controller_input_state->left_joystick_state.y_axis / controller_input_state->left_joystick_state.x_axis);
    }
    else {
        angle = 0.0f;
    }
    float max_x_velocity = MAX_PLAYER_MOVEMENT_SPEED * acos(angle);
    float max_y_velocity = MAX_PLAYER_MOVEMENT_SPEED * asin(angle);
    player->entity->body->velocity[0] = max_x_velocity * fabs(controller_input_state->left_joystick_state.x_axis);
    player->entity->body->velocity[1] = max_y_velocity * fabs(controller_input_state->left_joystick_state.y_axis);
    printf("player velocity: %f, %f\n", player->entity->body->velocity[0], player->entity->body->velocity[1]);
}