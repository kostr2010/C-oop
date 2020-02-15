//this file contains declarations of tree methods

#pragma once

//====================
// INCLUDES

#include "map.h"

//====================
// METHODS DECLARATION

typedef int (*cmp_k)(void *key1, void *key2);
typedef int (*cmp_v)(void *val1, void *val2);

Map *tree_create(cmp_k cmp_k_func, cmp_v cmp_v_func); //

void tree_destroy(Map* obj); //

int tree_insert(Map* obj, void* key, void* value); //

int tree_delete(Map* obj, void* key);

int tree_change(Map* obj, void* key, void* new_value); //

void* tree_get(Map* obj, void* key); //

int tree_count_value(Map *obj, void *value); //

int tree_size(Map *obj);

