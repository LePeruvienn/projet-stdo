#ifndef DJIKSTRA_H
#define DJIKSTRA_H

#include "core/graph.h"
#include "core/hashmap.h"

/**
 * \brief Apply Djikstra shortest path algorithm on graph g, from the src node.
 * \param g The graph
 * \param src The source node
 * \return Array of int
 */
hashmap     *dijkstra(graph *g, int src, int *edge_node_number);

#endif // DJIKSTRA_H
