#ifndef TSP_SECTION_UNSTREAM_H
#define TSP_SECTION_UNSTREAM_H

#include "tsp/file.h"

#include <stdio.h>

void TSP_Node_Coord_Section_unstream(FILE* str, TSP_File lsp_file);

void TSP_Depot_Section_unstream(FILE* str, TSP_File lsp_file);

void TSP_Demand_Section_unstream(FILE* str, TSP_File lsp_file);

void TSP_Edge_Data_Section_unstream(FILE* str, TSP_File lsp_file);

void TSP_Fixed_Edges_Section_unstream(FILE* str, TSP_File lsp_file);

void TSP_Display_Data_Section_unstream(FILE* str, TSP_File lsp_file);

void TSP_Tour_Section_unstream(FILE* str, TSP_File lsp_file);

void TSP_Edge_Weight_Section_unstream(FILE* str, TSP_File lsp_file);

#endif // TSP_SECTION_UNSTREAM_H
