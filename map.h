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
    int   (*compare_keys)(void* key1, void* key2);
    void  (*print_pair)(void* key, void* value);
	void  (*free_key)(void* key);
	void  (*free_value)(void* value);
};
typedef struct _Map Map;
