// this file contains meta-structure implementation, which is
// simply called Map

#pragma once

//====================
// STRUCTURES

struct _Map {
    void *(*destroy)(struct _Map *obj);
};
typedef struct _Map Map;
