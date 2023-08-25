#include "map_helpers.h"
#include "collision_behavior.h"

// set up map & props
void init_map(Map *map)
{
    Sprite_Sheet *sprite_sheet_shipping_container_red_front = malloc(sizeof(Sprite_Sheet));
    Sprite_Sheet *sprite_sheet_shipping_container_red_back = malloc(sizeof(Sprite_Sheet));

    // init sprite sheets
    render_sprite_sheet_init(sprite_sheet_shipping_container_red_front, "assets/shipping_container_red_front.png", 52, 63);
    render_sprite_sheet_init(sprite_sheet_shipping_container_red_back, "assets/shipping_container_red_back.png", 52, 59);

    Sprite shipping_container_red_front = (Sprite){
        .sprite_sheet = sprite_sheet_shipping_container_red_front,
        .row = 0,
        .column = 0,
        .position = {320, 148},
        .z_index = -1,
        .is_flipped = false,
        .color = {1, 1, 1, 1},
    };
    Sprite shipping_container_red_back = (Sprite){
        .sprite_sheet = sprite_sheet_shipping_container_red_back,
        .row = 0,
        .column = 0,
        .position = {320, 209},
        .z_index = 1,
        .is_flipped = false,
        .color = {1, 1, 1, 1},
    };

    Sprite *sprite_array = malloc(2 * sizeof(Sprite));
    if (!sprite_array)
    {
        // Handle memory allocation error
        // ...
    }
    sprite_array[0] = shipping_container_red_front;
    sprite_array[1] = shipping_container_red_back;

    // init static bodies
    Static_Body *red_shipping_container_static_body = physics_static_body_create((vec2){322, 165}, (vec2){32, 26}, COLLISION_LAYER_TERRIAN);

    map->num_sprites = 2;
    map->num_static_bodies = 1;
    map->sprites = sprite_array;
    map->static_bodies = red_shipping_container_static_body;
}
