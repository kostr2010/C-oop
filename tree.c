// this file contains tree methods implementation

//====================
// INCLUDES

#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

//====================
// STRUCTURES

struct _Tree {
    struct _Box obj;

    char *name;
};
typedef struct _Tree Tree;

//====================
// METHODS IMPLEMENTATION

Box *tree_create() {
    Tree *tree = calloc(1, sizeof(Tree) + sizeof(Box));
    tree->obj.destroy = tree_destroy;

    return tree;
}

void *tree_destroy(Box *obj) {
    free((Tree *)(obj));

    printf("tree dead \n");
}