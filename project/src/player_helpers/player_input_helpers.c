#include "../engine/input/input.h"
#include "../engine/render.h"
#include "player_helpers.h"

void assign_player_input_devices(void)
{
    player_one->controller_id = open_controller_ids[0];
    if (SPLIT_SCREEN)
        player_two->controller_id = open_controller_ids[1];

    printf("player_one->controller_id: %d\n", player_one->controller_id);
    printf("player_two->controller_id: %d\n", player_two->controller_id);
}