#ifndef UTIL_H
#define UTIL_H

#include "types.h"
#include <stdio.h>

#define ERROR_EXIT(...)                                                                                                                                                            \
    {                                                                                                                                                                              \
        fprintf(stderr, __VA_ARGS__);                                                                                                                                              \
        exit(1);                                                                                                                                                                   \
    }
#define ERROR_RETURN(R, ...)                                                                                                                                                       \
    {                                                                                                                                                                              \
        fprintf(stderr, __VA_ARGS__);                                                                                                                                              \
        return R;                                                                                                                                                                  \
    }
#define WHITE                                                                                                                                                                      \
    (vec4) { 1, 1, 1, 1 }
#define BLACK                                                                                                                                                                      \
    (vec4) { 0, 0, 0, 1 }
#define RED                                                                                                                                                                        \
    (vec4) { 1, 0, 0, 1 }
#define GREEN                                                                                                                                                                      \
    (vec4) { 0, 1, 0, 1 }
#define BLUE                                                                                                                                                                       \
    (vec4) { 0, 0, 1, 1 }
#define YELLOW                                                                                                                                                                     \
    (vec4) { 1, 1, 0, 1 }
#define CYAN                                                                                                                                                                       \
    (vec4) { 0, 1, 1, 1 }
#define MAGENTA                                                                                                                                                                    \
    (vec4) { 1, 0, 1, 1 }
#define ORANGE                                                                                                                                                                     \
    (vec4) { 1, 0.5, 0, 1 }
#define PURPLE                                                                                                                                                                     \
    (vec4) { 0.5, 0, 1, 1 }
#define TURQUOISE                                                                                                                                                                  \
    (vec4) { 0, 1, 0.5, 1 }
#define GREYED_OUT                                                                                                                                                                 \
    (vec4) { 0.3, 0.3, 0.3, 1 }
#define SEMI_TRANSPARENT                                                                                                                                                           \
    (vec4) { 1, 1, 1, 0.8 }

#define ARRAY_LENGTH(array) (sizeof(array) / sizeof((array)[0]))

#define MAX(a, b) ((a) > (b) ? (a) : (b))

inline f32 get_array_sum(f32 *array, int size)
{
    f32 sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum;
}

#endif
