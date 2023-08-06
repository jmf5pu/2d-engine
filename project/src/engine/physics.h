#ifndef PHYSICS_H
#define PHYSICS_H

#include <linmath.h>
#include "types.h"

// axis-aligned bounding box, rectangle that cannot rotate
typedef struct aabb
{
    vec2 position;
    vec2 half_size;
} AABB;

typedef struct body
{
    AABB aabb;
    vec2 velocity;
    vec2 acceleration;
} Body;

void physics_init(void);
void physics_update(void);
usize physics_body_create(vec2 position, vec2 size);
Body *physics_body_get(usize index);

#endif