#ifndef STRUCTS_H
#define STRUCTS_H

#define MENU_MAX_LINES 10
#define MENU_MAX_LINE_LENGTH 50

#include "engine/animation.h"
#include "engine/entity.h"
#include "engine/input/input.h"
#include "engine/render.h"
#include "engine/types.h"

enum Pickup_Name { M44_PICKUP, BREWSTER_PICKUP };

enum Player_Status {
    PLAYER_SPAWNING,
    PLAYER_ACTIVE,
    PLAYER_RELOADING,
    PLAYER_INTERACTING,
    PLAYER_DESPAWNING,
    PLAYER_INACTIVE,
};

enum Enemy_Status {
    ENEMY_ACTIVE,
    ENEMY_DESPAWNING,
    ENEMY_INACTIVE,
};

enum Pickup_Status { PICKUP_ACTIVE, PICKUP_INACTIVE, PICKUP_SPAWNING };

enum Fire_Mode { AUTO, SEMI, BURST };

typedef struct player_key_state {
    Key_State left;
    Key_State right;
    Key_State up;
    Key_State down;
    Key_State shoot;
    Key_State reload;
    Key_State use;
    Key_State pause;
} Player_Key_State;

typedef struct player_input_state {
    Controller_Input_State *controller_input_state;
    Player_Key_State *key_state;
} Player_Input_State;

typedef struct player Player; // forward dec for OnShoot
typedef void (*OnShoot)(Player *player);

typedef struct weapon_type Weapon_Type;
typedef struct weapon {
    u16 capacity;
    u16 reserve;
    i8 burst_shots_remaining;
    u16 frames_since_last_shot;
    bool ready_to_fire;
    bool is_firing;
    Animation *character_anim;
    vec2 position;
    Weapon_Type *weapon_type;
} Weapon;

typedef struct weapon_type {
    char *name;
    enum Fire_Mode fire_mode;
    u16 capacity;      // max ammo in a magazine
    u16 reserve;       // maximum amount of spare ammo
    u16 max_fire_rate; // rounds per minute
    u16 burst_count;   // maximum number of shots in a "burst", both burst
                       // attributes will be null if Fire_Mode != BURST
    f32 burst_delay;   // in seconds
    i16 damage;
    i16 bullet_velocity;
    u16 reload_frame_delay;
    u16 pickup_frame_delay;
    char *muzzle_flash_id;
    Animation_Definition *bullet_adef;
    Animation_Definition *bullet_impact_adef;
    char *blood_splatter_prefix;
    Animation *hud_ammo_icon;
    OnShoot on_shoot; // handles bullet entity creation when the weapon is fired
} Weapon_Type;

typedef struct pickup_animation_set {
    Animation *active;
    Animation *spawning;
} Pickup_Animation_Set;

typedef struct armor {
    char *name;
    i16 integrity;
} Armor;

typedef struct camera {
    vec2 position;
    vec2 *target_position;
    vec4 buffer;
} Camera;
typedef struct player {
    Entity *entity;
    Entity *crosshair;
    Entity *interact_bar;
    Camera *camera;
    Weapon *weapon;
    Armor *armor;
    vec2 spawn_point;
    vec2 relative_position; // position relative to the rest of the map NOT
                            // to the window
    enum Player_Status status;
    Player_Input_State *input_state;
    f32 render_scale_factor; // render scale factor (determines FOV of the
                             // player). Normal is 0.5, render width is 0.5
                             // of window width
    f32 despawn_time;        // time it takes for animation to complete after
                             // health <=
                             // 0
    f32 spawn_delay;         // time in s from INACTIVE status to SPAWNING status
    f32 spawn_time;          // time in s from SPAWNING status to ACTIVE status
    u16 interact_frame_delay;
    f32 crosshair_angle;
    u32 frames_on_status; // # of frames since last status change
    i16 health;
    bool is_left_player;
} Player;

typedef struct bullet {
    Entity *entity;
    Animation_Definition *impact_adef;
    Animation_Definition *splatter_adef;
    i32 damage;
} Bullet;

typedef struct zombie {
    Entity *entity;
    enum Enemy_Status status;
    f32 despawn_time;
    u32 frames_on_status;
    i16 health;
} Zombie;

typedef struct hud {
    SDL_Window *window;
    Sprite_Sheet_Frame *p1_health_display;
    Sprite_Sheet_Frame *p2_health_display;
} HUD;

typedef struct menu {
    void (*input_handler)(void);
    char items[MENU_MAX_LINES][MENU_MAX_LINE_LENGTH];
    u8 items_count;
    u8 selected_item;
} Menu;

typedef struct time_spawner TimeSpawer;
typedef void (*Spawn)(vec2 spawn_point);

typedef struct time_spawner {
    bool is_active;
    vec2 position;
    u32 wait_frames_remaining;
    u32 max_frames_seconds;
    Spawn spawn;
} TimeSpawner;

typedef enum { TELEPORTER, TELEPORTER_BUTTON, WEAPON_PICKUP_GLOCK, WEAPON_PICKUP_M16, WEAPON_PICKUP_COACH_GUN } DynamicPropType;

typedef enum {
    ACTIVE,
    INACTIVE,
    SPINNING_UP,
    SPINNING_DOWN,
} TeleporterStateEnum;

typedef enum {
    PRESSED,
    UNPRESSED,
} ButtonStateEnum;

typedef enum { NORMAL, HIGHLIGHTING, INTERACTING, USED } PickupStateEnum;
typedef union {
    TeleporterStateEnum teleporter_state_enum;
    ButtonStateEnum button_state_enum;
    PickupStateEnum pickup_state_enum;
} StateEnum;

typedef struct dynamic_prop DynamicProp;

typedef void (*UpdateState)(DynamicProp *prop);
typedef struct dynamic_prop {
    Entity *entity;
    StateEnum state;
    u32 frames_on_state;
    UpdateState update_state;
    DynamicPropType type;     // used to group types of dynamic props when controller interactions between them
    Player *colliding_player; // who is able to interact with this prop
} DynamicProp;

typedef struct map {
    // these indicate the lengths of their respective arrays
    usize num_p1_spawns;
    usize num_p2_spawns;
    usize num_enemy_spawners;
    usize max_enemies;
    usize num_dynamic_props;
    vec2 *player_one_spawn_points; // player one's spawn points
    vec2 *player_two_spawn_points; // player two's spawn points
    TimeSpawner *enemy_spawners;
    DynamicProp **dynamic_props;
} Map;

typedef struct muzzle_flash {
    Entity *entity;
    Body *parent; // body to tie movement to
} MuzzleFlash;

#endif