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

usize array_list_append(Array_List *list, void *item) // TODO: OLD implementation
{
    if (list->len == list->capacity)
    {
        list->capacity = list->capacity > 0 ? list->capacity * 2 : 1; // fix this, poor implementation to just double memory
        void *items = realloc(list->items, list->item_size * list->capacity);

        if (!items)
        {
            ERROR_RETURN(-1, "Could not allocate memory for Array_List\n");
        }

        list->items = items;
    }

    usize index = list->len++;

    memcpy((u8 *)list->items + index * list->item_size, item, list->item_size);

    return index;
}

void *array_list_get(Array_List *list, usize index, char *description)
{
    // TODO: fix error here: Description: called by animation_get [list->len: 5] [index: 0] Index out of bounds(get)
    if ((u32)index >= (u32)list->len)
    {
        printf("Description: %s [list->len: %d] [index: %d]\n", description, list->len, index);
        ERROR_RETURN(NULL, "Index out of bounds (get)");
    }
    return (u8 *)list->items + index * list->item_size;
}

// void *array_list_get(Array_List *list, usize index, char *description) // TODO: NEW implementation
// {
//     if ((u32)index >= (u32)list->len)
//     {
//         printf("Description: %s [list->len: %zd] [index: %zd]\n", description, list->len, index);
//         ERROR_RETURN(NULL, "Index out of bounds (get)");
//     }
//     void **stored_item = (void **)((u8 *)list->items + index * sizeof(void *));
//     return *stored_item;
// }

// usize array_list_append(Array_List *list, void *item)
// {
//     if (list->len == list->capacity)
//     {
//         list->capacity = list->capacity > 0 ? list->capacity * 2 : 1;
//         void **items = (void **)realloc(list->items, sizeof(void *) * list->capacity);

//         if (!items)
//         {
//             ERROR_RETURN(-1, "Could not allocate memory for Array_List\n");
//         }

//         list->items = items;
//     }

//     usize index = list->len++;
//     void **stored_item = (void **)((u8 *)list->items + index * sizeof(void *));
//     *stored_item = item;
//     return index;
// }

// TODO: update this to actually free the unused memory
u8 array_list_remove(Array_List *list, usize index, char *description)
{
    if (list->len == 0) // TODO: replace this with switch logic?
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

    --list->len;

    u8 *item_ptr = (u8 *)list->items + index * list->item_size;
    u8 *end_ptr = (u8 *)list->items + list->len * list->item_size;
    memcpy(item_ptr, end_ptr, list->item_size);
    printf("%s\n", description);
    return 0;
}