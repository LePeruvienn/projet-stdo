#include "core/node.h"
#include <stdlib.h>

typedef	struct s_edge 
{
	int				dest;
	float			distance;
	struct s_edge	*next;
} nd_edge;

struct	s_node
{
	nd_edge			*first;		
};

node    *node_new()
{
	node* n = malloc(sizeof(struct s_node));
	n->first = NULL;
	return n;
}

float	node_get_edge(node *n, int dest)
{
	nd_edge *current = n->first;

	while (current != NULL)
	{
		if (current->dest == dest)
		{
			return current->distance;
		}
		else
		{
			current = current->next;
		}
	}

	return -1.f;
}

static nd_edge *__node_new_edge(int dest, float distance)
{
	nd_edge *edge = malloc(sizeof(nd_edge));

	edge->dest = dest;
	edge->distance = distance;
	edge->next = NULL;

	return edge;
}

void	node_add_edge(node *n, int dest, float distance)
{
	if (n->first == NULL)
	{
		n->first = __node_new_edge(dest, distance); 
	}
	else
	{
		nd_edge *current = n->first;
		while (current->next != NULL) {
			// if it already exists, we just replace the distance and return
			if (current->dest == dest) 
			{
				current->distance = distance;
				return;
			}
			current = current->next;

		}
		// we're at the last edge, so we're inserting the new edge
		current->next = __node_new_edge(dest, distance);
	}
}

void	node_free(node *n)
{
	nd_edge *current = n->first;
	
	while (current != NULL)
	{
		if (current->next != NULL)
		{
			nd_edge *to_remove = current;
			current = to_remove->next;
			free(to_remove);
		}
		else
		{
			free(current);
		}
	}

	free(n);
}
