#include "tsp/file.h"

#include "tsp/fields.h"
#include "tsp/fields_enums.h"
#include "tsp/section.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define END_STR '\0'

TSP_File TSP_File_create()
{
	TSP_File lsp_file = malloc(sizeof(struct TSP_File));

	// Header
	lsp_file->NAME[0] = END_STR;
	lsp_file->NAME[TSP_NAME_MAX_SIZE] = END_STR;

	lsp_file->TYPE = e_TYPE_UNDEFINED;

	lsp_file->COMMENT[0] = END_STR;
	lsp_file->COMMENT[TSP_COMMENT_MAX_SIZE] = END_STR;

	lsp_file->DIMENSION = 0;
	lsp_file->CAPACITY = 0;

	// File config
	lsp_file->EDGE_WEIGHT_TYPE = e_EDGE_WEIGHT_TYPE_UNDEFINED;
	lsp_file->EDGE_WEIGHT_FORMAT = e_EDGE_WEIGHT_FORMAT_UNDEFINED;
	lsp_file->EDGE_DATA_FORMAT = e_EDGE_DATA_FORMAT_UNDEFINED;
	lsp_file->NODE_COORD_TYPE = e_NODE_COORD_TYPE_UNDEFINED;
	lsp_file->DISPLAY_DATA_TYPE = e_DISPLAY_DATA_TYPE_UNDEFINED;

	// Sections
	lsp_file->NODE_COORD_SECTION = NULL;
	// lsp_file->DEPOT_SECTION = NULL; // UNSUPPORTED
	lsp_file->DEMAND_SECTION = NULL;
	lsp_file->EDGE_DATA_SECTION = NULL;
	lsp_file->FIXED_EDGES_SECTION = NULL;
	lsp_file->DISPLAY_DATA_SECTION = NULL;
	lsp_file->TOUR_SECTION = NULL;
	lsp_file->EDGE_WEIGHT_SECTION = NULL;

	return lsp_file;
}

void TSP_File_free(TSP_File lsp_file)
{
	if (lsp_file->NODE_COORD_SECTION   != NULL) TSP_Section_free(lsp_file->NODE_COORD_SECTION);
	if (lsp_file->DEMAND_SECTION       != NULL) TSP_Section_free(lsp_file->DEMAND_SECTION);
	if (lsp_file->EDGE_DATA_SECTION    != NULL) TSP_Section_free(lsp_file->EDGE_DATA_SECTION);
	if (lsp_file->FIXED_EDGES_SECTION  != NULL) TSP_Section_free(lsp_file->FIXED_EDGES_SECTION);
	if (lsp_file->DISPLAY_DATA_SECTION != NULL) TSP_Section_free(lsp_file->DISPLAY_DATA_SECTION);
	if (lsp_file->TOUR_SECTION         != NULL) TSP_Section_free(lsp_file->TOUR_SECTION);
	if (lsp_file->EDGE_WEIGHT_SECTION  != NULL) TSP_Section_free(lsp_file->EDGE_WEIGHT_SECTION);

	// if (lsp_file->DEPOT_SECTION == NULL) TSP_Section_free(lsp_file->DEPOT_SECTION); // UNSUPPORTED

	free(lsp_file);
}

void TSP_File_print(TSP_File lsp_file)
{
	// Header
	printf("----- TSP FILE -----\n");
	printf("Header\n");
	printf(" > NAME: %s\n", lsp_file->NAME[0] == '\0' ? "EMPTY" : lsp_file->NAME);
	printf(" > TYPE: %s\n", TSP_Type_to_str(lsp_file->TYPE));
	printf(" > COMMENT: %s\n", lsp_file->COMMENT[0] == '\0' ? "EMPTY" : lsp_file->COMMENT);
	printf(" > DIMENSION: %zu\n", lsp_file->DIMENSION);
	printf(" > CAPACITY: %zu\n", lsp_file->CAPACITY);

	// File config
	printf("Config\n");
	printf(" > EDGE_WEIGHT_TYPE: %s\n", TSP_Edge_Weight_Type_to_str(lsp_file->EDGE_WEIGHT_TYPE));
	printf(" > EDGE_WEIGHT_FORMAT: %s\n", TSP_Edge_Weight_Format_to_str(lsp_file->EDGE_WEIGHT_FORMAT));
	printf(" > EDGE_DATA_FORMAT: %s\n", TSP_Edge_Data_Format_to_str(lsp_file->EDGE_DATA_FORMAT));
	printf(" > NODE_COORD_TYPE: %s\n", TSP_Node_Coord_Type_to_str(lsp_file->NODE_COORD_TYPE));
	printf(" > DISPLAY_DATA_TYPE: %s\n", TSP_Display_Data_Type_to_str(lsp_file->DISPLAY_DATA_TYPE));

	// Sections
	printf("Sections\n");
	printf(" > NODE_COORD_SECTION: %s\n",
		lsp_file->NODE_COORD_SECTION == NULL ? "No" : "YES!");
	printf(" > DEMAND_SECTION: %s\n",
		lsp_file->DEMAND_SECTION == NULL ? "No" : "YES!");
	printf(" > EDGE_DATA_SECTION: %s\n",
		lsp_file->EDGE_DATA_SECTION == NULL ? "No" : "YES!");
	printf(" > FIXED_EDGES_SECTION: %s\n",
		lsp_file->FIXED_EDGES_SECTION == NULL ? "No" : "YES!");
	printf(" > DISPLAY_DATA_SECTION: %s\n",
		lsp_file->DISPLAY_DATA_SECTION == NULL ? "No" : "YES!");
	printf(" > TOUR_SECTION: %s\n",
		lsp_file->TOUR_SECTION == NULL ? "No" : "YES!");
	printf(" > EDGE_WEIGHT_SECTION: %s\n",
		lsp_file->EDGE_WEIGHT_SECTION == NULL ? "No" : "YES!");
	printf("--------------------\n");

	TSP_Section_print_Node_Coord(lsp_file->NODE_COORD_SECTION);
}

