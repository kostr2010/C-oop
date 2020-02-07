#include <stdlib.h>
#include <stdio.h>

#include "hmap.h"

Box *hmap_create()
{
    Box *obj = calloc(1, sizeof(Box));
    obj->destroy = hmap_destroy;

    return obj;
}

void *hmap_destroy(Box *obj)
{
    free(obj);
    printf("hmap dead \n");
}