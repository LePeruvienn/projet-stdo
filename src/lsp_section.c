#include "lsp_section.h"
#include "lsp_section_datas.h"
#include "logger.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ELMENT_START_SIZE 32

#define LSP_SECTION_TYPE_NODE_COORD_SECTION_STR "NODE_COORD_SECTION"
#define LSP_SECTION_TYPE_DEPOT_SECTION_STR "DEPOT_SECTION"
#define LSP_SECTION_TYPE_DEMAND_SECTION_STR "DEMAND_SECTION"
#define LSP_SECTION_TYPE_EDGE_DATA_SECTION_STR "EDGE_DATA_SECTION"
#define LSP_SECTION_TYPE_FIXED_EDGES_SECTION_STR "FIXED_EDGES_SECTION"
#define LSP_SECTION_TYPE_DISPLAY_DATA_SECTION_STR "DISPLAY_DATA_SECTION"
#define LSP_SECTION_TYPE_TOUR_SECTION_STR "TOUR_SECTION"
#define LSP_SECTION_TYPE_EDGE_WEIGHT_SECTION_STR "EDGE_WEIGHT_SECTION"

struct LSP_Section
{
	LSP_Section_Type type;

	void* buffer;
	size_t size;
	size_t stride;

	size_t element_size;
	size_t element_amount;
};

static size_t get_stride(LSP_Section_Type type)
{
	switch(type)
	{
		case e_SECTION_TYPE_UNDEFINED:
			LOG_ERROR("Trying to get stride for a undefined section type, returning 0 instead.");
			return 0;

		case e_NODE_COORD_SECTION:
			return sizeof(struct LSP_Node_Coord);

		case e_DEPOT_SECTION:
			LOG_ERROR("Trying to get stride for a unsupported section type, returning 0 instead.");
			return 0;

		case e_DEMAND_SECTION:
			return sizeof(struct LSP_Demand);

		case e_EDGE_DATA_SECTION:
			return sizeof(struct LSP_Edge);

		case e_FIXED_EDGES_SECTION:
			return sizeof(struct LSP_Edge);

		case e_DISPLAY_DATA_SECTION:
			return sizeof(struct LSP_Display_Data);

		case e_TOUR_SECTION:
			return sizeof(struct LSP_Tour);

		case e_EDGE_WEIGHT_SECTION:
			return sizeof(struct LSP_Edge_Weight);
	}

	LOG_ERROR("Could not matche any LSP type, returned 0 instead.");

	return 0;
}


LSP_Section LSP_Section_create(LSP_Section_Type type)
{
	LSP_Section section = malloc(sizeof(struct LSP_Section));

	section->type = type;
	section->buffer = NULL;
	section->size = 0;
	section->stride = get_stride(type);
	section->element_size = 0;
	section->element_amount = 0;

	return section;
}

void LSP_Section_free(LSP_Section section)
{
	if (section->buffer != NULL)
	{
		free(section->buffer);
	}

	free(section);
}

static void LSP_Section_setup_for_next(LSP_Section section)
{
	if (section->buffer == NULL)
	{
		section->element_size = ELMENT_START_SIZE;
		section->size = section->stride * section->element_size;
		section->buffer = malloc(section->size);
	}

	if(section->element_amount == section->element_size)
	{
		section->element_size *= 2;
		section->size = section->stride * section->element_size;
		section->buffer = realloc(section->buffer, section->size);
	}

	if (section->buffer == NULL)
	{
		LOG_ERROR("malloc or realloc failed, returning NULL.");
	}
}

void* LSP_Section_get_next(LSP_Section section)
{
	if (section == NULL)
	{
		LOG_ERROR("Cannot get next of a NULL section, returned NULL.");
		return NULL;
	}

	LSP_Section_setup_for_next(section);

	return (unsigned char*) section->buffer + (section->element_amount++ * section->stride);
}

