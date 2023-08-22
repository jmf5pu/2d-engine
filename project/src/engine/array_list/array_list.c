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

u8 array_list_remove(Array_List *list, usize index, char *description)
{
    if (list->len == 0)
    {
        ERROR_RETURN(1, "List is empty\n");
    }
    if (index >= list->len)
    {
        ERROR_RETURN(1, "Index out of bounds (remove)\n");
    }
    if (list->len == 1)
    {
        list->len = 0;
        return 0;
    }

    // Calculate the start and end pointers for the elements to be moved
    u8 *item_ptr = (u8 *)list->items + index * sizeof(void *);
    u8 *end_ptr = (u8 *)list->items + (list->len - 1) * sizeof(void *);

    // Shift the elements after the removed one
    memmove(item_ptr, item_ptr + sizeof(void *), (list->len - index - 1) * sizeof(void *));

    --list->len;

    void **new_items = realloc(list->items, sizeof(void *) * list->len);
    if (new_items == NULL)
    {
        // Handle realloc failure
        ERROR_RETURN(1, "Memory reallocation error\n");
    }
    list->items = new_items;

    printf("%s\n", description);

    return 0;
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