#include "core/heap.h"
#include "CUnit/CUnit.h"
#include "core/edge.h"
#include "utils/logger.h"
#include <CUnit/Basic.h>


void heap_test()
{
	heap *h = heap_new(8);

    edge *e = edge_new(1, 1.0);

	heap_insert(h, e);

	edge *initial = heap_pop(h);

	CU_ASSERT(edge_node(initial) == 1);
	CU_ASSERT(edge_distance(initial) - 1.0 < 0.01);

	heap_insert(h, edge_new(2, 10.0));
	heap_insert(h, edge_new(3, 20.0));

	heap_change_value(h, 3, 5.0);

    edge *decreased = heap_pop(h);
	
	LOG("(n: %d, d: %f)", edge_node(decreased), edge_distance(decreased));
	CU_ASSERT(edge_node(decreased) == 3);
	CU_ASSERT(edge_distance(decreased) - 5.0 < 0.01);

	heap_insert(h, e);
	heap_change_value(h, 1, 100.0);

    decreased = heap_pop(h);
	
	LOG("(n: %d, d: %f)", edge_node(decreased), edge_distance(decreased));
	CU_ASSERT(edge_node(decreased) == 2);
	CU_ASSERT(edge_distance(decreased) - 10.0 < 0.01);

    decreased = heap_pop(h);
	
	LOG("(n: %d, d: %f)", edge_node(decreased), edge_distance(decreased));
	CU_ASSERT(edge_node(decreased) == 1);
	CU_ASSERT(edge_distance(decreased) - 100.0 < 0.01);
}

int main()
{
	CU_initialize_registry();

	// Permet de créer des groupes de tests (on peut en faire plusieurs !)
	CU_pSuite suite = CU_add_suite("heap test", 0, 0);

	// ajoute des fonctions de test à un groupe
	CU_add_test(suite, "heap test", heap_test);

	// Lancer les tests
	CU_basic_run_tests();

	// récupère le nombre de tests échoué
	unsigned int ko_amount = CU_get_number_of_failures();

	// Free CUnit
	CU_cleanup_registry();

	// Retourne 1 si il y a eu des tests KO
	return (ko_amount  > 0) ? ko_amount  : 0;
}

