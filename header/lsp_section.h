#ifndef LSP_SECTION_H
#define LSP_SECTION_H

#include <stdint.h>
#include <stddef.h>

#define LSP_SECTION_UNDEFINED 0

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

LSP_Section LSP_Section_create();

void LSP_Section_free(LSP_Section section);

#endif // LSP_SECTION_H
