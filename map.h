// this file contains meta-structure implementation, which is
// simply called Map

#pragma once

//====================
// STRUCTURES

struct _Pair {
    void* key;
    void* value;
};
typedef struct _Pair Pair;

struct _Map {
    void  (*destroy)(struct _Map* obj);
    int   (*insert)(struct _Map* obj, Pair* data);
    int   (*delete)(struct _Map* obj, void* key);
    int   (*change)(struct _Map* obj, Pair* data);
    void* (*get)(struct _Map* obj, void* key);
};
typedef struct _Map Map;
