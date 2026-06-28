#include "core/dijkstra.h"
#include "core/edge.h"
#include "core/graph.h"
#include "core/hashmap.h"
#include "CUnit/CUnit.h"
#include "utils/logger.h"
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include <stdlib.h>

void dijkstra_base()
{
	graph *g = graph_new();

    graph_add_edge(g, 1, 2, 10.0);
    graph_add_edge(g, 1, 5, 5.0);
    graph_add_edge(g, 2, 3, 1.0);
    graph_add_edge(g, 2, 5, 2.0);
    graph_add_edge(g, 3, 4, 4.0);
    graph_add_edge(g, 4, 3, 6.0);
    graph_add_edge(g, 4, 1, 7.0);
    graph_add_edge(g, 5, 2, 3.0);
    graph_add_edge(g, 5, 3, 9.0);
    graph_add_edge(g, 5, 4, 2.0);

    hashmap *h = dijkstra(g, 1);

    edge **edges = malloc(sizeof(edge*) * 5);

	for (int i = 0; i < 5; i++) 
	{
		edges[i] = hashmap_get(h, i + 1);
		LOG("Node: %d, Distance from 1: %f", 
			edge_node(edges[i]),
			edge_distance(edges[i])
		);
	}

	CU_ASSERT(edge_distance(edges[0]) - 0.0 < 0.01);
	CU_ASSERT(edge_node(edges[0]) == 1);
	CU_ASSERT(edge_distance(edges[1]) - 8.0 < 0.01);
	CU_ASSERT(edge_node(edges[1]) == 5);
	CU_ASSERT(edge_distance(edges[2]) - 9.0 < 0.01);
	CU_ASSERT(edge_node(edges[2]) == 2);
	CU_ASSERT(edge_distance(edges[3]) - 7.0 < 0.01);
	CU_ASSERT(edge_node(edges[3]) == 5);
	CU_ASSERT(edge_distance(edges[4]) - 5.0 < 0.01);
	CU_ASSERT(edge_node(edges[4]) == 1);
}

int main()
{
	CU_initialize_registry();

	// Permet de créer des groupes de tests (on peut en faire plusieurs !)
	CU_pSuite suite = CU_add_suite("dijkstra", 0, 0);

	CU_add_test(suite, "dijkstra test", dijkstra_base);

	// Lancer les tests
	CU_basic_run_tests();

	// récupère le nombre de tests échoué
	unsigned int ko_amount = CU_get_number_of_failures();

	// Free CUnit
	CU_cleanup_registry();

	// Retourne 1 si il y a eu des tests KO
	return (ko_amount  > 0) ? ko_amount  : 0;
}

