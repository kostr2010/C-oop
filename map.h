// this file contains meta-structure implementation, which is
// simply called Map

#pragma once

//====================
// STRUCTURES

struct _Map {
    void  (*destroy)(struct _Map* obj);                             		// deallocates all memory, associated with obj
    int   (*insert)(struct _Map* obj, const void* key, const void* value);	// inserts given key and value to the object
    int   (*delete)(struct _Map* obj, const void* key);                   	// deletes element with given key
    int   (*change)(struct _Map* obj, const void* key, const void* newValue);// changes value of given key to the newValue
    void* (*get)(const struct _Map* obj, const void* key);                	// returns value of given key
    int   (*count_value)(const struct _Map* obj, const void* value);        // counts all elements with given value
	int   (*size)(const struct _Map* obj);                                	// returns number of elements in the object
};
typedef struct _Map Map;
