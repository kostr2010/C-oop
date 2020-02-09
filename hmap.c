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
const int DLLIST_INIT_SZ = 1;

//====================
// STRUCTURES

struct _HashMap {
    struct _Map obj;
    
    DLList* table;    
    int size;
    
    int  (*hash)(void* key);
    void (*free_key)(void* key);
	void (*free_value)(void* value);
};
typedef struct _HashMap HashMap;

//====================
// METHODS IMPLEMENTATION

int GetHashDefault(void* key) {
    assert(key);

    return *(int*)key % 10;
}

int CompareKeysDefault(void* key1, void* key2) {
    assert(key1);
    assert(key2);

    if (*(int*)key1 == *(int*)key2)
        return 0;
    else if (*(int*)key1 < *(int*)key2)
        return -1;
    else 
        return 1;
}

void PrintPairDefault(void* key, void* value) {
    assert(key);
    assert(value);

    printf("\"%d\", \"%d\"", *(int*)key, *(int*)value);

    return;
}

void FreeKeyDefault(void* key) {
    assert(key);

    return;
}

void FreeValueDefault(void* value) {
    assert(value);

    return;
}

Map *hmap_create(int (*hash)(void* key), int (*cmp)(void* key1, void* key2), int* size, void (*print_pair)(void* key, void* value), void (*free_key)(void* key), void (*free_value)(void* value)) {
    HashMap *hmap = calloc(1, sizeof(HashMap));

    if (hash == NULL) {
        hmap->hash = GetHashDefault;
        hmap->size = HMAP_SZ_DEFAULT;
    } else {
        hmap->hash = hash;
        hmap->size = *size;
    }

    if (free_key == NULL)
        hmap->free_key = FreeKeyDefault;
    else
        hmap->free_key = free_key;
    
    if (free_value == NULL)
        hmap->free_value = FreeValueDefault;
    else 
        hmap->free_value = free_value;

    if (cmp == NULL)
        hmap->obj.compare_keys = CompareKeysDefault;
    else
        hmap->obj.compare_keys = cmp;

    if (print_pair == NULL)
        hmap->obj.print_pair = PrintPairDefault;
    else 
        hmap->obj.print_pair = print_pair;

    hmap->table = calloc(hmap->size, sizeof(DLList));
    for (int i = 0; i < hmap->size; i++)
        DLLIST_INIT(&(hmap->table[i]), DLLIST_INIT_SZ);

    hmap->obj.destroy = hmap_destroy;
    hmap->obj.change = hmap_change;
    hmap->obj.delete = hmap_delete;
    hmap->obj.get = hmap_get;
    hmap->obj.insert = hmap_insert;

    return (Map*)hmap;
}

void hmap_destroy(Map *obj) {
    if (obj == NULL)
        return;

    for (int i = 0; i < ((HashMap*)obj)->size; i++) {
        DLList* lst = &(((HashMap*)obj)->table[i]);

        for (int j = lst->head; j != 0; j = lst->next[j]) {
            ((HashMap*)obj)->free_key(lst->data[j].key);
            ((HashMap*)obj)->free_key(lst->data[j].value);
        }
        
        free(lst->data);

        free(lst->next);

        free(lst->prev);
    }

    free(((HashMap*)obj)->table);
    free((HashMap*)obj);

    printf("hmap freed \n");

    return;
}

int hmap_insert(Map* obj, void* key, void* value) {
    assert(obj);
    assert(key);
    assert(value);

    int hash = ((HashMap*)obj)->hash(key);
    DLList* lst = &(((HashMap*)obj)->table[hash]);
    Pair data = {key, value};

    for (int i = lst->head; i != 0; i = lst->next[i])
        if (obj->compare_keys(key, lst->data[i].key) == 0) {
                printf("[hmap_insert] trying to insert element with existing key. try hmap_change\n");
                return -1;
        } 

    DLListInsertR(lst, DLListGetTail(lst), data);

    return 0;
}

int hmap_delete(Map* obj, void* key) {
    assert(obj);
    assert(key);

    int hash = ((HashMap*)obj)->hash(key);
    DLList* lst = &(((HashMap*)obj)->table[hash]);
    
    for (int i = lst->head; i != 0; i = lst->next[i])
        if (obj->compare_keys(key, lst->data[i].key) == 0) {
            if (DLListDelete(lst, i) == -1)
                return -1;
            else 
                return 0;
        };

    printf("[hmap_delete] no element with such key!\n");

    return -1;
}

int hmap_change(Map* obj, void* key, void* newValue) {
    assert(obj);
    assert(key);
    assert(newValue);

    int hash = ((HashMap*)obj)->hash(key);
    DLList* lst = &(((HashMap*)obj)->table[hash]);
    
    for (int i = lst->head; i != 0; i = lst->next[i])
        if (obj->compare_keys(key, lst->data[i].key) == 0) {
            lst->data[i].value = newValue;
            return 0;
        }
    
    printf("[hmap_change] no element with such key!\n");

    return -1;
}

void* hmap_get(Map* obj, void* key) {
    assert(obj);
    assert(key);

    int hash = ((HashMap*)obj)->hash(key);
    DLList* lst = &(((HashMap*)obj)->table[hash]);
    
    for (int i = lst->head; i != 0; i = lst->next[i])
        if (obj->compare_keys(key, lst->data[i].key) == 0)
            return lst->data[i].value;

    printf("[hmap_get] no element with such key!\n");

    return NULL;
}

void Print(Map* obj) {
    assert(obj);

    for (int i = 0; i < ((HashMap*)obj)->size; i++) {
        DLList* lst = &(((HashMap*)obj)->table[i]);
        printf("lst #%d: (size: %d/%d)\n", i, lst->dataCur, lst->dataMax);
        for (int j = lst->head; j != 0; j = lst->next[j]) {
            printf("  [%d]: ", j);
            PrintPairDefault(lst->data[j].key, lst->data[j].value);
            printf("\n");
        }
    }

    printf("\n");

    return;
}
