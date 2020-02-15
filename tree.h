//this file contains declarations of tree methods

#pragma once

//====================
// INCLUDES

#include "map.h"

//====================
// METHODS DECLARATION

typedef int (*cmp_k)(const void *key1, const void *key2);
typedef int (*cmp_v)(const void *val1, const void *val2);

Map *tree_create(cmp_k cmp_k_func, cmp_v cmp_v_func); //

void tree_destroy(Map* obj); //

int tree_insert(Map* obj, const void* key, const void* value); //

int tree_delete(Map* obj, const void* key);

int tree_change(Map* obj, const void* key, const void* new_value); //

void* tree_get(const Map* obj, const void* key); //

int tree_count_value(const Map *obj, const void *value); //

int tree_size(const Map *obj);

