// main file. here the methods will be tested

//====================
// INCLUDES

#include "tree.h"
#include "hmap.h"
#include "list.h"

//====================
// MAIN

int main()
{
    Map *c = hmap_create();
    Map *b = tree_create();

    c->destroy(c);
    b->destroy(b);

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
}