#ifndef LSP_H
#define LSP_H

#include "lsp_fields_enums.h"
#include "lsp_section.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#define LSP_NAME_MAX_SIZE 128
#define LSP_COMMENT_MAX_SIZE 256

typedef struct LSP_File* LSP_File;

struct LSP_File
{
	// Header
	char NAME[LSP_NAME_MAX_SIZE + 1];
	LSP_Type TYPE;
	char COMMENT[LSP_COMMENT_MAX_SIZE + 1];
	size_t DIMENSION;
	size_t CAPACITY;

	// File config
	LSP_Edge_Weight_Type EDGE_WEIGHT_TYPE;
	LSP_Edge_Weight_Format EDGE_WEIGHT_FORMAT;
	LSP_Edge_Data_Format EDGE_DATA_FORMAT;
	LSP_Node_Coord_Type NODE_COORD_TYPE;
	LSP_Display_Data_Type DISPLAY_DATA_TYPE;

	// Sections
	LSP_Section NODE_COORD_SECTION;
	// LSP_Section DEPOT_SECTION; UNSUPPORTED
	LSP_Section DEMAND_SECTION;
	LSP_Section EDGE_DATA_SECTION;
	LSP_Section FIXED_EDGES_SECTION;
	LSP_Section DISPLAY_DATA_SECTION;
	LSP_Section TOUR_SECTION;
	LSP_Section EDGE_WEIGHT_SECTION;
};


LSP_File LSP_File_create();

void LSP_File_free(LSP_File lsp_file);

void LSP_File_print(LSP_File lsp_file);

#endif // LSP_H
