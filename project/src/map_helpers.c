#include "engine./util.h"
#include "engine/global.h"
#include "map_helpers.h"
#include "collision_behavior.h"
#include <stdlib.h>

Map map;

// set up map & props
void init_map(Map *map)
{
    map->num_pickups = 2;
    map->num_props = 3;

    Sprite_Sheet *sprite_sheet_map_1_main_bg = malloc(sizeof(Sprite_Sheet));
    render_sprite_sheet_init(sprite_sheet_map_1_main_bg, "assets/map_1.png", 640, 360);
    Sprite *map_1_main_bg = malloc(sizeof(Sprite));
    map_1_main_bg->sprite_sheet = sprite_sheet_map_1_main_bg;
    map_1_main_bg->row = 0;
    map_1_main_bg->column = 0;
    map_1_main_bg->position[0] = 320;
    map_1_main_bg->position[1] = 180;
    map_1_main_bg->half_size[0] = 640;
    map_1_main_bg->half_size[1] = 360;
    map_1_main_bg->z_index = -5;
    map_1_main_bg->is_flipped = false;
    map_1_main_bg->color[0] = 1;
    map_1_main_bg->color[1] = 1;
    map_1_main_bg->color[2] = 1;
    map_1_main_bg->color[3] = 1;
    Prop background_prop = (Prop){
        .sprite = map_1_main_bg,
        .layer_threshold = INT32_MIN, // this prop should ALWAYS render before (underneath) everything else
        .static_body = NULL,
    };

    Sprite_Sheet *sprite_sheet_chain_link_fence_horizontal_wide = malloc(sizeof(Sprite_Sheet));
    render_sprite_sheet_init(sprite_sheet_chain_link_fence_horizontal_wide, "assets/chain_link_fence_horizontal_wide_no_concrete_barbed_wire.png", 640, 75);
    Sprite *chain_link_fence_horizontal_wide = malloc(sizeof(Sprite));
    chain_link_fence_horizontal_wide->sprite_sheet = sprite_sheet_chain_link_fence_horizontal_wide;
    chain_link_fence_horizontal_wide->row = 0;
    chain_link_fence_horizontal_wide->column = 0;
    chain_link_fence_horizontal_wide->position[0] = 317;
    chain_link_fence_horizontal_wide->position[1] = 36;
    chain_link_fence_horizontal_wide->half_size[0] = 320;
    chain_link_fence_horizontal_wide->half_size[1] = 37.5;
    chain_link_fence_horizontal_wide->z_index = -3;
    chain_link_fence_horizontal_wide->is_flipped = false;
    chain_link_fence_horizontal_wide->color[0] = 1;
    chain_link_fence_horizontal_wide->color[1] = 1;
    chain_link_fence_horizontal_wide->color[2] = 1;
    chain_link_fence_horizontal_wide->color[3] = 1;
    Prop chain_link_fence_bottom_prop = (Prop){
        .sprite = chain_link_fence_horizontal_wide,
        .layer_threshold = 25,
        .static_body = physics_static_body_create((vec2){320, 10}, (vec2){640, 3}, COLLISION_LAYER_TERRIAN),
    };

    Sprite_Sheet *sprite_sheet_traffic_cone = malloc(sizeof(Sprite_Sheet));
    render_sprite_sheet_init(sprite_sheet_traffic_cone, "assets/traffic_cone_square.png", 9, 13);
    Sprite *traffic_cone = malloc(sizeof(Sprite));
    traffic_cone->sprite_sheet = sprite_sheet_traffic_cone;
    traffic_cone->row = 0;
    traffic_cone->column = 0;
    traffic_cone->position[0] = 75;
    traffic_cone->position[1] = 75;
    traffic_cone->half_size[0] = 4.5;
    traffic_cone->half_size[1] = 6.5;
    traffic_cone->z_index = -3;
    traffic_cone->is_flipped = false;
    traffic_cone->color[0] = 1;
    traffic_cone->color[1] = 1;
    traffic_cone->color[2] = 1;
    traffic_cone->color[3] = 1;
    Prop traffic_cone_prop = (Prop){
        .sprite = traffic_cone,
        .layer_threshold = 4,
        .static_body = NULL,
    };

    Prop *prop_array = malloc(map->num_props * sizeof(Prop));

    if (!prop_array)
    {
        // Handle memory allocation error
        // ...
    }

    // populate prop array
    prop_array[0] = background_prop;
    prop_array[1] = chain_link_fence_bottom_prop;
    prop_array[2] = traffic_cone_prop;

    /*
     * initializing pickups
     */

    Pickup *pickup_array = malloc(map->num_pickups * sizeof(Pickup));

    // m44 pickup
    Sprite_Sheet *sprite_sheet_m44 = malloc(sizeof(Sprite_Sheet));
    Sprite_Sheet *sprite_sheet_m44_spawning = malloc(sizeof(Sprite_Sheet));
    Animation_Definition *adef_m44 = malloc(sizeof(Animation_Definition));
    Animation_Definition *adef_m44_spawning = malloc(sizeof(Animation_Definition));
    Animation *anim_m44 = malloc(sizeof(Animation));
    Animation *anim_m44_spawning = malloc(sizeof(Animation));
    render_sprite_sheet_init(sprite_sheet_m44, "assets/m44.png", 30, 15);
    adef_m44 = animation_definition_create(
        sprite_sheet_m44,
        (f32[]){0},
        (u8[]){0},
        (u8[]){1},
        1);
    anim_m44 = animation_create(adef_m44, false);
    render_sprite_sheet_init(sprite_sheet_m44_spawning, "assets/m44_spawning.png", 30, 15);
    adef_m44_spawning = animation_definition_create(
        sprite_sheet_m44_spawning,
        (f32[]){0.25, 0.25},
        (u8[]){0},
        (u8[]){1, 2},
        2);
    anim_m44_spawning = animation_create(adef_m44_spawning, true);

    Pickup_Animation_Set *m44_pickup_animation_set = malloc(sizeof(Pickup_Animation_Set));
    m44_pickup_animation_set->active = anim_m44;
    m44_pickup_animation_set->spawning = anim_m44_spawning;

    Pickup m44_pickup = (Pickup){
        .entity = entity_create((vec2){340, 75}, (vec2){30, 20}, (vec2){0, 0}, COLLISION_LAYER_PICKUP, bullet_mask, pickup_on_hit, pickup_on_hit_static),
        .animation_set = m44_pickup_animation_set,
        .name = M44_PICKUP,
        .status = PICKUP_ACTIVE,
        .spawn_delay = 5,
        .spawn_time = 3,
        .frames_on_status = 0};

    m44_pickup.entity->animation = anim_m44;

    // brewster body armor pickup
    Sprite_Sheet *sprite_sheet_brewster = malloc(sizeof(Sprite_Sheet));
    Sprite_Sheet *sprite_sheet_brewster_spawning = malloc(sizeof(Sprite_Sheet));
    Animation_Definition *adef_brewster = malloc(sizeof(Animation_Definition));
    Animation_Definition *adef_brewster_spawning = malloc(sizeof(Animation_Definition));
    Animation *anim_brewster = malloc(sizeof(Animation));
    Animation *anim_brewster_spawning = malloc(sizeof(Animation));
    render_sprite_sheet_init(sprite_sheet_brewster, "assets/brewster_body_shield.png", 22, 22);
    adef_brewster = animation_definition_create(
        sprite_sheet_brewster,
        (f32[]){0},
        (u8[]){0},
        (u8[]){1},
        1);
    anim_brewster = animation_create(adef_brewster, false);
    render_sprite_sheet_init(sprite_sheet_brewster_spawning, "assets/brewster_body_shield.png", 22, 22);
    adef_brewster_spawning = animation_definition_create(
        sprite_sheet_brewster_spawning,
        (f32[]){0},
        (u8[]){0},
        (u8[]){1},
        1);
    anim_brewster_spawning = animation_create(adef_brewster_spawning, false);

    Pickup_Animation_Set *brewster_pickup_animation_set = malloc(sizeof(Pickup_Animation_Set));
    brewster_pickup_animation_set->active = anim_brewster;
    brewster_pickup_animation_set->spawning = anim_brewster_spawning;

    Pickup brewster_pickup = (Pickup){
        .entity = entity_create((vec2){340, 200}, (vec2){22, 22}, (vec2){0, 0}, COLLISION_LAYER_PICKUP, bullet_mask, pickup_on_hit, pickup_on_hit_static),
        .animation_set = brewster_pickup_animation_set,
        .name = BREWSTER_PICKUP,
        .status = PICKUP_ACTIVE,
        .spawn_delay = 5,
        .spawn_time = 3,
        .frames_on_status = 0};

    brewster_pickup.entity->animation = anim_brewster;

    pickup_array[0] = m44_pickup;
    pickup_array[1] = brewster_pickup;

    // populate map struct
    map->pickups = pickup_array;
    map->props = prop_array;
}

