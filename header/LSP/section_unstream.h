#ifndef LSP_SECTION_UNSTREAM_H
#define LSP_SECTION_UNSTREAM_H

#include "LSP/file.h"

#include <stdio.h>

void LSP_Node_Coord_Section_unstream(FILE* str, LSP_File lsp_file);

void LSP_Depot_Section_unstream(FILE* str, LSP_File lsp_file);

void LSP_Demand_Section_unstream(FILE* str, LSP_File lsp_file);

void LSP_Edge_Data_Section_unstream(FILE* str, LSP_File lsp_file);

void LSP_Fixed_Edges_Section_unstream(FILE* str, LSP_File lsp_file);

void LSP_Display_Data_Section_unstream(FILE* str, LSP_File lsp_file);

void LSP_Tour_Section_unstream(FILE* str, LSP_File lsp_file);

void LSP_Edge_Weight_Section_unstream(FILE* str, LSP_File lsp_file);

#endif // LSP_SECTION_UNSTREAM_H
