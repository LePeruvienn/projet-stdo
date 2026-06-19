#include "core/node.h"

#include <stdlib.h>

struct s_node
{
	int foo;
};

node    *node_new()
{
	node* n = malloc(sizeof(struct s_node));
	return n;
}

void    node_free(node *n)
{
	free(n);
}
