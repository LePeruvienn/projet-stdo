#include "../header/hashmap.h"
#include "../header/node.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define A               0.5 * (sqrt(5) - 1)
#define PRIME_NUMBER    193	

/**
 * Hashmap entry, the smallest part of the Hashmap: stores the key (to differentiate
 * this entry from other entries that have the same hash), its value and the next node 
 * in case of collisions.
 */
typedef struct  s_hashmap_entry
{
    int                     key;
    node                    *value;
    struct s_hashmap_entry  *next;
} hm_entry;

/**
 * Hashmap struct made to represent non-oriented graphs, composed of PRIME_NUMBER items
 * of struct s_hashmap_store. 
 * Each PRIME_NUMBER item can store multiple values (to handle collisions).
 * See struct s__hashmap_store documentation for further details.
 * Keys are int-typed, and the value are node-typed to represent a graph.
 */
struct  s_hashmap 
{
    hm_entry                **keys;
};

/**
 * Hash formula for int indexed hashmaps
 */
int     __hash(int i)
{
    return i * (i + 3) % PRIME_NUMBER; 
}

hashmap*    hashmap_new()
{
    hashmap *hm = malloc(sizeof(struct s_hashmap));
    
    hm->keys = malloc(sizeof(struct s_hashmap_entry) * PRIME_NUMBER);
    for (int i = 0; i < PRIME_NUMBER; i++)
    {
        hm->keys[i] = NULL;
    }

    return hm;
}

hm_entry*    __hashmap_entry_new(int key, node *value)
{
    hm_entry *entry = malloc(sizeof(struct s_hashmap_entry));

    entry->key = key;
    entry->value = value;
    entry->next = NULL;

    return entry;
}

void        __hashmap_entry_free(hm_entry *entry)
{
    node_free(entry->value);
    free(entry);
}

void        hashmap_free    (hashmap *hm)
{
    for (int i = 0; i < PRIME_NUMBER; i++)
    {
        int hash = __hash(i);
        hm_entry *current_node = hm->keys[hash];
        while (current_node)
        {
            struct s_hashmap_entry *node_to_free = current_node;
            current_node = node_to_free->next;
            __hashmap_entry_free(node_to_free); 
        }
    }
    free(hm->keys);
}

hm_entry*   __hashmap_get_entry_last_node(hm_entry *entry)
{
    hm_entry *current = entry;
    while (current->next != NULL)
    {
        current = current->next;
    }
    return current;
}

hm_entry*   __hashmap_get_entry_if_exists(hm_entry *entries, int key)
{
    hm_entry *current_node = entries;
    while (current_node)
    {
        if (key == current_node->key)
        {
            return current_node;
        }
        current_node = current_node->next;
    }
    return NULL;
}

void        hasmap_put(hashmap *hm, int key, node *value)
{
    int hash        = __hash(key);
    hm_entry *entry = __hashmap_entry_new(key, value);

    if (hm->keys[hash] == NULL) 
    {
       hm->keys[hash] = entry;
    }
    else
    {
        hm_entry *correct_place = __hashmap_get_entry_if_exists(hm->keys[hash], key);

        if (correct_place == NULL) 
        {
            correct_place = __hashmap_get_entry_last_node(hm->keys[hash]);
            correct_place->next = entry;
        }
        else
        {   
            // we just replace the value if the key is already present
            node_free(correct_place->value);
            correct_place->value = value;
        }

    }
}

node*       hashmap_get(hashmap *hm, int key)
{
    int hash = __hash(key);
    hm_entry *entry = __hashmap_get_entry_if_exists(hm->keys[hash], key);

    return (entry) ? entry->value : NULL;
}

void        hashmap_remove  (hashmap *hm, int key)
{
    int hash = __hash(key);
    hm_entry *current = hm->keys[hash];

    while (current != NULL)
    {
        
        if (current->next != NULL && current->next->key == key)
        {
            hm_entry *to_remove = current->next;
            if (to_remove->next != NULL) 
            {
                current->next = to_remove->next;
                __hashmap_entry_free(to_remove);
            }
            else 
            {
                current->next = NULL;
                __hashmap_entry_free(to_remove);
            }
            break;
        }
        current = current->next;
    }
}
