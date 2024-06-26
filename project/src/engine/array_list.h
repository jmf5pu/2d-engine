#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include "types.h"
#include <stdbool.h>

typedef struct array_list {
    usize len;
    usize capacity;
    usize item_size;
    void *items;
} Array_List;

Array_List *array_list_create(usize item_size, usize initial_capacity);
usize array_list_append(Array_List *list, void *item);
void *array_list_get(Array_List *list, usize index);
void array_list_remove(Array_List *list, usize index);
void array_list_clear(Array_List *list, bool free_elements);
void free_array_list(Array_List *list);

#endif