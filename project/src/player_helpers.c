#include "engine/global.h"
#include "engine/util.h"
#include "player_helpers.h"
#include "collision_behavior.h"

// declare players
Player *player_one;
Player *player_two;

// sets up animations for players and bullets
void init_all_anims()
{
    // player_one stuff
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_idle_side, "assets/soldier_1_m16_idle_side.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_running_side, "assets/soldier_1_m16_running_side.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_idle_back, "assets/soldier_1_m16_idle_back.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_running_back, "assets/soldier_1_m16_running_back.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_idle_front, "assets/soldier_1_m16_idle_front.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_running_front, "assets/soldier_1_m16_running_front.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_spawning_side, "assets/soldier_1_spawning_side.png", 42, 42);
    render_sprite_sheet_init(&p1_sprite_sheet_soldier_dying_side, "assets/soldier_1_m16_dying_side.png", 42, 42);

    p1_adef_soldier_idle_side = animation_definition_create(
        &p1_sprite_sheet_soldier_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_running_side = animation_definition_create(
        &p1_sprite_sheet_soldier_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    p1_adef_soldier_idle_back = animation_definition_create(
        &p1_sprite_sheet_soldier_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_running_back = animation_definition_create(
        &p1_sprite_sheet_soldier_running_back,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    p1_adef_soldier_idle_front = animation_definition_create(
        &p1_sprite_sheet_soldier_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p1_adef_soldier_running_front = animation_definition_create(
        &p1_sprite_sheet_soldier_running_front,
        (f32[]){0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.04, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
    p1_adef_soldier_spawning_side = animation_definition_create(
        &p1_sprite_sheet_soldier_spawning_side,
        (f32[]){0.25, 0.25},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);
    p1_adef_soldier_dying_side = animation_definition_create(
        &p1_sprite_sheet_soldier_dying_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.75, 0.5, 0.5, 0.5, 0.75},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);

    p1_anim_soldier_idle_side = animation_create(p1_adef_soldier_idle_side, false);
    p1_anim_soldier_running_side = animation_create(p1_adef_soldier_running_side, true);
    p1_anim_soldier_idle_back = animation_create(p1_adef_soldier_idle_back, false);
    p1_anim_soldier_running_back = animation_create(p1_adef_soldier_running_back, true);
    p1_anim_soldier_idle_front = animation_create(p1_adef_soldier_idle_front, false);
    p1_anim_soldier_running_front = animation_create(p1_adef_soldier_running_front, true);
    p1_anim_soldier_spawning_side = animation_create(p1_adef_soldier_spawning_side, true);
    p1_anim_soldier_dying_side = animation_create(p1_adef_soldier_dying_side, true);

    // player_two stuff
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_idle_side, "assets/soldier_1_m16_idle_side.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_running_side, "assets/soldier_1_m16_running_side.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_idle_back, "assets/soldier_1_m16_idle_back.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_running_back, "assets/soldier_1_m16_running_back.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_idle_front, "assets/soldier_1_m16_idle_front.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_running_front, "assets/soldier_1_m16_running_front.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_spawning_side, "assets/soldier_1_spawning_side.png", 42, 42);
    render_sprite_sheet_init(&p2_sprite_sheet_soldier_dying_side, "assets/soldier_1_m16_dying_side.png", 42, 42);

    p2_adef_soldier_idle_side = animation_definition_create(
        &p2_sprite_sheet_soldier_idle_side,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_running_side = animation_definition_create(
        &p2_sprite_sheet_soldier_running_side,
        (f32[]){0.03, 0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.03, 0.03, 0.04, 0.03, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    p2_adef_soldier_idle_back = animation_definition_create(
        &p2_sprite_sheet_soldier_idle_back,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_running_back = animation_definition_create(
        &p2_sprite_sheet_soldier_running_back,
        (f32[]){0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);
    p2_adef_soldier_idle_front = animation_definition_create(
        &p2_sprite_sheet_soldier_idle_front,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    p2_adef_soldier_running_front = animation_definition_create(
        &p2_sprite_sheet_soldier_running_front,
        (f32[]){0.03, 0.03, 0.04, 0.03, 0.03, 0.03, 0.04, 0.03},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8},
        8);
    p2_adef_soldier_spawning_side = animation_definition_create(
        &p2_sprite_sheet_soldier_spawning_side,
        (f32[]){0.25, 0.25},
        (u8[]){0, 0},
        (u8[]){1, 2},
        2);

    p2_adef_soldier_dying_side = animation_definition_create(
        &p2_sprite_sheet_soldier_dying_side,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.75, 0.5, 0.5, 0.5, 0.75},
        (u8[]){0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        10);

    p2_anim_soldier_idle_side = animation_create(p2_adef_soldier_idle_side, false);
    p2_anim_soldier_running_side = animation_create(p2_adef_soldier_running_side, true);
    p2_anim_soldier_idle_back = animation_create(p2_adef_soldier_idle_back, false);
    p2_anim_soldier_running_back = animation_create(p2_adef_soldier_running_back, true);
    p2_anim_soldier_idle_front = animation_create(p2_adef_soldier_idle_front, false);
    p2_anim_soldier_running_front = animation_create(p2_adef_soldier_running_front, true);
    p2_anim_soldier_spawning_side = animation_create(p2_adef_soldier_spawning_side, true);
    p2_anim_soldier_dying_side = animation_create(p2_adef_soldier_dying_side, true);

    // bullet stuff
    render_sprite_sheet_init(&sprite_sheet_bullet_1_horizontal, "assets/bullet_1_horizontal.png", 5, 5);
    render_sprite_sheet_init(&sprite_sheet_bullet_1_vertical, "assets/bullet_1_vertical.png", 5, 5);
    adef_bullet_1_horizontal = animation_definition_create(
        &sprite_sheet_bullet_1_horizontal,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    adef_bullet_1_vertical = animation_definition_create(
        &sprite_sheet_bullet_1_vertical,
        (f32[]){0},
        (u8[]){0},
        (u8[]){0},
        1);
    anim_bullet_1_horizontal = animation_create(adef_bullet_1_horizontal, false);
    anim_bullet_1_vertical = animation_create(adef_bullet_1_vertical, false);
}

// updates player statuses based on frame counter associated with each playaer
void update_player_status(Player *player)
{
    // check if spawn delay is up
    if (player->status == PLAYER_INACTIVE && player->frames_on_status >= (player->spawn_delay * global.time.frame_rate))
    {
        // update status & reset counter
        player->status = PLAYER_SPAWNING;
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
    else if (player->status == PLAYER_SPAWNING && player->frames_on_status >= (player->spawn_time * global.time.frame_rate))
    {
        player->status = PLAYER_ACTIVE;
        player->frames_on_status = 0;
    }
    // check if health is 0
    else if (player->health <= 0 && player->status == PLAYER_ACTIVE)
    {
        player->status = PLAYER_DESPAWNING;
        player->animation_set->dying->current_frame_index = 0;
        player->frames_on_status = 0;

        // shouldn't be moving on death anim
        player->entity->body->velocity[0] = 0;
        player->entity->body->velocity[1] = 0;
    }
    // check if death animation is complete
    else if (player->status == PLAYER_DESPAWNING && player->frames_on_status >= (player->despawn_time * global.time.frame_rate))
    {
        player->status = PLAYER_INACTIVE;
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

// updates player animations based on direction
void update_player_animations(Player *player)
{
    if (player->status == PLAYER_ACTIVE)
    {
        if (player->direction == RIGHT || player->direction == LEFT)
        {
            player->entity->animation = player->entity->body->velocity[0] != 0 ? player->animation_set->side_moving : player->animation_set->side_idle; // anim_soldier_running_side : anim_soldier_idle_side;
            player->entity->animation->is_flipped = player->direction == LEFT ? true : false;
        }
        else if (player->direction == UP)
        {
            player->entity->animation = player->entity->body->velocity[1] != 0 ? player->animation_set->up_moving : player->animation_set->up_idle; // anim_soldier_running_back : anim_soldier_idle_back;
        }
        else if (player->direction == DOWN)
        {
            player->entity->animation = player->entity->body->velocity[1] != 0 ? player->animation_set->down_moving : player->animation_set->down_idle; // anim_soldier_running_front : anim_soldier_idle_front;
        }
        else
        {
            ERROR_EXIT(-1, "Player direction not recognized");
        }
    }
    else if (player->status == PLAYER_SPAWNING)
    {
        player->entity->animation = player->animation_set->spawning;
    }
    else if (player->status == PLAYER_DESPAWNING)
    {
        player->entity->animation = player->animation_set->dying;
    }
}

void handle_player_shooting(Player *player)
{
    if (player->weapon->current_capacity > 0) // only generate bullet if weapon is loaded
    {
        vec2 bullet_position = {player->entity->body->aabb.position[0], player->entity->body->aabb.position[1]};
        vec2 bullet_velocity = {0, 0};
        Animation *bullet_anim = anim_bullet_1_horizontal;
        if (player->direction == UP)
        {
            bullet_position[1] += 25;
            bullet_velocity[1] = 1200;
            bullet_anim = anim_bullet_1_vertical;
        }
        else if (player->direction == RIGHT)
        {
            bullet_position[0] += 25;
            bullet_velocity[0] = 1200;
        }
        else if (player->direction == DOWN)
        {
            bullet_position[1] -= 25;
            bullet_velocity[1] = -1200;
            bullet_anim = anim_bullet_1_vertical;
        }
        else if (player->direction == LEFT)
        {
            bullet_position[0] -= 25;
            bullet_velocity[0] = -1200;
        }
        else
        {
            ERROR_EXIT(NULL, "Player direction not recognized");
        }
        Entity *bullet = entity_create(bullet_position, (vec2){5, 5}, (vec2){0, 0}, COLLISION_LAYER_BULLET, bullet_mask, bullet_on_hit, bullet_on_hit_static);
        bullet->animation = bullet_anim;
        bullet->body->velocity[0] = bullet_velocity[0];
        bullet->body->velocity[1] = bullet_velocity[1];

        // decrement weapon capacity
        player->weapon->current_capacity -= 1;

        // restart rpm timer
        player->weapon->ready_to_fire = false;
        player->weapon->frames_since_last_shot = 0;
    }
}

// handles key inputs of players
void handle_player_input(Player *player)
{
    if (player->status != PLAYER_ACTIVE) // don't allow inputs on inactive players
    {
        return;
    }
    Key_State left = player->is_left_player ? global.input.l_left : global.input.r_left;
    Key_State right = player->is_left_player ? global.input.l_right : global.input.r_right;
    Key_State up = player->is_left_player ? global.input.l_up : global.input.r_up;
    Key_State down = player->is_left_player ? global.input.l_down : global.input.r_down;
    Key_State shoot = player->is_left_player ? global.input.l_shoot : global.input.r_shoot;

    f32 velx = 0;
    f32 vely = 0;

    // 4 directional movement only, no diagonals
    if (right)
    {
        player->direction = RIGHT;
        velx += 150;
    }

    else if (left)
    {
        player->direction = LEFT;
        velx -= 150;
    }

    else if (up)
    {
        player->direction = UP;
        vely += 150;
    }

    else if (down)
    {
        player->direction = DOWN;
        vely -= 150;
    }

    // handle weapon attribute updates & bullet generationm, contingent on fire mode, input, and weapon shot cooldown
    if (player->weapon->fire_mode == AUTO && shoot == KS_HELD && player->weapon->ready_to_fire)
    {
        handle_player_shooting(player);
    }
    if (player->weapon->fire_mode == SEMI && shoot == KS_PRESSED && player->weapon->ready_to_fire)
    {
        handle_player_shooting(player);
    }
    if (player->weapon->fire_mode == BURST)
    {
        // TODO: Not implemented
    }
    player->entity->body->velocity[0] = velx;
    player->entity->body->velocity[1] = vely;
}

Player *get_player_from_body(Player *player_one, Player *player_two, Body *body, bool return_other_player)
{
    if (player_one->entity->body == body)
    {
        return !return_other_player ? player_one : player_two;
    }
    else if (player_two->entity->body == body)
    {
        return !return_other_player ? player_two : player_one;
    }
    else
    {
        return NULL;
    }
}