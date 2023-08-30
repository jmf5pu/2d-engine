#include <stdlib.h>
#include <string.h>
#include "../util.h"
#include "../array_list.h"

Array_List *array_list_create(usize item_size, usize initial_capacity)
{
    Array_List *list = malloc(sizeof(Array_List));

    if (!list)
    {
        ERROR_RETURN(NULL, "Could not allocate memory for Array_List\n");
    }

    list->item_size = item_size;
    list->capacity = initial_capacity;
    list->len = 0;
    list->items = malloc(item_size * initial_capacity);

    if (!list->items)
    {
        ERROR_RETURN(NULL, "Could not allocate memory for Array_List\n");
    }

    return list;
}

void *array_list_get(Array_List *list, usize index, char *description)
{
    if ((u32)index >= (u32)list->len)
    {
        printf("Description: %s [list->len: %zd] [index: %zd]\n", description, list->len, index);
        ERROR_RETURN(NULL, "Index out of bounds (get)");
    }
    void **stored_item = (void **)((u8 *)list->items + index * sizeof(void *));
    return *stored_item;
}

usize array_list_append(Array_List *list, void *item)
{
    if (list->len == list->capacity)
    {
        list->capacity = list->capacity > 0 ? list->capacity * 2 : 1;
        void **items = (void **)realloc(list->items, sizeof(void *) * list->capacity);

        if (!items)
        {
            ERROR_RETURN(-1, "Could not allocate memory for Array_List\n");
        }

        list->items = items;
    }

    usize index = list->len++;
    void **stored_item = (void **)((u8 *)list->items + index * sizeof(void *));
    *stored_item = item;
    return index;
}

void array_list_remove(Array_List *list, usize index)
{
    if (index >= list->len)
    {
        printf("Index out of bounds (remove) [list->len: %zd] [index: %zd]\n", list->len, index);
        return;
    }

    // Move elements after the removed index one position back
    for (usize i = index; i < list->len - 1; ++i)
    {
        void **current_item = (void **)((u8 *)list->items + i * sizeof(void *));
        void **next_item = (void **)((u8 *)list->items + (i + 1) * sizeof(void *));
        *current_item = *next_item;
    }

    // Update the length of the list
    list->len--;

    // Check if the number of elements is significantly lower than capacity
    if (list->len < list->capacity / 2)
    {
        usize new_capacity = list->capacity / 2;
        if (new_capacity < 1)
            new_capacity = 1;

        // Reallocate memory to fit the new capacity
        void **new_items = (void **)realloc(list->items, sizeof(void *) * new_capacity);
        if (new_items)
        {
            list->items = new_items;
            list->capacity = new_capacity;
        }
    }
}

void array_list_clear(Array_List *list)
{
    for (usize i = 0; i < list->len; ++i)
    {
        void *item = array_list_get(list, i, "Clearing ArrayList");
        free(item);
    }

    list->len = 0;
}