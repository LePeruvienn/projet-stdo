#include "tsp/parser.h"
#include "tsp/file.h"

#include "core/hashmap.h"
#include "core/node.h"

const char* filepath = "TSPLIB/res/a280.tsp";

int main(void)
{
	TSP_File lsp_file = TSP_parse_file(filepath);

	TSP_File_print(lsp_file);

	TSP_File_free(lsp_file);
}
