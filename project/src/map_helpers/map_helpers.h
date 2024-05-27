#ifndef MAP_HELPERS_H
#define MAP_HELPERS_H

#include "../engine/physics.h"
#include "../engine/render.h"
#include "../structs.h"

extern const u8 TELEPORTER_DIMENSIONS[];
extern const u8 TELEPORTER_GLOW_DIMENSIONS[];

extern const f32 TELEPORTER_SPIN_UP_DURATIONS[];
extern const u8 TELEPORTER_SPIN_UP_ROWS[];
extern const u8 TELEPORTER_SPIN_UP_COLS[];

extern const f32 TELEPORTER_ACTIVE_DURATIONS[];
extern const u8 TELEPORTER_ACTIVE_ROWS[];
extern const u8 TELEPORTER_ACTIVE_COLS[];

extern const f32 TELEPORTER_SPIN_DOWN_DURATIONS[];
extern const u8 TELEPORTER_SPIN_DOWN_ROWS[];
extern const u8 TELEPORTER_SPIN_DOWN_COLS[];

extern const f32 TELEPORTER_GLOW_DURATIONS[];
extern const u8 TELEPORTER_GLOW_ROWS[];
extern const u8 TELEPORTER_GLOW_COLS[];

extern Map map;

Sprite_Sheet sprite_sheet_bunker_background;
Animation_Definition *adef_bunker_background;
Animation *anim_bunker_background;

// props
Sprite_Sheet sprite_sheet_metal_table_vertical_1;
Animation_Definition *adef_metal_table_vertical_1;
Animation *anim_metal_table_vertical_1;
Sprite_Sheet sprite_sheet_metal_table_vertical_2;
Animation_Definition *adef_metal_table_vertical_2;
Animation *anim_metal_table_vertical_2;

// teleporter prop
Sprite_Sheet sprite_sheet_teleporter_inactive;
Animation_Definition *adef_teleporter_inactive;
Sprite_Sheet sprite_sheet_teleporter_active;
Animation_Definition *adef_teleporter_active;
Sprite_Sheet sprite_sheet_teleporter_spinning;
Animation_Definition *adef_teleporter_spinning;
Sprite_Sheet sprite_sheet_teleporter_glow;
Animation_Definition *adef_teleporter_glow;

// weapon pickups
Sprite_Sheet sprite_sheet_m16_pickup;
Animation_Definition *adef_m16_pickup;
Animation *anim_m16_pickup;
Sprite_Sheet sprite_sheet_glock_pickup;
Animation_Definition *adef_glock_pickup;
Animation *anim_glock_pickup;

void init_map(Map *map);
void init_map_assets(void);
void init_map_props(Map *map);
void init_map_background_prop(void);
void init_metal_table_props(void);
DynamicProp *init_teleporter_prop(void);
void init_pickup_props(void);
void update_map(Map *map);
void update_spawners(Map *map);
void update_dynamic_props(Map *map);
void update_spawner(TimeSpawner *spawner);
void free_map_attributes(Map *map);
void update_all_positions(Map *map, vec2 shift, bool left_player_is_active);

// spawning logic callbacks
void spawn_zombie(vec2 spawn_point);

// dynamic prop logic callbacks & corresponding helpers
void teleporter_update_state(Entity *entity, StateEnum *state);
void teleporter_spin_up_and_down_states(
    Entity *entity, TeleporterStateEnum *teleporter_state_enum, u32 *frames_on_state, TeleporterStateEnum next_state, f32 first_duration, f32 second_duration, f32 third_duration);
void update_adef_frame_durations(Animation_Definition *adef, f32 duration);

#endif