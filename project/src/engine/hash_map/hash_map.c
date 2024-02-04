#include "../hash_map.h"
#include "../util.h"
#include <stdlib.h>
#include <string.h>

// Function to create the hash map
Hash_Map *create_hash_map(int capacity) {
  Hash_Map *map = (Hash_Map *)malloc(sizeof(Hash_Map));
  map->capacity = capacity;
  map->data = malloc(sizeof(Key_Value_Pair *) * capacity);
  for (int i = 0; i < capacity; i++) {
    map->data[i] = NULL;
  }
  return map;
}

// Hash function
int hash(char *key, int capacity) {
  int hash = 0;
  for (int i = 0; key[i] != '\0'; i++) {
    hash += key[i];
  }
  return hash % capacity;
}

// Function to insert a key-value pair
void insert(Hash_Map *map, char *key, void *value) {
  int index = hash(key, map->capacity);

  // Create a new key-value pair
  Key_Value_Pair *newPair = malloc(sizeof(Key_Value_Pair));
  newPair->key = strdup(key);
  newPair->value = value;
  newPair->next = NULL;

  // Handle collisions using linked list
  if (map->data[index] == NULL) {
    map->data[index] = newPair;
  } else {
    Key_Value_Pair *current = map->data[index];
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newPair;
  }
}

// Function to retrieve a value by key
void *get(Hash_Map *map, char *key) {
  int index = hash(key, map->capacity);

  // Search for the key in the linked list
  Key_Value_Pair *current = map->data[index];
  while (current != NULL) {
    if (strcmp(current->key, key) == 0) {
      return current->value;
    }
    current = current->next;
  }

  // Key not found
  return NULL;
}

// Function to destroy the hash map and free memory
void destroy_hash_map(Hash_Map *map) {
  for (int i = 0; i < map->capacity; i++) {
    Key_Value_Pair *current = map->data[i];
    while (current != NULL) {
      Key_Value_Pair *temp = current;
      // current = current->next;
      free(temp->key);
      free(temp);
    }
  }
  free(map->data);
  free(map);
}