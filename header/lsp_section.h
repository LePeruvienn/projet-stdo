#ifndef LSP_SECTION_H
#define LSP_SECTION_H

#include "lsp_section_datas.h"

#include <stdint.h>
#include <stddef.h>

#define LSP_SECTION_UNDEFINED 0
#define LSP_SECTION_UNDEFINED_STR "UNDEFINED"

#define LSP_SECTION_TYPE_NODE_COORD_SECTION_STR   "NODE_COORD_SECTION"
#define LSP_SECTION_TYPE_DEPOT_SECTION_STR        "DEPOT_SECTION"
#define LSP_SECTION_TYPE_DEMAND_SECTION_STR       "DEMAND_SECTION"
#define LSP_SECTION_TYPE_EDGE_DATA_SECTION_STR    "EDGE_DATA_SECTION"
#define LSP_SECTION_TYPE_FIXED_EDGES_SECTION_STR  "FIXED_EDGES_SECTION"
#define LSP_SECTION_TYPE_DISPLAY_DATA_SECTION_STR "DISPLAY_DATA_SECTION"
#define LSP_SECTION_TYPE_TOUR_SECTION_STR         "TOUR_SECTION"
#define LSP_SECTION_TYPE_EDGE_WEIGHT_SECTION_STR  "EDGE_WEIGHT_SECTION"

typedef enum LSP_Section_Type LSP_Section_Type;
typedef struct LSP_Section* LSP_Section;

enum LSP_Section_Type
{
	e_SECTION_TYPE_UNDEFINED = LSP_SECTION_UNDEFINED,

	e_NODE_COORD_SECTION,
	e_DEPOT_SECTION,
	e_DEMAND_SECTION,
	e_EDGE_DATA_SECTION,
	e_FIXED_EDGES_SECTION,
	e_DISPLAY_DATA_SECTION,
	e_TOUR_SECTION,
	e_EDGE_WEIGHT_SECTION
};

LSP_Section LSP_Section_create(LSP_Section_Type type);

void LSP_Section_free(LSP_Section section);

void* LSP_Section_get_next(LSP_Section section);
LSP_Node_Coord* LSP_Section_get_next_Node_Coord(LSP_Section section);

LSP_Section_Type parse_LSP_Section_Type(const char* field);
const char* LSP_Section_Type_to_str(LSP_Section_Type type);

void LSP_Section_print_Node_Coord(LSP_Section section);

#endif // LSP_SECTION_H
