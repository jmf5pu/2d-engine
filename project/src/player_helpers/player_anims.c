#include "player_anims.h"
#include "../engine/hash_map.h"

static Hash_Map *player_anim_map;

void update_player_character_anim(Player *player)
{
    // cache old anim to check if we are SWITCHING anims
    Animation *prev_anim = player->entity->animation;

    char *anim_name = calloc(50, sizeof(char));
    strcat(anim_name, "player_skinhead_"); // TODO: move character name to player struct, pull from there

    // determine movment state anim siffux
    bool player_is_moving = player->entity->body->velocity[0] || player->entity->body->velocity[1];
    char *movement_state = player_is_moving ? "moving" : "idle";

    // determine direction anim suffix
    char *direction;
    if (player->crosshair_angle > -1 * M_PI / 4 && player->crosshair_angle <= M_PI / 4)
        direction = "1";
    else if (player->crosshair_angle > M_PI / 4 && player->crosshair_angle <= 3 * M_PI / 4)
        direction = "2";
    else if (player->crosshair_angle > 3 * M_PI / 4 || player->crosshair_angle <= -3 * M_PI / 4)
        direction = "3";
    else if (player->crosshair_angle > -3 * M_PI / 4 && player->crosshair_angle < -1 * M_PI / 4)
        direction = "4";
    else
        printf("got unexpected crosshair angle: %f\n", player->crosshair_angle);

    // build the anim name from the suffixes
    strcat(anim_name, movement_state);
    strcat(anim_name, "_");
    strcat(anim_name, direction);
    strcat(anim_name, "\0");

    // select the correct anim from hashmap or use the placeholder
    Animation *player_anim = get(player_anim_map, anim_name);
    if (player_anim)
        player->entity->animation = player_anim;
    else
        player->entity->animation = missing_anim_placeholder;

    // ensure we are starting new anims at the first frame
    if (player->entity->animation != prev_anim)
        player->entity->animation->current_frame_index = 0;

    free(anim_name);
}

void init_player_character_anim_hashmap(void)
{
    player_anim_map = create_hash_map(PLAYER_ANIM_COUNT);

    insert(player_anim_map, "player_skinhead_idle_1", anim_player_skinhead_idle_1);
    insert(player_anim_map, "player_skinhead_idle_2", anim_player_skinhead_idle_2);
    insert(player_anim_map, "player_skinhead_idle_3", anim_player_skinhead_idle_3);
    insert(player_anim_map, "player_skinhead_idle_4", anim_player_skinhead_idle_4);
    insert(player_anim_map, "player_skinhead_moving_1", anim_player_skinhead_moving_1);
    insert(player_anim_map, "player_skinhead_moving_2", anim_player_skinhead_moving_2);
    insert(player_anim_map, "player_skinhead_moving_3", anim_player_skinhead_moving_3);
    insert(player_anim_map, "player_skinhead_moving_4", anim_player_skinhead_moving_4);
}

/// @brief libresprite automatically appends each image with an int starting at 0, so the variables names are confusingly off by 1 :/
/// @param
void init_player_character_anims(void)
{
    render_sprite_sheet_init(&sprite_sheet_player_skinhead_idle_1, "assets/wip/player_skinhead_idle_0.png", 18, 26);
    adef_player_skinhead_idle_1 = animation_definition_create(&sprite_sheet_player_skinhead_idle_1, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_player_skinhead_idle_1 = animation_create(adef_player_skinhead_idle_1, false);
    render_sprite_sheet_init(&sprite_sheet_player_skinhead_idle_2, "assets/wip/player_skinhead_idle_1.png", 18, 26);
    adef_player_skinhead_idle_2 = animation_definition_create(&sprite_sheet_player_skinhead_idle_2, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_player_skinhead_idle_2 = animation_create(adef_player_skinhead_idle_2, false);
    render_sprite_sheet_init(&sprite_sheet_player_skinhead_idle_3, "assets/wip/player_skinhead_idle_2.png", 18, 26);
    adef_player_skinhead_idle_3 = animation_definition_create(&sprite_sheet_player_skinhead_idle_3, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_player_skinhead_idle_3 = animation_create(adef_player_skinhead_idle_3, false);
    render_sprite_sheet_init(&sprite_sheet_player_skinhead_idle_4, "assets/wip/player_skinhead_idle_3.png", 18, 26);
    adef_player_skinhead_idle_4 = animation_definition_create(&sprite_sheet_player_skinhead_idle_4, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    anim_player_skinhead_idle_4 = animation_create(adef_player_skinhead_idle_4, false);

    render_sprite_sheet_init(&sprite_sheet_player_skinhead_moving_1, "assets/wip/player_skinhead_moving_1.png", 18, 26);
    adef_player_skinhead_moving_1 =
        animation_definition_create(&sprite_sheet_player_skinhead_moving_1, (f32[]){0.07, 0.07, 0.07, 0.07, 0.07, 0.07}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
    anim_player_skinhead_moving_1 = animation_create(adef_player_skinhead_moving_1, true);
    render_sprite_sheet_init(&sprite_sheet_player_skinhead_moving_2, "assets/wip/player_skinhead_moving_2.png", 18, 26);
    adef_player_skinhead_moving_2 =
        animation_definition_create(&sprite_sheet_player_skinhead_moving_2, (f32[]){0.07, 0.07, 0.07, 0.07, 0.07, 0.07}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
    anim_player_skinhead_moving_2 = animation_create(adef_player_skinhead_moving_2, true);
    render_sprite_sheet_init(&sprite_sheet_player_skinhead_moving_3, "assets/wip/player_skinhead_moving_3.png", 18, 26);
    adef_player_skinhead_moving_3 =
        animation_definition_create(&sprite_sheet_player_skinhead_moving_3, (f32[]){0.07, 0.07, 0.07, 0.07, 0.07, 0.07}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
    anim_player_skinhead_moving_3 = animation_create(adef_player_skinhead_moving_3, true);
    render_sprite_sheet_init(&sprite_sheet_player_skinhead_moving_4, "assets/wip/player_skinhead_moving_4.png", 18, 26);
    adef_player_skinhead_moving_4 =
        animation_definition_create(&sprite_sheet_player_skinhead_moving_4, (f32[]){0.07, 0.07, 0.07, 0.07, 0.07, 0.07}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
    anim_player_skinhead_moving_4 = animation_create(adef_player_skinhead_moving_4, true);
}