LSP_Node_Coord* LSP_Section_get_next_Node_Coord(LSP_Section section)
{
	if (section == NULL)
	{
		LOG_ERROR("Cannot get next of a NULL section, returned NULL.");
		return NULL;
	}

	if (section->type != e_NODE_COORD_SECTION)
	{
		LOG_ERROR("Section type does not matche. Returned NULL.");
		return NULL;
	}

	LSP_Section_setup_for_next(section);

	LSP_Node_Coord* buffer = (LSP_Node_Coord*) section->buffer;

	return &buffer[section->element_amount++];
}

LSP_Section_Type parse_LSP_Section_Type(const char* field)
{
	if     (strcmp(field, LSP_SECTION_TYPE_NODE_COORD_SECTION_STR)   == 0) return e_NODE_COORD_SECTION;
	else if(strcmp(field, LSP_SECTION_TYPE_DEPOT_SECTION_STR)        == 0) return e_DEPOT_SECTION;
	else if(strcmp(field, LSP_SECTION_TYPE_DEMAND_SECTION_STR)       == 0) return e_DEMAND_SECTION;
	else if(strcmp(field, LSP_SECTION_TYPE_EDGE_DATA_SECTION_STR)    == 0) return e_EDGE_DATA_SECTION;
	else if(strcmp(field, LSP_SECTION_TYPE_FIXED_EDGES_SECTION_STR)  == 0) return e_FIXED_EDGES_SECTION;
	else if(strcmp(field, LSP_SECTION_TYPE_DISPLAY_DATA_SECTION_STR) == 0) return e_DISPLAY_DATA_SECTION;
	else if(strcmp(field, LSP_SECTION_TYPE_TOUR_SECTION_STR)         == 0) return e_TOUR_SECTION;
	else if(strcmp(field, LSP_SECTION_TYPE_EDGE_WEIGHT_SECTION_STR)  == 0) return e_EDGE_WEIGHT_SECTION;

	// TODO uncomment this
	// LOG_ERROR("Could not find .LSP Section type for field : %s", field);

	return LSP_SECTION_UNDEFINED;
}

const char* LSP_Section_Type_to_str(LSP_Section_Type type)
{
	switch (type)
	{
		case e_NODE_COORD_SECTION   : return LSP_SECTION_TYPE_NODE_COORD_SECTION_STR  ;
		case e_DEPOT_SECTION        : return LSP_SECTION_TYPE_DEPOT_SECTION_STR       ;
		case e_DEMAND_SECTION       : return LSP_SECTION_TYPE_DEMAND_SECTION_STR      ;
		case e_EDGE_DATA_SECTION    : return LSP_SECTION_TYPE_EDGE_DATA_SECTION_STR   ;
		case e_FIXED_EDGES_SECTION  : return LSP_SECTION_TYPE_FIXED_EDGES_SECTION_STR ;
		case e_DISPLAY_DATA_SECTION : return LSP_SECTION_TYPE_DISPLAY_DATA_SECTION_STR;
		case e_TOUR_SECTION         : return LSP_SECTION_TYPE_TOUR_SECTION_STR        ;
		case e_EDGE_WEIGHT_SECTION  : return LSP_SECTION_TYPE_EDGE_WEIGHT_SECTION_STR ;
		
		case e_SECTION_TYPE_UNDEFINED: return LSP_SECTION_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .LSP string for SECTION_TYPE enum : %d", type);
	return LSP_SECTION_UNDEFINED_STR;
}

void LSP_Section_print_Node_Coord(LSP_Section section)
{
	if (section == NULL)
	{
		LOG_ERROR("Cannot print a NULL section.");
		return;
	}

	if(section->type != e_NODE_COORD_SECTION)
	{
		LOG_ERROR("Section type mismatch.");
	}

	LSP_Node_Coord* buffer = (LSP_Node_Coord*) section->buffer;

	for (size_t i = 0; i < section->element_amount; ++i)
	{
		printf("%zu : %zu (x: %lf, y: %lf, z: %lf)\n",
				i, (size_t) buffer[i].node_number,
				buffer[i].px, buffer[i].py, buffer[i].pz);
	}
}
