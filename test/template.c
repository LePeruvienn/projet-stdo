#include "CUnit/CUnit.h"
#include <CUnit/Basic.h>

void test_1()
{
	CU_ASSERT(3 + 2 == 5);
}


void test_2()
{
	CU_ASSERT(2 + 3 == 5);
}

void test_3()
{
	CU_ASSERT(5 + 0 == 5);
}

int main()
{
	CU_initialize_registry();

	// Permet de créer des groupes de tests (on peut en faire plusieurs !)
	CU_pSuite suite = CU_add_suite("mylib_tests", 0, 0);

	// ajoute des fonctions de test à un groupe
	CU_add_test(suite, "test_1", test_1);
	CU_add_test(suite, "test_2", test_2);
	CU_add_test(suite, "test_3", test_3);

	// Lancer les tests
	CU_basic_run_tests();

	// récupère le nombre de tests échoué
	unsigned int ko_amount = CU_get_number_of_failures();

	// Free CUnit
	CU_cleanup_registry();

	// Retourne 1 si il y a eu des tests KO
	return (ko_amount  > 0) ? ko_amount  : 0;
}

