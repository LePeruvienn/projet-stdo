#ifndef LSP_H
#define LSP_H

#include "lsp_fields.h"
#include "lsp_fields_enums.h"

#include <stdint.h>
#include <stddef.h>

typedef struct LSP_File LSP_File;

struct LSP_File
{
	// Header
	char* NAME;
	LSP_Type TYPE;
	char* COMMENT;
	uint8_t DIMENSION;
	size_t CAPACITY;

	// File config
	LSP_Edge_Weight_Type EDGE_WEIGHT_TYPE;
	LSP_Edge_Weight_Format EDGE_WEIGHT_FORMAT;
	LSP_Edge_Data_Format EDGE_DATA_FORMAT;
	LSP_Node_Coord_Type NODE_COORD_TYPE;
	LSP_Display_Data_Type DISPLAY_DATA_TYPE;

	// Sections
	DEPOT_SECTION
	DEMAND_SECTION
	EDGE_DATA_SECTION
	FIXED_EDGES_SECTION
	DISPLAY_DATA_SECTION
	TOUR_SECTION
	EDGE_WEIGHT_SECTION
};

#endif // LSP_H
