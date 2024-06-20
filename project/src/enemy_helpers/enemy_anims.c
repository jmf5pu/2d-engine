#include "../engine/hash_map.h"
#include "../player_helpers/player_helpers.h"
#include "../structs.h"
#include "enemy_helpers.h"

static Hash_Map *enemy_adef_map;

void update_enemy_anim(Zombie *zombie)
{
    char *anim_name = calloc(50, sizeof(char));
    strcat(anim_name, "zombie_"); // TODO: move character name to player struct, pull from there

    // determine movment state adef suffux
    bool player_is_moving = zombie->entity->body->velocity[0] || zombie->entity->body->velocity[1];
    char *movement_state = player_is_moving ? "moving" : "idle";

    // determine direction adef suffix
    f32 angle = atan2(zombie->entity->body->velocity[1], zombie->entity->body->velocity[0]);
    char *direction;
    if (angle > -1 * M_PI / 4 && angle <= M_PI / 4)
        direction = "1";
    else if (angle > M_PI / 4 && angle <= 3 * M_PI / 4)
        direction = "2";
    else if (angle > 3 * M_PI / 4 || angle <= -3 * M_PI / 4)
        direction = "3";
    else if (angle > -3 * M_PI / 4 && angle < -1 * M_PI / 4)
        direction = "4";
    else
        printf("got unexpected enemy angle, cannot map to animation: %f\n", angle);

    // build the anim name from the suffixes
    strcat(anim_name, movement_state);
    strcat(anim_name, "_");
    strcat(anim_name, direction);
    strcat(anim_name, "\0");

    // select the correct anim from hashmap or use the placeholder
    Animation_Definition *enemy_adef = get(enemy_adef_map, anim_name);
    if (!enemy_adef) {
        animation_destroy(zombie->entity->animation);
        zombie->entity->animation = missing_anim_placeholder;
    }
    else if (zombie->entity->animation->animation_definition != enemy_adef) {
        animation_destroy(zombie->entity->animation);
        zombie->entity->animation = animation_create(enemy_adef, true);
    }
    free(anim_name);
}

void init_enemy_adef_hashmap(void)
{
    enemy_adef_map = create_hash_map(ENEMY_ADEF_COUNT);

    insert(enemy_adef_map, "zombie_idle_1", adef_zombie_idle_1);
    insert(enemy_adef_map, "zombie_idle_2", adef_zombie_idle_2);
    insert(enemy_adef_map, "zombie_idle_3", adef_zombie_idle_3);
    insert(enemy_adef_map, "zombie_idle_4", adef_zombie_idle_4);
    insert(enemy_adef_map, "zombie_moving_1", adef_zombie_moving_1);
    insert(enemy_adef_map, "zombie_moving_2", adef_zombie_moving_2);
    insert(enemy_adef_map, "zombie_moving_3", adef_zombie_moving_3);
    insert(enemy_adef_map, "zombie_moving_4", adef_zombie_moving_4);
}

void init_enemy_adefs(void)
{
    const int size_x = 18;
    const int size_y = 23;

    // TODO: update to the correct .png files once they are created
    render_sprite_sheet_init(&sprite_sheet_zombie_idle_1, "assets/wip/zombie_idle_0.png", size_x, size_y);
    adef_zombie_idle_1 = animation_definition_create(&sprite_sheet_zombie_idle_1, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_zombie_idle_2, "assets/wip/zombie_idle_1.png", size_x, size_y);
    adef_zombie_idle_2 = animation_definition_create(&sprite_sheet_zombie_idle_2, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_zombie_idle_3, "assets/wip/zombie_idle_2.png", size_x, size_y);
    adef_zombie_idle_3 = animation_definition_create(&sprite_sheet_zombie_idle_3, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);
    render_sprite_sheet_init(&sprite_sheet_zombie_idle_4, "assets/wip/zombie_idle_3.png", size_x, size_y);
    adef_zombie_idle_4 = animation_definition_create(&sprite_sheet_zombie_idle_4, (f32[]){0}, (u8[]){0}, (u8[]){0}, 1);

    render_sprite_sheet_init(&sprite_sheet_zombie_moving_1, "assets/wip/zombie_moving_1.png", size_x, size_y);
    adef_zombie_moving_1 =
        animation_definition_create(&sprite_sheet_zombie_moving_1, (f32[]){0.07, 0.07, 0.07, 0.07, 0.07, 0.07}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
    render_sprite_sheet_init(&sprite_sheet_zombie_moving_2, "assets/wip/player_skinhead_moving_2.png", 18, 26);
    adef_zombie_moving_2 =
        animation_definition_create(&sprite_sheet_zombie_moving_2, (f32[]){0.07, 0.07, 0.07, 0.07, 0.07, 0.07}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
    render_sprite_sheet_init(&sprite_sheet_zombie_moving_3, "assets/wip/zombie_moving_2.png", size_x, size_y);
    adef_zombie_moving_3 =
        animation_definition_create(&sprite_sheet_zombie_moving_3, (f32[]){0.07, 0.07, 0.07, 0.07, 0.07, 0.07}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
    render_sprite_sheet_init(&sprite_sheet_zombie_moving_4, "assets/wip/player_skinhead_moving_4.png", 18, 26);
    adef_zombie_moving_4 =
        animation_definition_create(&sprite_sheet_zombie_moving_4, (f32[]){0.07, 0.07, 0.07, 0.07, 0.07, 0.07}, (u8[]){0, 0, 0, 0, 0, 0}, (u8[]){0, 1, 2, 3, 4, 5}, 6);
}