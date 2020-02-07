#include "tree.h"
#include "hmap.h"

int main()
{
    Box *c = hmap_create();
    Box *b = tree_create();

    c->destroy(c);
    b->destroy(b);
}