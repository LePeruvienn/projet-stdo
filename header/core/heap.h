#ifndef HEAP_H
#define HEAP_H

#include "core/edge.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct s_heap heap;

heap    *heap_new               (size_t initial_size);

void    heap_free               (heap *h);

bool    heap_is_empty           (heap *h);

void    heap_insert             (heap *h, edge *value);

void    heap_change_value       (heap *h, int dest, float value);

edge    *heap_pop               (heap *h);

#endif // HEAP_H
