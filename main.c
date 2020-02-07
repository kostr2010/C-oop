// main file. here the methods will be tested

//====================
// INCLUDES

#include "tree.h"
#include "hmap.h"

//====================
// MAIN

int main()
{
    Map *c = hmap_create();
    Map *b = tree_create();

    c->destroy(c);
    b->destroy(b);
}