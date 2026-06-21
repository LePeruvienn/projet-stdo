#ifndef LIST_H
#define LIST_H

#include <stddef.h>

typedef struct s_int_list
{
    int *inner;
    size_t size;
} int_list;

#endif // LIST_H
