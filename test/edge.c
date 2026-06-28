#include "core/edge.h"
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include <CUnit/TestDB.h>
#include <stdio.h>

void edge_test()
{
    edge* e = edge_new(1, 1.0);

    CU_ASSERT(edge_node(e) == 1);
    CU_ASSERT(edge_distance(e) == 1.0);

    edge_set_node(e, 10);

    CU_ASSERT(edge_node(e) == 10);

    edge_set_distance(e, 5.256);

    CU_ASSERT(edge_distance(e) - 5.256 < 0.01);

    edge_free(e);

    CU_ASSERT(e == NULL);
}

int main()
{
    CU_initialize_registry();

    CU_pSuite suite = CU_add_suite("Edges", 0, 0);


    // Lancer les tests
	CU_basic_run_tests();

	// récupère le nombre de tests échoué
	unsigned int ko_amount = CU_get_number_of_failures();

	// Free CUnit
	CU_cleanup_registry();

	// Retourne 1 si il y a eu des tests KO
	return (ko_amount  > 0) ? ko_amount  : 0;
}
