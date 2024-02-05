#ifndef HASH_MAP_H
#define HASH_MAP_H

// struct key_value_pair;

// Structure to hold a key-value pair
typedef struct key_value_pair {
    char *key;
    void *value; // arbitrary struct pointer
    struct key_value_pair *next;
} Key_Value_Pair;

// Structure for the hash map
typedef struct hash_map {
    int capacity;          // Total number of buckets
    Key_Value_Pair **data; // Array of bucket pointers
} Hash_Map;

Hash_Map *create_hash_map(int capacity);
int hash(char *key, int capacity);
void insert(Hash_Map *map, char *key, void *value);
void *get(Hash_Map *map, char *key);
void destroy_hash_map(Hash_Map *map);

#endif