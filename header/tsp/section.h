#ifndef TSP_SECTION_H
#define TSP_SECTION_H

#include "tsp/section_datas.h"

#include <stdint.h>
#include <stddef.h>

#define TSP_SECTION_UNDEFINED 0
#define TSP_SECTION_UNDEFINED_STR "UNDEFINED"

#define TSP_SECTION_TYPE_NODE_COORD_SECTION_STR   "NODE_COORD_SECTION"
#define TSP_SECTION_TYPE_DEPOT_SECTION_STR        "DEPOT_SECTION"
#define TSP_SECTION_TYPE_DEMAND_SECTION_STR       "DEMAND_SECTION"
#define TSP_SECTION_TYPE_EDGE_DATA_SECTION_STR    "EDGE_DATA_SECTION"
#define TSP_SECTION_TYPE_FIXED_EDGES_SECTION_STR  "FIXED_EDGES_SECTION"
#define TSP_SECTION_TYPE_DISPLAY_DATA_SECTION_STR "DISPLAY_DATA_SECTION"
#define TSP_SECTION_TYPE_TOUR_SECTION_STR         "TOUR_SECTION"
#define TSP_SECTION_TYPE_EDGE_WEIGHT_SECTION_STR  "EDGE_WEIGHT_SECTION"

typedef enum TSP_Section_Type TSP_Section_Type;
typedef struct TSP_Section* TSP_Section;
typedef struct TSP_Section_Data TSP_Section_Data;

enum TSP_Section_Type
{
	e_SECTION_TYPE_UNDEFINED = TSP_SECTION_UNDEFINED,

	e_NODE_COORD_SECTION,
	e_DEPOT_SECTION,
	e_DEMAND_SECTION,
	e_EDGE_DATA_SECTION,
	e_FIXED_EDGES_SECTION,
	e_DISPLAY_DATA_SECTION,
	e_TOUR_SECTION,
	e_EDGE_WEIGHT_SECTION,
	e_SECTION_EOF
};

struct TSP_Section_Data
{
	union
	{
		void* buffer;
		TSP_Node_Coord* coords;
		TSP_Demand* demands;
		TSP_Edge* edges;
		TSP_Display_Data* display_datas;
		TSP_Tour* tours;
		TSP_Edge_Weight* edges_weight;
	};

	size_t size;
	TSP_Section_Type type;
};

TSP_Section TSP_Section_create(TSP_Section_Type type);

void TSP_Section_free(TSP_Section section);

TSP_Section_Data TSP_Section_get_data(TSP_Section section);

void* TSP_Section_get_next(TSP_Section section);
TSP_Node_Coord* TSP_Section_get_next_Node_Coord(TSP_Section section);

TSP_Section_Type parse_TSP_Section_Type(const char* field);
const char* TSP_Section_Type_to_str(TSP_Section_Type type);

void TSP_Section_print_Node_Coord(TSP_Section section);

#endif // TSP_SECTION_H
