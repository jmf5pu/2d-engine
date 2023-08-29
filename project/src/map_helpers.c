#include "engine./util.h"
#include "engine/global.h"
#include "map_helpers.h"
#include "collision_behavior.h"

Map map;

// set up map & props
void init_map(Map *map)
{

    map->num_sprites = 3;
    map->num_pickups = 1;
    map->num_static_bodies = 2;

    Sprite_Sheet *sprite_sheet_map_1_main_bg = malloc(sizeof(Sprite_Sheet));
    Sprite_Sheet *sprite_sheet_chain_link_fence_horizontal_wide = malloc(sizeof(Sprite_Sheet));
    Sprite_Sheet *sprite_sheet_shipping_containers_red_and_yellow_back = malloc(sizeof(Sprite_Sheet));

    // init sprite sheets
    render_sprite_sheet_init(sprite_sheet_map_1_main_bg, "assets/map_1.png", 640, 360);
    render_sprite_sheet_init(sprite_sheet_chain_link_fence_horizontal_wide, "assets/chain_link_fence_horizontal_wide_no_concrete_barbed_wire.png", 640, 75);
    render_sprite_sheet_init(sprite_sheet_shipping_containers_red_and_yellow_back, "assets/shipping_containers_red_and_yellow_back.png", 96, 59);

    Sprite map_1_main_bg = (Sprite){
        .sprite_sheet = sprite_sheet_map_1_main_bg,
        .row = 0,
        .column = 0,
        .position = {320, 180},
        .z_index = -3,
        .is_flipped = false,
        .color = {1, 1, 1, 1},
    };

    Sprite chain_link_fence_horizontal_wide = (Sprite){
        .sprite_sheet = sprite_sheet_chain_link_fence_horizontal_wide,
        .row = 0,
        .column = 0,
        .position = {317, 36},
        .z_index = -3,
        .is_flipped = false,
        .color = {1, 1, 1, 1},
    };

    Sprite shipping_containers_red_and_yellow_back = (Sprite){
        .sprite_sheet = sprite_sheet_shipping_containers_red_and_yellow_back,
        .row = 0,
        .column = 0,
        .position = {244, 224},
        .z_index = -3,
        .is_flipped = false,
        .color = {1, 1, 1, 1},
    };

    Sprite *sprite_array = malloc(map->num_sprites * sizeof(Sprite));
    if (!sprite_array)
    {
        // Handle memory allocation error
        // ...
    }

    sprite_array[0] = map_1_main_bg;
    sprite_array[1] = chain_link_fence_horizontal_wide;
    sprite_array[2] = shipping_containers_red_and_yellow_back;

    // init static bodies TODO: will need to create array like above when we have more than 1
    Static_Body *bottom_fence = physics_static_body_create((vec2){320, 10}, (vec2){640, 3}, COLLISION_LAYER_TERRIAN);
    Static_Body *shipping_containers = physics_static_body_create((vec2){322, 165}, (vec2){32, 26}, COLLISION_LAYER_TERRIAN);

    Static_Body *static_body_array = malloc(map->num_static_bodies * sizeof(Static_Body));
    static_body_array[0] = *bottom_fence;
    static_body_array[1] = *shipping_containers;

    // init pickups
    render_sprite_sheet_init(&sprite_sheet_m44_spinning, "assets/m44_spinning.png", 30, 20);
    adef_m44_spinning = animation_definition_create(
        &sprite_sheet_m44_spinning,
        (f32[]){0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1},
        (u8[]){0},
        (u8[]){1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
        12);
    anim_m44_spinning = animation_create(adef_m44_spinning, true);

    Pickup m44_pickup = (Pickup){
        .entity = entity_create((vec2){340, 75}, (vec2){30, 20}, (vec2){0, 0}, COLLISION_LAYER_PICKUP, bullet_mask, pickup_on_hit, pickup_on_hit_static),
        .name = M44_PICKUP,
        .status = PICKUP_ACTIVE,
        .spawn_delay = 5,
        .spawn_time = 3,
        .frames_on_status = 0};
    m44_pickup.entity->animation = anim_m44_spinning;

    Pickup *pickup_array = malloc(map->num_pickups * sizeof(Pickup));
    // TODO: handle malloc failure here
    pickup_array[0] = m44_pickup;

    map->sprites = sprite_array;
    map->pickups = pickup_array;
    map->static_bodies = static_body_array;
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
    }
    else if (pickup->status == PICKUP_ACTIVE)
    {
        pickup->entity->animation = anim_m44_spinning;
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
    for (int i = 0; i < map->num_sprites; i++)
    {
        free(&map->sprites[i]);
    }
    for (int i = 0; i < map->num_pickups; i++)
    {
        free(&map->pickups[i]);
    }

    free(map->static_bodies);
    free(map->sprites);
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