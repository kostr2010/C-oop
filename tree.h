#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#include "box.h"

// constants

Box *tree_create();
void *tree_destroy(Box *obj);
void *tree_print(Box *obj);
// ...

#endif