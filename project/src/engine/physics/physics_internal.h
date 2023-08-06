#ifndef PHYSICS_INTERNAL_H
#define PHYSICS_INTERNAL_H

#include "../array_list.h"
#include "../types.h"

typedef struct physics_state_internal
{
    Array_List *body_list;
} Physics_State_Internal;

#endif