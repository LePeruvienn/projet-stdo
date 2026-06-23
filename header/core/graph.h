#ifndef GRAPH_H
#define GRAPH_H

#include "core/edge.h"
#include "core/list.h"
#include <stddef.h>

typedef struct s_graph graph;

/**
 * \brief Creates a graph
 * \returns The newly created graph
 */
graph       *graph_new();

/**
 * \brief Frees a graph
 * \param The graph to be freed
 */
void        graph_free(graph *g);

/**
 * \brief Adds an edge between src and dest, with a specified distance
 * \param g The graph
 * \param src The source node
 * \param dest The destination node
 * \param distance The distance between the two nodes
 */
void        graph_add_edge(graph *g, int src, int dest, float distance);

/**
 * \brief Get all nodes from the graph
 * \param g The graph
 * \return List of nodes names
 */
int_list    *graph_get_all_nodes_names(graph *g);

/**
 * \brief Adds edges between src and a list of dest, with specified distances
 * \param g The graph
 * \param src The source node
 * \param dest The destination nodes
 * \param distance The distances between the nodes
 * \param n the number of nodes/distances
 * \attention dest and distance must be of size n
 */
void        graph_bulk_add_edge(graph *g, int src, int dest[], float distance[], size_t n);

/**
 * \brief Get the distance between two nodes
 * \param g The graph
 * \param src The source node
 * \param dest The destination node
 * \return The distance if there's an edge between the two nodes, and -1 if there's no edge.
 */
edge       *graph_get_distance(graph *g, int src, int dest);

#endif // GRAPH_H
