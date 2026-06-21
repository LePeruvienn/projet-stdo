#ifndef TSP_H
#define TSP_H

#include "tsp/fields_enums.h"
#include "tsp/section.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#define TSP_NAME_MAX_SIZE 128
#define TSP_COMMENT_MAX_SIZE 256

typedef struct TSP_File* TSP_File;

struct TSP_File
{
	// Header
	char NAME[TSP_NAME_MAX_SIZE + 1];
	TSP_Type TYPE;
	char COMMENT[TSP_COMMENT_MAX_SIZE + 1];
	size_t DIMENSION;
	size_t CAPACITY;

	// File config
	TSP_Edge_Weight_Type EDGE_WEIGHT_TYPE;
	TSP_Edge_Weight_Format EDGE_WEIGHT_FORMAT;
	TSP_Edge_Data_Format EDGE_DATA_FORMAT;
	TSP_Node_Coord_Type NODE_COORD_TYPE;
	TSP_Display_Data_Type DISPLAY_DATA_TYPE;

	// Sections
	TSP_Section NODE_COORD_SECTION;
	// TSP_Section DEPOT_SECTION; UNSUPPORTED
	TSP_Section DEMAND_SECTION;
	TSP_Section EDGE_DATA_SECTION;
	TSP_Section FIXED_EDGES_SECTION;
	TSP_Section DISPLAY_DATA_SECTION;
	TSP_Section TOUR_SECTION;
	TSP_Section EDGE_WEIGHT_SECTION;
};


TSP_File TSP_File_create();

void TSP_File_free(TSP_File lsp_file);

void TSP_File_print(TSP_File lsp_file);

#endif // TSP_H
