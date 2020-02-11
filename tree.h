//this file contains declarations of tree methods

#pragma once

//====================
// INCLUDES

#include "map.h"

//====================
// METHODS DECLARATION


Map *tree_create(int (*compare_keys)(void *key1, void *key2),
int (*compare_vals)(void *val1, void *val2),
void (*print_key)(void *key), void (*print_value)(void *value),
void (*free_key)(void *key), void (*free_value)(void *value)); //

void tree_destroy(Map* obj); //

int tree_insert(Map* obj, void* key, void* value); //

int tree_delete(Map* obj, void* key);

int tree_change(Map* obj, void* key, void* new_value); //

void* tree_get(Map* obj, void* key); //

int tree_count_value(Map *obj, void *value); //

int tree_size(Map *obj);

