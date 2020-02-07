#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED

struct _Box
{
    void *(*destroy)(struct _Box *obj);
};
typedef struct _Box Box;

#endif