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
 
	char names[] = "EABCDS";

	graph_add_edge(g, 0, 1, 3.0);
	graph_add_edge(g, 0, 2, 1.0);
	graph_add_edge(g, 1, 3, 3.0);
	graph_add_edge(g, 1, 2, 1.0);
	graph_add_edge(g, 2, 3, 3.0);
	graph_add_edge(g, 2, 4, 5.0);
	graph_add_edge(g, 3, 5, 3.0);
	graph_add_edge(g, 3, 4, 1.0);
	graph_add_edge(g, 4, 5, 1.0);

	hashmap *h = dijkstra(g, 0);

    edge *edge;
	for (int i = 0; i < 6; i++) 
	{
		edge = hashmap_get(h, i);
		LOG("Node: %c, Distance from %c: %f (through %c)", 
			names[i],
			names[0],
			edge_distance(edge),
			names[edge_node(edge)]
		);
	}
 
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

