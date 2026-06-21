#ifndef NODE_H
#define NODE_H

/**
 * \brief Represents a list of edges originating from
 * the same node, with the destination and the distance from the node. 
 */
typedef struct s_node node;

/**
 * \brief Creates a new node.
 * \attention The node muist be freed with node_free()
 * \return New hashmap
 */
node    *node_new       ();

/**
 * \brief Add an edge (destination, distance) to the node
 * \param n Source node
 * \param dest Destination node
 * \param distance Distance from the node
 */
void    node_add_edge  (node *n, int dest, float distance);

/**
 * \brief Get the distance to an other node if there's an edge.
 * \param n The node (source)
 * \param dest The other node (destination)
 * \return The distance if there is an edge, and -1.0 if there's no edge
 *      between the two nodes.
 */
float   node_get_edge  (node *n, int dest);

/**
 * \brief Frees a node
 * \param n The node to be freed
 */
void    node_free       (node *n);

#endif // NODE_H


