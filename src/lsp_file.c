#include "lsp_file.h"

#include "lsp_fields.h"
#include "lsp_fields_enums.h"
#include "lsp_section.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define END_STR '\0'

LSP_File LSP_File_create()
{
	LSP_File lsp_file = malloc(sizeof(struct LSP_File));

	// Header
	lsp_file->NAME[0] = END_STR;
	lsp_file->NAME[LSP_NAME_MAX_SIZE] = END_STR;

	lsp_file->TYPE = e_TYPE_UNDEFINED;

	lsp_file->COMMENT[0] = END_STR;
	lsp_file->COMMENT[LSP_COMMENT_MAX_SIZE] = END_STR;

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

void LSP_File_free(LSP_File lsp_file)
{
	if (lsp_file->NODE_COORD_SECTION   != NULL) LSP_Section_free(lsp_file->NODE_COORD_SECTION);
	if (lsp_file->DEMAND_SECTION       != NULL) LSP_Section_free(lsp_file->DEMAND_SECTION);
	if (lsp_file->EDGE_DATA_SECTION    != NULL) LSP_Section_free(lsp_file->EDGE_DATA_SECTION);
	if (lsp_file->FIXED_EDGES_SECTION  != NULL) LSP_Section_free(lsp_file->FIXED_EDGES_SECTION);
	if (lsp_file->DISPLAY_DATA_SECTION != NULL) LSP_Section_free(lsp_file->DISPLAY_DATA_SECTION);
	if (lsp_file->TOUR_SECTION         != NULL) LSP_Section_free(lsp_file->TOUR_SECTION);
	if (lsp_file->EDGE_WEIGHT_SECTION  != NULL) LSP_Section_free(lsp_file->EDGE_WEIGHT_SECTION);

	// if (lsp_file->DEPOT_SECTION == NULL) LSP_Section_free(lsp_file->DEPOT_SECTION); // UNSUPPORTED

	free(lsp_file);
}

void LSP_File_print(LSP_File lsp_file)
{
	// Header
	printf("----- LSP FILE -----\n");
	printf("Header\n");
	printf(" > NAME: %s\n", lsp_file->NAME[0] == '\0' ? "EMPTY" : lsp_file->NAME);
	printf(" > TYPE: %s\n", LSP_Type_to_str(lsp_file->TYPE));
	printf(" > COMMENT: %s\n", lsp_file->COMMENT[0] == '\0' ? "EMPTY" : lsp_file->COMMENT);
	printf(" > DIMENSION: %zu\n", lsp_file->DIMENSION);
	printf(" > CAPACITY: %zu\n", lsp_file->CAPACITY);

	// File config
	printf("Config\n");
	printf(" > EDGE_WEIGHT_TYPE: %s\n", LSP_Edge_Weight_Type_to_str(lsp_file->EDGE_WEIGHT_TYPE));
	printf(" > EDGE_WEIGHT_FORMAT: %s\n", LSP_Edge_Weight_Format_to_str(lsp_file->EDGE_WEIGHT_FORMAT));
	printf(" > EDGE_DATA_FORMAT: %s\n", LSP_Edge_Data_Format_to_str(lsp_file->EDGE_DATA_FORMAT));
	printf(" > NODE_COORD_TYPE: %s\n", LSP_Node_Coord_Type_to_str(lsp_file->NODE_COORD_TYPE));
	printf(" > DISPLAY_DATA_TYPE: %s\n", LSP_Display_Data_Type_to_str(lsp_file->DISPLAY_DATA_TYPE));

	// Sections
	printf("Sections\n");
	printf(" > NODE_COORD_SECTION: %s\n",
		lsp_file->NODE_COORD_SECTION == NULL ? "NULL" : LSP_Section_Type_to_str(e_NODE_COORD_SECTION));
	printf(" > DEMAND_SECTION: %s\n",
		lsp_file->DEMAND_SECTION == NULL ? "NULL" : LSP_Section_Type_to_str(e_DEMAND_SECTION));
	printf(" > EDGE_DATA_SECTION: %s\n",
		lsp_file->EDGE_DATA_SECTION == NULL ? "NULL" : LSP_Section_Type_to_str(e_EDGE_DATA_SECTION));
	printf(" > FIXED_EDGES_SECTION: %s\n",
		lsp_file->FIXED_EDGES_SECTION == NULL ? "NULL" : LSP_Section_Type_to_str(e_FIXED_EDGES_SECTION));
	printf(" > DISPLAY_DATA_SECTION: %s\n",
		lsp_file->DISPLAY_DATA_SECTION == NULL ? "NULL" : LSP_Section_Type_to_str(e_DISPLAY_DATA_SECTION));
	printf(" > TOUR_SECTION: %s\n",
		lsp_file->TOUR_SECTION == NULL ? "NULL" : LSP_Section_Type_to_str(e_TOUR_SECTION));
	printf(" > EDGE_WEIGHT_SECTION: %s\n",
		lsp_file->EDGE_WEIGHT_SECTION == NULL ? "NULL" : LSP_Section_Type_to_str(e_EDGE_WEIGHT_SECTION));
	printf("--------------------\n");
}