// updates the status of a pickup, should be called once per frame for each pickup
void update_pickup_status(Pickup *pickup)
{
    // inactive to spawning
    if (pickup->status == PICKUP_INACTIVE && pickup->frames_on_status >= (pickup->spawn_delay * global.time.frame_rate))
    {

        pickup->status = PICKUP_SPAWNING;
        pickup->entity->body->is_active = true;
        pickup->frames_on_status = 0;
    }
    // spawning to active
    else if (pickup->status == PICKUP_SPAWNING && pickup->frames_on_status >= (pickup->spawn_time * global.time.frame_rate))
    {

        pickup->status = PICKUP_ACTIVE;
        pickup->frames_on_status = 0;
    }

    // active to inactive is handled in player_on_hit in collision_behavior.c

    pickup->frames_on_status++;
}

// updates pickup animations, should be called once per frame for each pickup
void update_pickup_animations(Pickup *pickup)
{
    if (pickup->status == PICKUP_SPAWNING)
    {
        pickup->entity->animation = pickup->animation_set->spawning;
    }
    else if (pickup->status == PICKUP_ACTIVE)
    {
        pickup->entity->animation = pickup->animation_set->active;
    }
}

// updates all pickup statuses and animations, should be called once per frame
void update_map(Map *map)
{
    for (int i = 0; i < map->num_pickups; i++)
    {
        update_pickup_status(&map->pickups[i]);
        update_pickup_animations(&map->pickups[i]);
    }
}

// frees all map attributes that used malloc to init
void free_map_attributes(Map *map)
{
    for (int i = 0; i < map->num_props; i++)
    {
        free(&map->props->sprite);
        free(&map->props->static_body);
        free(&map->props[i]);
    }
    for (int i = 0; i < map->num_pickups; i++)
    {
        free(&map->pickups[i]);
    }

    free(map->props);
    free(map->pickups);
}

// returns the pickup associated with a physics body if it exists in the current map, returns NULL if not found
Pickup *get_pickup_from_body(Body *body)
{
    if (!map.pickups)
    {
        ERROR_RETURN(1, "Map not yet initialized or initialized incorrectly.")
    }

    for (int i = 0; i < map.num_pickups; i++)
    {
        if (map.pickups[i].entity->body == body)
        {
            return &map.pickups[i];
        }
    }

    return NULL;
}