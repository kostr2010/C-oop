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
    Map *c = hmap_create(NULL, NULL, NULL, NULL);
    //Map *b = tree_create();

    int val1 = 12;
    int val2 = 13;
    int val3 = 14;

    int key1 = 21;
    int key2 = 31;
    int key3 = 41;

    c->insert(c, &key1, &val1);
    c->insert(c, &key1, &val1);
    c->insert(c, &key1, &val1);
    c->insert(c, &key1, &val1);
    c->insert(c, &key1, &val1);
    c->insert(c, &key1, &val1);
    c->insert(c, &key1, &val1);

    Print(c);

    c->delete(c, &key1);

    Print(c);

    c->destroy(c);
    //b->destroy(b);

    
    /*
    DLList* lst = DLListAlloc();
    DLLIST_INIT(lst, 10);
    DLListInsertL(lst, DLListGetHead(lst), 20);
    DLListInsertR(lst, DLListGetTail(lst), 10);
    DLListInsertR(lst, DLListGetTail(lst), 13);
    DLListInsertR(lst, DLListGetTail(lst), 12);
    DLListInsertL(lst, DLListGetHead(lst), 11);
    DLListInsertL(lst, DLListGetHead(lst), 40);
 
    DLListDelete(lst, DLListGetHead(lst));
    DLListDelete(lst, DLListGetTail(lst));

    DLListSort(lst);

    DLListFree(lst);
    */
}