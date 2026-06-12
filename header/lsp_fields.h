#ifndef LSP_FIELDS_H
#define LSP_FIELDS_H

#include "lsp_fields_enums.h"

LSP_Type parse_LSP_Type(const char* field);
LSP_Edge_Weight_Type parse_LSP_Edge_Weight_Type(const char* field);
LSP_Edge_Weight_Format parse_LSP_Edge_Weight_Format(const char* field);
LSP_Edge_Data_Format parse_LSP_Edge_Data_Format(const char* field);
LSP_Node_Coord_Type parse_LSP_Node_Coord_Type(const char* field);
LSP_Display_Data_Type parse_LSP_Display_Data_Type(const char* field);

#endif // LSP_FIELDS_H
