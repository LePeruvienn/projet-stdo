#include "LSP/parser.h"
#include "LSP/file.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

void open_tsp_file(const char* filepath)
{
	LSP_File lsp_file = LSP_parse_file(filepath);

	CU_ASSERT(lsp_file != NULL);

	LSP_File_free(lsp_file);
}

void open_a280()
{
	const char* filepath = "TSPLIB/res/a280.tsp";
	open_tsp_file(filepath);
}

void open_ali535()
{
	const char* filepath = "TSPLIB/res/ali535.tsp";
	open_tsp_file(filepath);
}

int main()
{
	CU_initialize_registry();

	// Permet de créer des groupes de tests (on peut en faire plusieurs !)
	CU_pSuite suite = CU_add_suite("Ouverture de fichier .tsp", 0, 0);

	CU_add_test(suite, "a280", open_a280);
	CU_add_test(suite, "ali535", open_ali535);

	// Lancer les tests
	CU_basic_run_tests();

	// récupère le nombre de tests échoué
	unsigned int ko_amount = CU_get_number_of_failures();

	// Free CUnit
	CU_cleanup_registry();

	// Retourne 1 si il y a eu des tests KO
	return (ko_amount  > 0) ? ko_amount  : 0;
}
