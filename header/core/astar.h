#ifndef ASTAR_H
#define ASTAR_H

#include "core/graph.h"
#include "core/hashmap.h"

/**
 * \brief Apply A* optimized Djikstra shortest path algorithm on graph g, from the src node.
 * \param g The graph
 * \param src The source node
 * \param h Graph representing the euclidian distance between each node
 * \return Array of int
 */
hashmap     *astar(graph *g, int src, int p, graph *h, int *visited_edge_number);

#endif // ASTAR_H
