// this file contains hash map methods implementation

//====================
// INCLUDES

#include <stdlib.h>
#include <stdio.h>

#include "hmap.h"

//====================
// STRUCTURES

struct _HMap {
    struct _Map obj;

};
typedef struct _HMap HMap;

//====================
// METHODS IMPLEMENTATION

Map *hmap_create() {
    Map *obj = calloc(1, sizeof(Map));
    obj->destroy = hmap_destroy;

    return obj;
}

void *hmap_destroy(Map *obj) {
    free(obj);
    printf("hmap dead \n");
}