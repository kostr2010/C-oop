// this file contains meta-structure implementation, which is
// simply called Map

#pragma once

//====================
// STRUCTURES

struct _Map {
    void  (*destroy)(struct _Map* obj);                             // deallocates all memory, associated with object
    int   (*insert)(struct _Map* obj, void* key, void* value);      // inserts given key and value to the object
    int   (*delete)(struct _Map* obj, void* key);                   // deletes element with given key
    int   (*change)(struct _Map* obj, void* key, void* newValue);   // changes value of given key to the newValue
    void* (*get)(struct _Map* obj, void* key);                      // returns value of given key
    int   (*count_value)(struct _Map* obj, void* value);            // counts all elements with given value in the object
	int   (*size)(struct _Map* obj);                                // returns number of elements in the object
};
typedef struct _Map Map;
