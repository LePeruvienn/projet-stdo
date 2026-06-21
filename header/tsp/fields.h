#ifndef TSP_FIELDS_H
#define TSP_FIELDS_H

#include "tsp/fields_enums.h"

#include <stddef.h>
#include <stdbool.h>

/* 
 * FIELDS STRINGS MACROS
 */
#define TSP_NAME_STR "NAME"
#define TSP_TYPE_STR "TYPE"
#define TSP_COMMENT_STR "COMMENT"
#define TSP_DIMENSION_STR "DIMENSION"
#define TSP_CAPACITY_STR "CAPACITY"

#define TSP_EDGE_WEIGHT_TYPE_STR "EDGE_WEIGHT_TYPE"
#define TSP_EDGE_WEIGHT_FORMAT_STR "EDGE_WEIGHT_FORMAT"
#define TSP_EDGE_DATA_FORMAT_STR "EDGE_DATA_FORMAT"
#define TSP_NODE_COORD_TYPE_STR "NODE_COORD_TYPE"
#define TSP_DISPLAY_DATA_TYPE_STR "DISPLAY_DATA_TYPE"
#define TSP_NODE_COORD_SECTION_STR "NODE_COORD_SECTION"
#define TSP_DEPOT_SECTION_STR "DEPOT_SECTION"
#define TSP_DEMAND_SECTION_STR "DEMAND_SECTION"
#define TSP_EDGE_DATA_SECTION_STR "EDGE_DATA_SECTION"
#define TSP_FIXED_EDGES_SECTION_STR "FIXED_EDGES_SECTION"
#define TSP_DISPLAY_DATA_SECTION_STR "DISPLAY_DATA_SECTION"
#define TSP_TOUR_SECTION_STR "TOUR_SECTION"
#define TSP_EDGE_WEIGHT_SECTION "EDGE_WEIGHT_SECTION"

#define TSP_EOF_STR "EOF"

TSP_Type parse_TSP_Type(const char* field);
TSP_Edge_Weight_Type parse_TSP_Edge_Weight_Type(const char* field);
TSP_Edge_Weight_Format parse_TSP_Edge_Weight_Format(const char* field);
TSP_Edge_Data_Format parse_TSP_Edge_Data_Format(const char* field);
TSP_Node_Coord_Type parse_TSP_Node_Coord_Type(const char* field);
TSP_Display_Data_Type parse_TSP_Display_Data_Type(const char* field);

const char* TSP_Type_to_str(TSP_Type type);
const char* TSP_Edge_Weight_Type_to_str(TSP_Edge_Weight_Type type);
const char* TSP_Edge_Weight_Format_to_str(TSP_Edge_Weight_Format format);
const char* TSP_Edge_Data_Format_to_str(TSP_Edge_Data_Format format);
const char* TSP_Node_Coord_Type_to_str(TSP_Node_Coord_Type type);
const char* TSP_Display_Data_Type_to_str(TSP_Display_Data_Type type);

#endif // TSP_FIELDS_H
