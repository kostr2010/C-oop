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
 * @arg int  (*hash)(void* key)                        - pointer to the function, which defines hash function. values must be between 0 and HMAP_SZ_DEFAULT. if NULL, default function will be assumed, interpretating key as int*
 * @arg int  (*cmp_keys)(void* key1, void* key2)       - pointer to the function, which defines comparation function between two keys. if NULL, default function will be assumed, interpretating keys as int*
 * @arg int  (*cmp_values)(void* value1, void* value2) - pointer to the function, which defines comparation function between two values. if NULL, default function will be assumed, interpretating values as int*
 * @arg int* size                                      - number of boxes in hash table. if hash is NULL, it will be ignored
 * @arg void (*print_key)(void* key)                   - pointer to the function, which prints key. if NULL, default function will be assumed, interpretating key as int*
 * @arg void (*print_value)(void* value)               - pointer to the function, which prints value. if NULL, default function will be assumed, interpretating value as int*
 * @arg void (*free_key)(void* key)                    - function to free the memory, pointed by the key pointer. if NULL, mo memory deallocation for key pointer will be made
 * @arg void (*free_value)(void* value)                - function to free the memory, pointed by the value pointer. if NULL, mo memory deallocation for value pointer will be made
 * 
 * @return Map* HashMap - object with set methods and default values
 */
Map* hmap_create(int (*hash)(void* key), int (*cmp_keys)(void* key1, void* key2), int (*cmp_values)(void* value1, void* value2), int* size, void (*print_key)(void* key), void (*print_value)(void* value), void (*free_key)(void* key), void (*free_value)(void* value));

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
 * @arg Map*  obj   - object, where the data will be inserted
 * @arg void* key   - key
 * @arg void* value - value 
 * 
 * @return int res - 0 if done normally, 1 if executed with errors
 */
int hmap_insert(Map* obj, void* key, void* value);

/**
 * @brief deletes data with given key in the obj structure
 * 
 * @arg Map*  obj - object, where the data will be deleted
 * @arg void* key - key
 * 
 * @return int res - 0 if done normally, 1 if executed with errors (f.ex. no data with this key was found)
 */
int hmap_delete(Map* obj, void* key);

/**
 * @brief changes existing data with given key to the newValue in the obj structure
 * 
 * @arg Map*  obj      - object, where new data will be inserted
 * @arg void* key      - key
 * @arg void* newValue - new value 
 * 
 * @return int res - 0 if done normally, 1 if executed with errors
 */
int hmap_change(Map* obj, void* key, void* newValue);

/**
 * @brief gets the value of the key in the obj structure
 * 
 * @arg Map*  obj - object, where the data will be inserted
 * @arg void* key - key
 * 
 * @return int res - value or NULL
 */
void* hmap_get(Map* obj, void* key);

/**
 * @brief this function counts all entries of the given value
 * 
 * @arg void* value      - value to be counted
 * @arg struct _Map* obj - hash map, in which programm should search
 * 
 * @return int count - times given value was detected 
 */
int hmap_count_value(Map* obj, void* value);

/**
 * @brief this function returns number of elements in given structure
 * 
 * @arg Map* obj - pointer to the object, in which we should count
 * 
 * @return int size - number of elements in structure
 */
int hmap_size(Map* obj);

/**
 * @brief default function for calculating key's hash
 *
 * @arg void* key - key
 * 
 * @return int res - hash of the key
 */
int GetHashDefault(void* key);

/**
 * @brief default function for comparation. compares two values as integers
 * 
 * @arg void* arg1 - pointer to first value
 * @arg void* arg2 - pointer to second value
 * 
 * @return int res - 0 if equal, 1 if arg1 > arg2, -1 if arg1 < arg2
 */
int CompareDefault(void* arg1, void* arg2);

/**
 * @brief this default function prints argument in following format: <"arg">, interpretating it as integer
 * 
 * @arg void* arg - arg
 * 
 * @return none
 */
void PrintDefault(void* arg);

/**
 * @brief default function to free memory, pointed by given pointer. treats it as the variable of int* or similar, e.g. not freing any memory
 * 
 * @arg void* arg - pointer to the variable
 * 
 * @return none
 */
void FreeDefault(void* arg);

// DEBUG FUNCTION
void Print(Map* obj);