#include "LSP/parser.h"
#include "LSP/file.h"

#include "core/hashmap.h"
#include "core/node.h"

const char* filepath = "TSPLIB/res/a280.tsp";

int main(void)
{
	LSP_File lsp_file = LSP_parse_file(filepath);

	LSP_File_print(lsp_file);

	LSP_File_free(lsp_file);
}
