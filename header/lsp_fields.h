#ifndef LSP_FIELDS_H
#define LSP_FIELDS_H

#include "lsp_fields_enums.h"

/* 
 * FIELDS STRINGS MACROS
 */
#define LSP_NAME_STR "NAME"
#define LSP_TYPE_STR "TYPE"
#define LSP_COMMENT_STR "COMMENT"
#define LSP_DIMENSION_STR "DIMENSION"
#define LSP_CAPACITY_STR "CAPACITY"
#define LSP_EDGE_WEIGHT_TYPE_STR "EDGE_WEIGHT_TYPE"
#define LSP_EDGE_WEIGHT_FORMAT_STR "EDGE_WEIGHT_FORMAT"
#define LSP_EDGE_DATA_FORMAT_STR "EDGE_DATA_FORMAT"
#define LSP_NODE_COORD_TYPE_STR "NODE_COORD_TYPE"
#define LSP_DISPLAY_DATA_TYPE_STR "DISPLAY_DATA_TYPE"
#define LSP_EOF_STR "EOF"
#define LSP_NODE_COORD_SECTION_STR "NODE_COORD_SECTION"
#define LSP_DEPOT_SECTION_STR "DEPOT_SECTION"
#define LSP_DEMAND_SECTION_STR "DEMAND_SECTION"
#define LSP_EDGE_DATA_SECTION_STR "EDGE_DATA_SECTION"
#define LSP_FIXED_EDGES_SECTION_STR "FIXED_EDGES_SECTION"
#define LSP_DISPLAY_DATA_SECTION_STR "DISPLAY_DATA_SECTION"
#define LSP_TOUR_SECTION_STR "TOUR_SECTION"
#define LSP_EDGE_WEIGHT_SECTION "EDGE_WEIGHT_SECTION"

LSP_Type parse_LSP_Type(const char* field);
LSP_Edge_Weight_Type parse_LSP_Edge_Weight_Type(const char* field);
LSP_Edge_Weight_Format parse_LSP_Edge_Weight_Format(const char* field);
LSP_Edge_Data_Format parse_LSP_Edge_Data_Format(const char* field);
LSP_Node_Coord_Type parse_LSP_Node_Coord_Type(const char* field);
LSP_Display_Data_Type parse_LSP_Display_Data_Type(const char* field);

#endif // LSP_FIELDS_H
