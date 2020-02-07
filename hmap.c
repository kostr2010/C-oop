// this file contains hash map methods implementation

//====================
// INCLUDES

#include <stdlib.h>
#include <stdio.h>

#include "hmap.h"

//====================
// STRUCTURES

struct _HMap {
    struct _Box obj;

    char *name;
};
typedef struct _HMap HMap;

//====================
// METHODS IMPLEMENTATION

Box *hmap_create() {
    Box *obj = calloc(1, sizeof(Box));
    obj->destroy = hmap_destroy;

    return obj;
}

void *hmap_destroy(Box *obj) {
    free(obj);
    printf("hmap dead \n");
}