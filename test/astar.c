#include "core/astar.h"
#include "core/dijkstra.h"
#include "core/edge.h"
#include "core/graph.h"
#include "core/hashmap.h"
#include "CUnit/CUnit.h"
#include "utils/logger.h"
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include <stdlib.h>

void astar_base()
{
	graph *g = graph_new();
 
	char names[] = "ABCDEFZ";

    int A = 0;
	int B = 1;
	int C = 2;
	int D = 3;
	int E = 4;
	int F = 5;
	int Z = 6;

	graph_add_edge(g, Z, F, 16.0);
	graph_add_edge(g, Z, E, 5.0);
	graph_add_edge(g, F, B, 5.0);
	graph_add_edge(g, E, C, 10.0);
	graph_add_edge(g, E, D, 2.0);
	graph_add_edge(g, E, B, 12.0);
	graph_add_edge(g, B, A, 4.0);
	graph_add_edge(g, A, C, 3.0);
	graph_add_edge(g, C, D, 7.0);


	graph *h = graph_new();

    int nodes[] = { F, E, B, C, D, A };
	float dist[] = { 11.0, 4.0, 12.0, 11.0, 6.0, 14.0 };

	graph_bulk_add_edge(h, Z, 
			nodes, 
			dist, 
			6);

	int visited_edge_number = 0;

	hashmap *r = astar(g, A, Z, h, &visited_edge_number);

    float exp_distances[] = { 0.0, 4.0, 3.0, 10.0, 12.0, 9.0, 17.0};
	int exp_through[]     = { A, A, A, C, D, B, E };

    edge *edge;
	for (int i = 0; i < 7; i++) 
	{
		edge = hashmap_get(r, i);
		LOG("Node: %c, Distance from %c: %f (through %c)", 
			names[i],
			names[A],
			edge_distance(edge),
			names[edge_node(edge)]
		);
		CU_ASSERT(edge_distance(edge) - exp_distances[i] < 0.01 && edge_distance(edge) - exp_distances[i] > -0.01);
		CU_ASSERT(edge_node(edge) == exp_through[i])
	}
 
}

int main()
{
	CU_initialize_registry();

	// Permet de créer des groupes de tests (on peut en faire plusieurs !)
	CU_pSuite suite = CU_add_suite("astar", 0, 0);

	CU_add_test(suite, "astar test", astar_base);

	// Lancer les tests
	CU_basic_run_tests();

	// récupère le nombre de tests échoué
	unsigned int ko_amount = CU_get_number_of_failures();

	// Free CUnit
	CU_cleanup_registry();

	// Retourne 1 si il y a eu des tests KO
	return (ko_amount  > 0) ? ko_amount  : 0;
}

