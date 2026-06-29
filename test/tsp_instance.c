#include "tsp/instance.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

static void create_instance(const char* filepath, float p)
{
	TSP_Instance instance = TSP_Instance_create(filepath, p);
	CU_ASSERT(instance != NULL);

	TSP_Instance_Nodes nodes = TSP_Instance_get_nodes(instance);
	CU_ASSERT(nodes.data != NULL);
	CU_ASSERT(nodes.size > 0);

	TSP_Instance_Edges edges = TSP_Instance_get_edges(instance);
	CU_ASSERT(edges.data != NULL);
	CU_ASSERT(edges.size > 0);

	TSP_Instance_free(instance);
}

void create_instance_a280(void)
{
	create_instance("TSPLIB/res/a280.tsp", 0.5f);
}

void create_instance_ali535(void)
{
	create_instance("TSPLIB/res/ali535.tsp", 0.5f);
}

int main(void)
{
	CU_initialize_registry();

	CU_pSuite suite = CU_add_suite("Création d'instance TSP", 0, 0);
	CU_add_test(suite, "a280",   create_instance_a280);
	CU_add_test(suite, "ali535", create_instance_ali535);

	CU_basic_run_tests();

	unsigned int ko_amount = CU_get_number_of_failures();
	CU_cleanup_registry();
	return (ko_amount > 0) ? ko_amount : 0;
}
