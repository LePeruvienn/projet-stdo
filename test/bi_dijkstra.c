#include "core/bi_dijkstra.h"
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

	int E = 0;
	int A = 1;
	int B = 2;
	int C = 3;
	int D = 4;
	int S = 5;

	graph_add_edge(g, E, A, 3.0);
	graph_add_edge(g, E, B, 1.0);
	graph_add_edge(g, A, C, 3.0);
	graph_add_edge(g, A, B, 1.0);
	graph_add_edge(g, B, C, 3.0);
	graph_add_edge(g, B, D, 5.0);
	graph_add_edge(g, C, S, 3.0);
	graph_add_edge(g, C, D, 1.0);
	graph_add_edge(g, D, S, 1.0);

	int visited_edges = 0;

	hashmap *h = bi_dijkstra(g, E, S, &visited_edges);

    float exp_distances[] = { 0.0, 2.0, 1.0, 4.0, 5.0, 6.0};
	int exp_through[]     = { E, B, E, B, C, D };

    edge *edge;
	for (int i = 0; i < 6; i++) 
	{
		edge = hashmap_get(h, i);
		LOG("Node: %c, Distance from %c: %f (through %c)", 
			names[i],
			names[E],
			edge_distance(edge),
			names[edge_node(edge)]
		);
	}

	CU_ASSERT(visited_edges == 9);
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

