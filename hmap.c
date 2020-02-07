// this file contains hash map methods implementation

//====================
// INCLUDES

#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "hmap.h"

//====================
// CONSTANTS

const int HMAP_SZ_DEFAULT = 10;
const int DLLIST_INIT_SZ = 3;

//====================
// STRUCTURES

struct _HMap {
    struct _Map obj;
    void (*hash)(struct _Map *obj);
    DLList* table;    
};
typedef struct _HMap HMap;

//====================
// METHODS IMPLEMENTATION

int GetHashDefault(int key) {
    return key % 10;
}

Map *hmap_create(int (*hash)(int key)) {
    Map *obj = calloc(1, sizeof(Map));
    obj->destroy = hmap_destroy;

    return obj;
}

void hmap_destroy(Map *obj) {
    free(obj);
    printf("hmap dead \n");
}

int  hmap_add(Map* obj, Pair* data);
int  hmap_delete(Map* obj, char* key);
int* hmap_access(Map* obj, char* key);