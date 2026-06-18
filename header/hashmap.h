#include "node.h"

typedef struct s_hashmap hashmap;

hashmap *hashmap_new     ();

void    hashmap_free    (hashmap *hm);

void    hashmap_put     (hashmap *hm, int key, node *value);

node    *hashmap_get     (hashmap *hm, int key);

void    hashmap_remove  (hashmap *hm, int key);
