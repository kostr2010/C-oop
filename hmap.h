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
 * @arg int (*hash)(void* key) - pointer to the function, which defines hash function. values must be between 0 and HMAP_SZ_DEFAULT. if NULL, default function will be assumed, interpretating key as int*
 * @arg int (*cmp)(void* key1, void* key2) - pointer to the function, which defines comparation function. if NULL, default function will be assumed, interpretating keys as int*
 * @arg int* size - number of boxes in hash table. if hash is NULL, it will be ignored
 * @erg void (*print_pair)(void* key, void* value) - pointer to the function, which prints elements of the pair. if NULL, default function will be assumed, interpretating key and value as int*
 * 
 * @return Map* HashMap - object with set methods and default values
 */
Map* hmap_create(int (*hash)(void* key), int (*cmp)(void* key1, void* key2), int* size, void (*print_pair)(void* key, void* value));

/**
 * @brief destroys allocated HashMap object, freeing all associated memory
 * 
 * @arg Map* obj - object to be freed
 * 
 * @return none
 */
void hmap_destroy(Map* obj);

/**
 * @brief inserts data with given parameters to the obj structure
 * 
 * @arg Map* obj  - object, where the data will be inserted
 * @arg void* key - key
 * @arg void* value - value 
 * 
 * @return int res - 0 if done normally, 1 if executed with errors
 */
int  hmap_insert(Map* obj, void* key, void* value);

/**
 * @brief deletes data with given key in the obj structure
 * 
 * @arg Map* obj  - object, where the data will be deleted
 * @arg void* key - key
 * 
 * @return int res - 0 if done normally, 1 if executed with errors (f.ex. no data with this key was found)
 */
int  hmap_delete(Map* obj, void* key);

/**
 * @brief changes existing data with given key to the newValue in the obj structure
 * 
 * @arg Map* obj  - object, where new data will be inserted
 * @arg void* key - key
 * @arg void* newValue - new value 
 * 
 * @return int res - 0 if done normally, 1 if executed with errors
 */
int  hmap_change(Map* obj, void* key, void* newValue);

/**
 * @brief gets the value of the key in the obj structure
 * 
 * @arg Map* obj  - object, where the data will be inserted
 * @arg void* key - key
 * 
 * @return int res - value or NULL
 */
void* hmap_get(Map* obj, void* key);

/**
 * @brief default function for comparation. compares two keys
 * 
 * @arg void* key1 - first key
 * @arg void* key2 - second key
 * 
 * @return int res - 0 equal, 1 if key1 > key2, -1 if key1 < key2
 */
int  CompareKeysDefault(void* key1, void* key2);

/**
 * @brief default function for calculating key's hash
 *
 * @arg void* key - key
 * 
 * @return int res - hash of the key
 */
int GetHashDefault(void* key);

/**
 * @brief this function dictates how to interpretate given value and key and prints them in following format: <"key", "value">
 * 
 * @arg void* key - key
 * @arg void* value - value 
 * 
 * @return none
 */
void PrintPairDefault(void* key, void* value);

// DEBUG FUNCTION
void Print(Map* obj);