// this file contains meta-structure implementation, which is
// simply called Map

#pragma once

//====================
// STRUCTURES

struct _Map {
    // deallocates all memory, associated with object
    void  (*destroy)(struct _Map* obj);

    // inserts given key and value to the object
    int   (*insert)(struct _Map* obj, void* key, void* value);

    // deletes element with given key
    int   (*delete)(struct _Map* obj, void* key);

    // changes value of given key to the newValue
    int   (*change)(struct _Map* obj, void* key, void* newValue);

    // returns value of given key
    void* (*get)(struct _Map* obj, void* key);

    // prints key
    void  (*print_key)(void* key);

    // prints value
    void  (*print_value)(void* value);

    // counts all elements with given value in the object
    int   (*count_value)(struct _Map* obj, void* value);
    
    // returns number of elemnts in the object
	int   (*size)(struct _Map* obj);
};
typedef struct _Map Map;

//later we'll change print_key & print_value with iterators
