#include "core/dijkstra.h"
#include "core/edge.h"
#include "core/graph.h"
#include "core/hashmap.h"
#include "core/heap.h"
#include "core/list.h"
#include "core/node.h"
#include "utils/logger.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

hashmap *dijkstra(graph *g, int src, int *visited_node_number)
{
    int_list *nodes         = graph_get_all_nodes_names(g);
    int n                   = nodes->size;
    hashmap *results        = hashmap_new(edge_free);
    hashmap *nodes_visited  = hashmap_new(free);

    bool    src_exists      = false;
    heap    *remainingNodes = heap_new(n);

    for (int i = 0; i < n; i++)
    {
        if (nodes->inner[i] == src)
        {
            heap_insert(remainingNodes, edge_new(src, 0.0));
            hashmap_put(results, src, edge_new(src, 0.0));
            LOG("Inserted (n:%d) with distance (d:%f)", nodes->inner[i], 0.0);
            src_exists          = true;
        }
        else
        {
            heap_insert(remainingNodes, edge_new(nodes->inner[i], INT_MAX));
            hashmap_put(results, nodes->inner[i], edge_new(nodes->inner[i], INT_MAX));
            LOG("Inserted (n:%d) with distance (d:%f)", nodes->inner[i], (float)INT_MAX);
        }
    }

    if (!src_exists)
    {
        heap_free(remainingNodes);
        LOG("Node %d doesn't exist in the graph.", src);
        return NULL;
    }

    while (!heap_is_empty(remainingNodes))
    {   
        // the edge containing the node with the smallest cumulative distance from src
        edge    *current            = heap_pop(remainingNodes);
        LOG("Starting %d turn...", edge_node(current));
        // the node associated with the edge
        node    *current_node       = graph_get_edges(g, edge_node(current));
        
        // number of edges from current
        int     successors_number   = node_edge_number(current_node);
        // list of edges from current
        edge    **edge_list         = node_edge_list(current_node);
    
        hashmap_put(nodes_visited, edge_node(current), malloc(1));
        (*visited_node_number)++;
        
        // iterate through all successors
        for (int i = 0; i < successors_number; i++)
        {
            if (hashmap_has(nodes_visited, edge_node(edge_list[i])))
            {
                LOG("  * Node (n:%d) already visited, skipping...", edge_node(edge_list[i]));
                continue;
            }
           
            // current successor
            edge *successor     = edge_list[i]; 
            // successor but in result map
            edge *result        = hashmap_get(results, edge_node(edge_list[i]));



            float cumulative_distance = edge_distance(current) + edge_distance(successor);

            LOG("  * (%d->%d), edge distance: %f (relative:%f) (current in results: %f)", edge_node(current), edge_node(successor), cumulative_distance, edge_distance(successor), edge_distance(result));

            if (cumulative_distance < edge_distance(result))
            {  
                LOG("  * It's the best path, registering (%d->%d: %f)", src, edge_node(successor), cumulative_distance);
                heap_change_value(remainingNodes, edge_node(successor), cumulative_distance);
                edge_set_node(result, edge_node(current));
                edge_set_distance(result, cumulative_distance);
            }
        }
    }

    return results;
}

