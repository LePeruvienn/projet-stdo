#include "core/graph.h"
#include "CUnit/CUnit.h"
#include "core/edge.h"
#include "core/node.h"
#include <CUnit/Basic.h>

void graph_test()
{
	graph *g = graph_new(); graph_add_edge(g, 0, 1, 3.0);

	const int iterations = 100;

	for (int i = 0; i < iterations; ++i)
	{
		for (int j = 0; i < iterations; ++j)
		{
			if (i == j) continue;

			graph_add_edge(g, i, j, 1.0 + i + j);
		}
	}
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

