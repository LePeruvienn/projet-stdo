#ifndef EDGE_H
#define EDGE_H

typedef struct s_edge edge;

/**
 * \brief Creates a new edge
 * \param node The destination node's name
 * \param distance The destination node's disance from source node
 * \return The newly created edge
 */
edge    *edge_new           (int node, float distance);

/**
 * \brief Frees an edge
 * \param e The edge to free
 */
void    edge_free           (void *e);

/**
 * \brief Gets the destination node
 * \param e The edge
 * \return The destination node's name
 */
int     edge_node           (edge *e);

void    edge_set_node       (edge *e, int node);

/**
 * \brief Gets the destination node's distance from the source node
 * \param e The edge
 * \return The destination node's distance from source node
 */
float   edge_distance       (edge *e);

void    edge_set_distance   (edge *e, float distance);

#endif //EDGE_H
