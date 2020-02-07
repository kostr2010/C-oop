//this file contains declarations of hash map methods

#pragma once

//====================
// INCLUDES

#include "map.h"

//====================
// METHODS DECLARATION

/**
 * @brief creates Map object and sets all it's methods to the ones of the hash map
 * 
 * @arg int (*hash)(int key) - pointer to the function, which defines hash function. values must be between 0 and HMAP_SZ_DEFAULT
 * 
 * 
 */
Map* hmap_create(int (*hash)(int key));
void hmap_destroy(Map* obj);
int  hmap_insert(Map* obj, void* key, void* value);
int  hmap_delete(Map* obj, void* key);
int  hmap_change(Map* obj, void* key, void* newValue);
int* hmap_get(Map* obj, char* key);
// ...
