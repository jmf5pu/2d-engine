#include "enemy_helpers.h"
#include "../collision_behavior/collision_behavior.h"
#include "../engine/array_list.h"
#include "../player_helpers/player_helpers.h"
#include <float.h>
#include <math.h>

static Array_List *current_enemies;

// calculates distance between two points represented by vec2s
f32 get_distance(vec2 point_a, vec2 point_b) { return abs(sqrt(pow((point_a[0] - point_b[0]), 2) + pow(point_a[1] - point_b[1], 2))); }

// determines if players are visible to the enemies (i.e. valid targets)
bool player_visible(Player *player)
{
    if (!player) // if not split screen and we are checking player two
        return false;
    return player->status != PLAYER_INACTIVE && player->status != PLAYER_SPAWNING && player->status != PLAYER_DESPAWNING;
}

// used by external methods
Array_List *get_all_enemies(void) { return current_enemies; }

// initializes enemy array list
void init_enemies(usize item_size, usize initial_capacity)
{
    current_enemies = array_list_create(sizeof(item_size), initial_capacity);
    init_enemy_adefs();
    init_enemy_adef_hashmap();
}

// initializes a single enemy and adds to current_enemies
void create_enemy(vec2 spawn_point)
{
    if (SPAWN_ENEMIES) {
        Zombie *enemy = malloc(sizeof(Zombie));
        enemy->entity = entity_create(spawn_point, (vec2){25, 25}, (vec2){0, 0}, COLLISION_LAYER_ENEMY, enemy_mask, enemy_on_hit, enemy_on_hit_static);
        enemy->entity->animation = animation_create(adef_zombie_idle_4, true);
        enemy->entity->body->parent = enemy;
        enemy->despawn_time = 1;
        enemy->frames_on_status = 0;
        enemy->health = 100;
        enemy->status = ENEMY_ACTIVE;
        array_list_append(current_enemies, enemy);
    }
}

// updates the statuses, animations, and locations of all enemies in
// current_enemies each frame
void update_current_enemies(void)
{
    for (int i = 0; i < current_enemies->len; i++) {
        // find closest player
        Zombie *zombie = array_list_get(current_enemies, i);

        // free dead enemies & remove from arraylist
        if (zombie->health <= 0) {
            zombie->entity->is_active = false; // marking entity for deletion
            array_list_remove(current_enemies, i);
        }

        if (!player_visible(player_one) && !player_visible(player_two)) {
            zombie->entity->body->velocity[0] = 0;
            zombie->entity->body->velocity[1] = 0;
            continue;
        }

        f32 p1_distance = player_visible(player_one) ? get_distance(player_one->relative_position, zombie->entity->body->aabb.position) : FLT_MAX;
        f32 p2_distance = player_visible(player_two) ? get_distance(player_two->relative_position, zombie->entity->body->aabb.position) : FLT_MAX;
        Player *closest_player = p1_distance < p2_distance ? player_one : player_two;

        // calculate enemy movement vector
        f32 x_dist = closest_player->relative_position[0] - zombie->entity->body->aabb.position[0];
        f32 y_dist = closest_player->relative_position[1] - zombie->entity->body->aabb.position[1];

        f32 angle;
        if (x_dist != 0.0)
            angle = atan(y_dist / x_dist);
        else
            angle = (y_dist >= 0.0) ? M_PI / 2.0 : -M_PI / 2.0;

        // Adjust for quadrants
        if (x_dist < 0)
            angle += M_PI;

        zombie->entity->body->velocity[0] = ZOMBIE_MOVEMENT_SPEED * cos(angle);
        zombie->entity->body->velocity[1] = ZOMBIE_MOVEMENT_SPEED * sin(angle);

        update_enemy_anim(zombie);
    }
}
