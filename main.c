// main file. here the methods will be tested

//====================
// INCLUDES

#include "tree.h"
#include "hmap.h"

//====================
// MAIN

int main()
{
    Box *c = hmap_create();
    Box *b = tree_create();

    c->destroy(c);
    b->destroy(b);
}