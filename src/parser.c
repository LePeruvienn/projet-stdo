#include "parser.h"
#include "logger.h"

#include <stdio.h>
#include <stdlib.h>

void parse_lsp_file(const char* filepath)
{
	FILE* fd = fopen(filepath, "r");

	if (fd == NULL)
	{
		LOG_ERROR("Failed to open .lsp file");
		return;
	}
}
