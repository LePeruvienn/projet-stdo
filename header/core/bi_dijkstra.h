#ifndef BI_DJIKSTRA_H
#define BI_DJIKSTRA_H

#include "core/graph.h"
#include "core/hashmap.h"

/**
 * \brief Apply Djikstra shortest path algorithm on graph g, from the src node.
 * \param g The graph
 * \param src The source node
 * \return Array of int
 */
hashmap     *bi_dijkstra(graph *g, int src, int dest);

#endif // BI_DJIKSTRA_H
