#include "core/hashmap.h"
#include "core/node.h"
#include "utils/logger.h"

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
    void                    *value;
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
    void                    (*free_value)(void *);
};

/**
 * Hash formula for int indexed hashmaps
 */
int         __hash(int i)
{
    return i * (i + 3) % PRIME_NUMBER; 
}

hashmap*    hashmap_new(void (*free_value_fn)(void *))
{
    hashmap *hm = malloc(sizeof(struct s_hashmap));
    
    hm->free_value = free_value_fn;
    hm->keys = malloc(sizeof(hm_entry*) * PRIME_NUMBER);
    for (int i = 0; i < PRIME_NUMBER; i++)
    {
        hm->keys[i] = NULL;
    }

    return hm;
}

static hm_entry*    __hashmap_entry_new(int key, void *value)
{
    hm_entry *entry = malloc(sizeof(hm_entry));

    entry->key = key;
    entry->value = value;
    entry->next = NULL;

    return entry;
}

static void        __hashmap_entry_free(hashmap *hm, hm_entry *entry)
{
    hm->free_value(entry->value);
    free(entry);
}

void        hashmap_free    (hashmap *hm)
{
    for (int i = 0; i < PRIME_NUMBER; i++)
    {
        hm_entry *current_node = hm->keys[i];
        while (current_node != NULL)
        {
            hm_entry *node_to_free = current_node;
            current_node = node_to_free->next;
            __hashmap_entry_free(hm, node_to_free); 
        }
    }
    free(hm->keys);
    free(hm);
}

static hm_entry*   __hashmap_get_entry_last_node(hm_entry *entry)
{
    hm_entry *current = entry;
    while (current->next != NULL)
    {
        current = current->next;
    }
    return current;
}

static hm_entry*   __hashmap_get_entry_if_exists(hm_entry *entries, int key)
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

bool        hashmap_has(hashmap *hm, int key)
{
    int hash = __hash(key);
    hm_entry *entry = __hashmap_get_entry_if_exists(hm->keys[hash], key);

    return (entry != NULL);
}

void        hashmap_put(hashmap *hm, int key, void *value)
{
    int hash        = __hash(key);
    hm_entry *entry = __hashmap_entry_new(key, value);
    LOG("Hashed entry %d (hash: %d)", key, hash);

    if (hm->keys[hash] == NULL) 
    {
        hm->keys[hash] = entry;
        LOG("Add entry to hashmap");
    }
    else
    {
        LOG("Collision detected");
        hm_entry *correct_place = __hashmap_get_entry_if_exists(hm->keys[hash], key);

        if (correct_place == NULL) 
        {
            correct_place = __hashmap_get_entry_last_node(hm->keys[hash]);
            correct_place->next = entry;
        }
        else
        {   
            // we just replace the value if the key is already present
            hm->free_value(correct_place->value);
            correct_place->value = value;
        }
    }
}

void*       hashmap_get (hashmap *hm, int key)
{
    int hash = __hash(key);
    hm_entry *entry = __hashmap_get_entry_if_exists(hm->keys[hash], key);

    return (entry != NULL) ? entry->value : NULL;
}

void        hashmap_remove  (hashmap *hm, int key)
{
    int hash = __hash(key);
    LOG("Hashed entry %d (hash: %d)", key, hash);

    hm_entry *current = hm->keys[hash];

    if (current->key == key)
    {
        hm->keys[hash] = current->next;
        __hashmap_entry_free(hm, current);
        return;
    }

    hm_entry *parent = current;
    current = parent->next;

    while (current != NULL)
    {
        if (current->key == key)
        {
            parent->next = current->next;
            __hashmap_entry_free(hm, current);
            break;
        }
        parent = current;
        current = parent->next;
    }
}
