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
    
    List* table;    
    int size;
    
    int  (*hash)(void* key);
    int  (*compare_keys)(void* key1, void* key2);
    int  (*compare_values)(void* value1, void* value2);
};
typedef struct _HashMap HashMap;

//====================
// METHODS IMPLEMENTATION

int GetHashDefault(void* key) {
    assert(key);

    return *(int*)key % 10;
}

int CompareDefault(void* arg1, void* arg2) {
    assert(arg1);
    assert(arg2);

    if (*(int*)arg1 == *(int*)arg2)
        return 0;
    else if (*(int*)arg1 < *(int*)arg2)
        return -1;
    else 
        return 1;
}

void PrintDefault(void* arg) {
    assert(arg);

    printf("\"%d\"", *(int*)arg);

    return;
}

Map *hmap_create(hash_func_t hash, cmp_keys_func_t cmp_keys, cmp_values_func_t cmp_values, int* size, print_key_func_t print_key, print_value_func_t print_value) {
    HashMap *hmap = calloc(1, sizeof(HashMap));

    if (hash == NULL) {
        hmap->hash = GetHashDefault;
        hmap->size = HMAP_SZ_DEFAULT;
    } else {
        hmap->hash = hash;
        hmap->size = *size;
    }

    if (cmp_keys == NULL)
        hmap->compare_keys = CompareDefault;
    else
        hmap->compare_keys = cmp_keys;

    if (cmp_values == NULL)
        hmap->compare_values = CompareDefault;
    else
        hmap->compare_values = cmp_values;

    hmap->table = calloc(hmap->size, sizeof(List));
    for (int i = 0; i < hmap->size; i++)
        ListInit(&(hmap->table[i]));

    hmap->obj.destroy = hmap_destroy;
    hmap->obj.change = hmap_change;
    hmap->obj.delete = hmap_delete;
    hmap->obj.get = hmap_get;
    hmap->obj.insert = hmap_insert;
    hmap->obj.count_value = hmap_count_value;

    return (Map*)hmap;
}

void hmap_destroy(Map *obj) {
    if (obj == NULL)
        return;

    for (int i = 0; i < ((HashMap*)obj)->size; i++) {
        List* lst = &(((HashMap*)obj)->table[i]);
        
        _ListFree(lst->first);
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
    List* lst = &(((HashMap*)obj)->table[hash]);
    Pair data = {key, value};

    for (Node* node = lst->first; node != NULL; node = node->next)
        if (((HashMap*)obj)->compare_keys(key, node->data.key) == 0) {
                printf("[hmap_insert] trying to insert element with existing key. try hmap_change\n");
                return -1;
        } 

    ListAppend(lst, data);

    return 0;
}

int hmap_delete(Map* obj, void* key) {
    assert(obj);
    assert(key);

    int hash = ((HashMap*)obj)->hash(key);
    List* lst = &(((HashMap*)obj)->table[hash]);
    
    Node* prev = NULL;
    for (Node* node = lst->first; node != NULL; node = node->next) {
        if (((HashMap*)obj)->compare_keys(key, node->data.key) == 0)
            return ListDelete(lst, prev, node);

        prev = node;
    }

    printf("[hmap_delete] no element with such key!\n");

    return -1;
}

int hmap_change(Map* obj, void* key, void* newValue) {
    assert(obj);
    assert(key);
    assert(newValue);

    int hash = ((HashMap*)obj)->hash(key);
    List* lst = &(((HashMap*)obj)->table[hash]);
    
    for (Node* node = lst->first; node != NULL; node = node->next) {
        if (((HashMap*)obj)->compare_keys(key, node->data.key) == 0) {
            node->data.value = newValue;

            return 0;
        }
    }
    
    printf("[hmap_change] no element with such key!\n");

    return -1;
}

void* hmap_get(Map* obj, void* key) {
    assert(obj);
    assert(key);

    int hash = ((HashMap*)obj)->hash(key);
    List* lst = &(((HashMap*)obj)->table[hash]);
    
    for (Node* node = lst->first; node != NULL; node = node->next)
        if (((HashMap*)obj)->compare_keys(key, node->data.key) == 0)
            return node->data.value;

    printf("[hmap_get] no element with such key!\n");

    return NULL;
}

int hmap_count_value(Map* obj, void* value) {
    int count = 0;

    for (int i = 0; i < ((HashMap*)obj)->size; i++) {
        List* lst = &(((HashMap*)obj)->table[i]);

        for (Node* node = lst->first; node != NULL; node = node->next)
            if (((HashMap*)obj)->compare_values(value, node->data.value) == 0)
                count++;
    }

    return count;
}

int hmap_size(Map* obj) {
    int count = 0;

    for (int i = 0; i < ((HashMap*)obj)->size; i++) {
        List* lst = &(((HashMap*)obj)->table[i]);

        for (Node* node = lst->first; node != NULL; node = node->next)
            count++;
    }

    return count;
}

void Print(Map* obj) {
    assert(obj);

    for (int i = 0; i < ((HashMap*)obj)->size; i++) {
        List* lst = &(((HashMap*)obj)->table[i]);
        printf("lst #%d: (size: %d)\n", i, lst->size);

        int iter = 0;
        for (Node* node = lst->first; node != NULL; node = node->next) {
            printf("  [%d]: ", iter);
            PrintDefault(node->data.key);
            printf(", ");
            PrintDefault(node->data.value);
            printf("\n");

            iter++;
        }
    }

    printf("\n");

    return;
}
