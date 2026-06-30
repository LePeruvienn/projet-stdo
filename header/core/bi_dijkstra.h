#ifndef BI_DIJKSTRA_H
#define BI_DIJKSTRA_H

#include "core/graph.h"
#include "core/hashmap.h"

/**
 * \brief Apply Djikstra shortest path algorithm on graph g, from the src node.
 * \param g The graph
 * \param src The source node
 * \return Array of int
 */
hashmap     *bi_dijkstra(graph *g, int src, int dest, int *visited_edge_number);

#endif // BI_DIJKSTRA_H
