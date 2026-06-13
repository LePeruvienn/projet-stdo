#include "lsp_section.h"
#include "logger.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

struct LSP_Section
{
	LSP_Section_Type type;

	void* buffer;
	size_t size;
	size_t stride;
};

// TODO
static size_t get_stride(LSP_Section_Type type)
{
	switch(type)
	{

	}

	return 0;
}


LSP_Section create_section()
{
	LSP_Section section = malloc(sizeof(struct LSP_Section));

	section->type = e_SECTION_TYPE_UNDEFINED;
	section->buffer = NULL;
	section->size = 0;

	return section;
}

void LSP_Section_free(LSP_Section section)
{
	free(section);
}
