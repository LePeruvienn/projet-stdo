#include "core/heap.h"
#include "core/edge.h"
#include "utils/logger.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#define HEAP_SIZE_MIN 0
#define HEAP_SIZE_MAX SIZE_MAX

struct s_heap {
    edge    **data;
    size_t  used_size;
    size_t  alllocated_size;
};

static int  __get_nearest_up_2_pow_n_value(size_t initial_size)
{
    size_t upper_bound = 2;

    while (initial_size >= upper_bound + 1)
    {
        upper_bound *= 2;
    }

    return upper_bound;
}

heap        *heap_new       (size_t initial_size)
{
    if (initial_size < HEAP_SIZE_MIN || initial_size > HEAP_SIZE_MAX)
    {
        LOG_ERROR("Wrong size for heap, must be between %d and %d", HEAP_SIZE_MIN, HEAP_SIZE_MAX);
    }

    heap *h = malloc(sizeof(heap));
    // adding +1 because of the heap's root
    h->alllocated_size = __get_nearest_up_2_pow_n_value(initial_size) + 1;
    h->data = malloc(sizeof(edge*) * h->alllocated_size);
    h->used_size = 0;

    return h;
}

void        heap_free       (heap *h)
{
    free(h->data);
    free(h);
}

bool        heap_is_empty   (heap *h)
{
    return h->used_size == 0;
}

void        heap_insert     (heap *h, edge *value)
{
    int child   = h->used_size;
    int parent  = (child - 1) / 2;

    // if we don't have space left in the heap, increase it to the next 2 power n value
    if (h->used_size + 1 > h->alllocated_size)
    {
        h->data = realloc(h->data, sizeof(edge*) * 1 + (h->alllocated_size - 1) * 2 );
    }

    while (child > 0 && edge_distance(h->data[parent]) > edge_distance(value) )
    {
        h->data[child] = h->data[parent];
        child = parent;
        parent = (child - 1) / 2;
    }

    h->data[child] = value;
    h->alllocated_size++;
}

static int  __heap_find_edge(heap *h, int dest)
{
    edge *current = h->data[0];
    int current_index = 0;

    while (current_index < h->used_size)
    {
        if (edge_node(current) == dest)
        {
            return current_index;
        }
        else
        {
            current = h->data[++current_index];
        }
    }

    return -1;
}

static int  __heap_get_parent(int i)
{
    return (i % 2 == 0) ? (i - 2) / 2 : (i - 1) / 2;
}

static int  __heap_get_left_child(int i)
{
    return (2 * i) + 1;
}

static int  __heap_get_right_child(int i)
{
    return (2 * i) + 2;
}

void        heap_decrease_value(heap *h, int dest, float value)
{
    int selected_index = __heap_find_edge(h, dest);

    if (selected_index == -1)
    {
        LOG("Could not find edge with destination %d", dest);
        return;
    }

    edge *selected = h->data[selected_index];

    if (edge_distance(selected) < value)
    {
        int i = selected_index;
        while (i > 0 && h->data[__heap_get_parent(selected_index)] < h->data[i])
        {
            int parent = __heap_get_parent(selected_index);
            edge *temp = h->data[parent];
            h->data[parent] = h->data[i];
            i = parent;
        }
    }
}

edge        *heap_pop       (heap *h)
{
    h->used_size--;
    edge *popped_value = h->data[0];
    edge *x = h->data[h->used_size];
    int parent = 0;
    int child;

    while (1)
    {
        int left_child_index = 2*parent+1;
        int right_child_index = left_child_index+1;

        // does left_child exists?
        if ((left_child_index) < h->used_size) child = 2*parent+1;
        else break;

        // does right_child exists?
        if ((right_child_index) < h->used_size)
            if (edge_distance(h->data[right_child_index]) <= edge_distance(h->data[left_child_index]))
                child = 2 * parent + 2;

        if (edge_distance(x) <= edge_distance(h->data[child]))
            break;

        h->data[parent] = h->data[child];
        parent = child;
    }

    h->data[parent] = x;

    return popped_value; 
}
