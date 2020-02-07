// this file contains tree methods implementation

//====================
// INCLUDES

#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

//====================
// STRUCTURES

struct _Tree {
    struct _Map obj;

    char *name;
};
typedef struct _Tree Tree;

//====================
// METHODS IMPLEMENTATION

Map *tree_create() {
    Tree *tree = calloc(1, sizeof(Tree) + sizeof(Map));
    tree->obj.destroy = tree_destroy;

    return tree;
}

void *tree_destroy(Map *obj) {
    free((Tree *)(obj));

    printf("tree dead \n");
}