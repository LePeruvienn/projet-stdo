#include "core/node.h"
#include "CUnit/CUnit.h"
#include "core/edge.h"
#include <CUnit/Basic.h>

void node_test()
{
	node *n = node_new();
	CU_ASSERT(n != NULL);

	
	node_add_edge(n, 2, 2.0);
	node_add_edge(n, 3, 3.0);
	node_add_edge(n, 4, 4.0);
	node_add_edge(n, 5, 5.0);

    CU_ASSERT(node_get_edge(n, 2) - 2.0 < 0.01);
    CU_ASSERT(node_get_edge(n, 3) - 3.0 < 0.01);
    CU_ASSERT(node_get_edge(n, 4) - 4.0 < 0.01);
    CU_ASSERT(node_get_edge(n, 5) - 5.0 < 0.01);

	edge **e = node_edge_list(n);

	
    CU_ASSERT(edge_distance(e[0]) - 2.0 < 0.01);
    CU_ASSERT(edge_distance(e[1]) - 3.0 < 0.01);
    CU_ASSERT(edge_distance(e[2]) - 4.0 < 0.01);
    CU_ASSERT(edge_distance(e[3]) - 5.0 < 0.01);

	
    for (int i = 0; i < 4; i++)
		edge_free(e[i]);
	
	CU_ASSERT(node_edge_number(n) == 4);

	node_free(n);
}

int main()
{
	CU_initialize_registry();

	// Permet de créer des groupes de tests (on peut en faire plusieurs !)
	CU_pSuite suite = CU_add_suite("node", 0, 0);

	// ajoute des fonctions de test à un groupe
	CU_add_test(suite, "general test", node_test);

	// Lancer les tests
	CU_basic_run_tests();

	// récupère le nombre de tests échoué
	unsigned int ko_amount = CU_get_number_of_failures();

	// Free CUnit
	CU_cleanup_registry();

	// Retourne 1 si il y a eu des tests KO
	return (ko_amount  > 0) ? ko_amount  : 0;
}

