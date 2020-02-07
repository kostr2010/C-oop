//this file contains declarations of hash map methods

#pragma once

//====================
// INCLUDES

#include "map.h"

//====================
// METHODS DECLARATION

Map* hmap_create(int (*hash)(int key));
void hmap_destroy(Map* obj);
int  hmap_add(Map* obj, Pair* data);
int  hmap_delete(Map* obj, char* key);
int* hmap_get(Map* obj, char* key);
// ...
