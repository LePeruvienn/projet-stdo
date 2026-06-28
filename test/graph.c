#include "core/graph.h"
#include "CUnit/CUnit.h"
#include "core/edge.h"
#include "core/node.h"
#include <CUnit/Basic.h>

void graph_test()
{
	graph *g = graph_new();

    graph_add_edge(g, 0, 1, 10.0);
    graph_add_edge(g, 0, 4, 5.0);
    graph_add_edge(g, 1, 2, 1.0);
    graph_add_edge(g, 1, 4, 2.0);
    graph_add_edge(g, 2, 3, 4.0);
    graph_add_edge(g, 3, 2, 6.0);
    graph_add_edge(g, 3, 0, 7.0);
    graph_add_edge(g, 4, 1, 3.0);
    graph_add_edge(g, 4, 2, 9.0);
    graph_add_edge(g, 4, 3, 2.0);

	int_list *il = graph_get_all_nodes_names(g);

	for (int i = 0; i < 5; i++)
	    CU_ASSERT(il->inner[i] == i);

    node *nd = graph_get_edges(g, 0);

	CU_ASSERT(node_edge_number(nd) == 2);
	
	edge **ed = node_edge_list(nd);

	CU_ASSERT(edge_distance(ed[0]) - 10.0 < 0.01);
	CU_ASSERT(edge_distance(ed[1]) - 5.0 < 0.01);
	CU_ASSERT(edge_node(ed[0]) == 1);
	CU_ASSERT(edge_node(ed[1]) == 4);
}

int main()
{
	CU_initialize_registry();

	// Permet de créer des groupes de tests (on peut en faire plusieurs !)
	CU_pSuite suite = CU_add_suite("graph tests", 0, 0);

	// ajoute des fonctions de test à un groupe
	CU_add_test(suite, "graph test", graph_test);

	// Lancer les tests
	CU_basic_run_tests();

	// récupère le nombre de tests échoué
	unsigned int ko_amount = CU_get_number_of_failures();

	// Free CUnit
	CU_cleanup_registry();

	// Retourne 1 si il y a eu des tests KO
	return (ko_amount  > 0) ? ko_amount  : 0;
}

