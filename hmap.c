// this file contains hash map methods implementation

//====================
// INCLUDES

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "list.h"
#include "hmap.h"

//====================
// CONSTANTS

const int HMAP_SZ_DEFAULT = 10;
const int DLLIST_INIT_SZ = 2;

//====================
// STRUCTURES

struct _HashMap {
    struct _Map obj;
    int (*hash)(struct _Map *obj);
    DLList* table;    
};
typedef struct _HashMap HashMap;

//====================
// METHODS IMPLEMENTATION

int GetHashDefault(int key) {
    return key % 10;
}

Map *hmap_create(int (*hash)(int key)) {
    HashMap *hmap = calloc(1, sizeof(HashMap));

    if (hash == NULL)
        hmap->hash = GetHashDefault;
    else
        hmap->hash = hash;

    hmap->obj.destroy = hmap_destroy;
    hmap->obj.change = hmap_change;
    hmap->obj.delete = hmap_delete;
    hmap->obj.get = hmap_get;
    hmap->obj.insert = hmap_insert;

    return (Map*)hmap;
}

void hmap_destroy(Map *obj) {
    if (obj != NULL)
        free((HashMap*)obj);
    printf("hmap dead \n");
}

int  hmap_insert(Map* obj, void* key, void* value) {
    assert(obj);
    assert(key);
    assert(value);

    return 0;
}

int  hmap_delete(Map* obj, void* key);
int  hmap_change(Map* obj, void* key, void* newValue);
int* hmap_get(Map* obj, char* key);