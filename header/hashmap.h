#include "node.h"

typedef struct s_hashmap hashmap;

/**
 * \brief Creates a new hashmap.
 * \attention The hashmap must be freed with hashmap_free()
 * \return New hashmap
 */
hashmap *hashmap_new     ();

/**
 * \brief Frees a hashmap.
 * \param hm The hashmap to be freed
 */
void    hashmap_free    (hashmap *hm);

/**
 * \brief Puts a value in the hashmap.
 * \attention If there's already a value with this key, the old value 
 *            will be freed and replaced with the one gave as an argument.
 * \param hm The hashmap
 * \param key The key used to identify the value
 * \param value The node to store
 */
void    hashmap_put     (hashmap *hm, int key, node *value);

/**
 * \brief Gets a value associated with the given key from the hashmap
 * \param hm The hashmap
 * \param key The key used to identify the value
 */
node    *hashmap_get     (hashmap *hm, int key);

/**
 * \brief Remove a value associated with the given key from the hashmap
 * \param hm The hashmap
 * \param key The key used to identify the value
 */
void    hashmap_remove  (hashmap *hm, int key);
