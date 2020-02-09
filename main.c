// main file. here the methods will be tested

//====================
// INCLUDES

#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
#include "hmap.h"
#include "list.h"

//====================
// MAIN

int main()
{
    //====================
    // HMAP TEST
    Map *c = hmap_create(NULL, NULL, NULL, NULL, NULL, NULL);

    int val1 = 1;
    int val2 = 2;
    int val3 = 3;

    int key1 = 11;
    int key2 = 21;
    int key3 = 31;

    c->insert(c, &key1, &val1);
    c->insert(c, &key2, &val2);
    c->insert(c, &key3, &val3);
    c->insert(c, &key1, &val1);
    c->insert(c, &key3, &val3);
    c->insert(c, &key2, &val2);
    c->insert(c, &key2, &val2);

    //Print(c);

    c->delete(c, &key3);
    c->change(c, &key2, &val3);

    Print(c);

    c->destroy(c);

    return 0;
}