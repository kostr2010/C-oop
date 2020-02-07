// this file contains meta-structure implementation, which is
// simply called Box

#pragma once

//====================
// STRUCTURES

struct _Box {
    void *(*destroy)(struct _Box *obj);
};
typedef struct _Box Box;
