#include "core/astar.h"
#include "core/edge.h"
#include "core/graph.h"
#include "core/hashmap.h"
#include "core/heap.h"
#include "utils/logger.h"
#include <limits.h>



hashmap     *astar(graph *g, int src, int p, graph *h, int *visited_edge_number)
{
    int_list    *nodes      = graph_get_all_nodes_names(g);
    int         n           = nodes->size;
    hashmap     *results    = hashmap_new(edge_free);
    hashmap *nodes_visited  = hashmap_new(free);
    bool        src_exists  = false;
    heap        *f          = heap_new(n);
    
    for (int i = 0; i < n; i++)
    {
        if (nodes->inner[i] == src)
        {
            heap_insert(f, edge_new(src, 0.0));
            LOG("Inserted (n:%d) in f with distance (d:%f)", nodes->inner[i], 0.0);
            hashmap_put(results, src, edge_new(src, 0.0));
            LOG("Inserted (n:%d) in results with distance (d:%f)", nodes->inner[i], 0.0);
            src_exists  = true;
        }
        else
        {
            heap_insert(f, 
                    edge_new(nodes->inner[i], 
                    INT_MAX)
            );
            LOG("Inserted (n:%d) in f with distance (d:%f)", nodes->inner[i], INT_MAX);
            hashmap_put(results, nodes->inner[i], edge_new(nodes->inner[i], INT_MAX));
            LOG("Inserted (n:%d) in results with distance (d:%f)", nodes->inner[i], (float)INT_MAX);
        }
    }

    if (!src_exists)
    {
        heap_free(f);
        hashmap_free(results);
        hashmap_free(nodes_visited);
        free(nodes->inner);
        free(nodes);
        LOG("Node %d doesn't exist in the graph.", src);
        return NULL;
    };

    edge *current = heap_pop(f);
    LOG("Starting with %d. %d", edge_node(current), p);
    while (edge_node(current) != p)
    {
        LOG("Starting %d turn...", edge_node(current));
        // the node associated with the edge
        node    *current_node       = graph_get_edges(g, edge_node(current));
        
        // number of edges from current
        int     successors_number   = node_edge_number(current_node);
        // list of edges from current
        edge    **edge_list         = node_edge_list(current_node);
    
        edge    *current_result     = hashmap_get(results, edge_node(current));

        hashmap_put(nodes_visited, edge_node(current), malloc(1));

        // iterate through all successors
        for (int i = 0; i < successors_number; i++)
        {
            if (hashmap_has(nodes_visited, edge_node(edge_list[i])))
            {
                LOG("  * Node (n:%d) already visited, skipping...", edge_node(edge_list[i]));
                continue;
            }

            (*visited_edge_number)++;

            // current successor
            edge *successor     = edge_list[i]; 
            // successor but in result map
            edge *result        = hashmap_get(results, edge_node(edge_list[i]));

            LOG("  * Successor (n:%d, d:%f, h(%d): %f):", edge_node(successor), edge_distance(successor), edge_node(successor),
                    edge_distance(graph_get_distance(h, p, edge_node(successor))));
            
            float cumulative_distance = edge_distance(current_result) + edge_distance(successor);

            LOG("  * (%d->%d), edge distance: %f (relative:%f) (current in results: %f)", edge_node(current), edge_node(successor), cumulative_distance, edge_distance(successor), edge_distance(result));

            if (cumulative_distance < edge_distance(result))
            {  
                LOG("  * It's the best path, registering (%d->%d: %f)", src, edge_node(successor), cumulative_distance);
                edge_set_node(result, edge_node(current));
                edge_set_distance(result, cumulative_distance);
            }
            
            heap_change_value(
                        f, 
                        edge_node(successor), 
                        cumulative_distance + edge_distance(graph_get_distance(h, p, edge_node(successor)))
            );
        }       

        // the edge containing the node with the smallest distance from src
        current            = heap_pop(f);
    }

    return results;
}
