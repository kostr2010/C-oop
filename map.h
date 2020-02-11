// this file contains meta-structure implementation, which is
// simply called Map

#pragma once

//====================
// STRUCTURES

struct _Map {
    void  (*destroy)(struct _Map* obj);
    int   (*insert)(struct _Map* obj, void* key, void* value);
    int   (*delete)(struct _Map* obj, void* key);
    int   (*change)(struct _Map* obj, void* key, void* newValue);
    void* (*get)(struct _Map* obj, void* key);
    void  (*print_key)(void* key);
    void  (*print_value)(void* value);
    int   (*count_value)(struct _Map* obj, void* value);
	int (*size)(struct _Map* obj);
};
typedef struct _Map Map;

//later we'll change print_key & print_value with iterators
