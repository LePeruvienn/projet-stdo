#include "core/hashmap.h"
#include "CUnit/CUnit.h"
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include <stdlib.h>

void hashmap_base()
{
    hashmap *h = hashmap_new(free);

    int *i = malloc(sizeof(int));
	*i = 1;

    int *k = malloc(sizeof(int));
	*i = 2;

    int *j = malloc(sizeof(int));
	*i = 3;
	
	hashmap_put(h, 1, i);
	hashmap_put(h, 2, k);
	hashmap_put(h, 3, j);

	CU_ASSERT((int*)hashmap_get(h, 1) == i);
	CU_ASSERT((int*)hashmap_get(h, 2) == k);
	CU_ASSERT((int*)hashmap_get(h, 3) == j);
    
	hashmap_remove(h, 1);
	
	CU_ASSERT((int*)hashmap_get(h, 1) == NULL);
    
	hashmap_free(h);
}

int main()
{
	CU_initialize_registry();

	// Permet de créer des groupes de tests (on peut en faire plusieurs !)
	CU_pSuite suite = CU_add_suite("hashmap", 0, 0);

	CU_add_test(suite, "basic hashmap test", hashmap_base);

	// Lancer les tests
	CU_basic_run_tests();

	// récupère le nombre de tests échoué
	unsigned int ko_amount = CU_get_number_of_failures();

	// Free CUnit
	CU_cleanup_registry();

	// Retourne 1 si il y a eu des tests KO
	return (ko_amount  > 0) ? ko_amount  : 0;
}

