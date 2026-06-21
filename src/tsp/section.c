#include "tsp/section.h"
#include "tsp/section_datas.h"
#include "utils/logger.h"

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ELMENT_START_SIZE 32

#define TSP_SECTION_TYPE_NODE_COORD_SECTION_STR "NODE_COORD_SECTION"
#define TSP_SECTION_TYPE_DEPOT_SECTION_STR "DEPOT_SECTION"
#define TSP_SECTION_TYPE_DEMAND_SECTION_STR "DEMAND_SECTION"
#define TSP_SECTION_TYPE_EDGE_DATA_SECTION_STR "EDGE_DATA_SECTION"
#define TSP_SECTION_TYPE_FIXED_EDGES_SECTION_STR "FIXED_EDGES_SECTION"
#define TSP_SECTION_TYPE_DISPLAY_DATA_SECTION_STR "DISPLAY_DATA_SECTION"
#define TSP_SECTION_TYPE_TOUR_SECTION_STR "TOUR_SECTION"
#define TSP_SECTION_TYPE_EDGE_WEIGHT_SECTION_STR "EDGE_WEIGHT_SECTION"

struct TSP_Section
{
	TSP_Section_Type type;

	void* buffer;
	size_t size;
	size_t stride;

	size_t element_size;
	size_t element_amount;
};

static size_t get_stride(TSP_Section_Type type)
{
	switch(type)
	{
		case e_SECTION_TYPE_UNDEFINED:
			LOG_ERROR("Trying to get stride for a undefined section type, returning 0 instead.");
			return 0;

		case e_NODE_COORD_SECTION:
			return sizeof(struct TSP_Node_Coord);

		case e_DEPOT_SECTION:
			LOG_ERROR("Trying to get stride for a unsupported section type, returning 0 instead.");
			return 0;

		case e_DEMAND_SECTION:
			return sizeof(struct TSP_Demand);

		case e_EDGE_DATA_SECTION:
			return sizeof(struct TSP_Edge);

		case e_FIXED_EDGES_SECTION:
			return sizeof(struct TSP_Edge);

		case e_DISPLAY_DATA_SECTION:
			return sizeof(struct TSP_Display_Data);

		case e_TOUR_SECTION:
			return sizeof(struct TSP_Tour);

		case e_EDGE_WEIGHT_SECTION:
			return sizeof(struct TSP_Edge_Weight);
	}

	LOG_ERROR("Could not matche any TSP type, returned 0 instead.");

	return 0;
}


TSP_Section TSP_Section_create(TSP_Section_Type type)
{
	TSP_Section section = malloc(sizeof(struct TSP_Section));

	section->type = type;
	section->buffer = NULL;
	section->size = 0;
	section->stride = get_stride(type);
	section->element_size = 0;
	section->element_amount = 0;

	return section;
}

void TSP_Section_free(TSP_Section section)
{
	if (section->buffer != NULL)
	{
		free(section->buffer);
	}

	free(section);
}

static void TSP_Section_setup_for_next(TSP_Section section)
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

void* TSP_Section_get_next(TSP_Section section)
{
	if (section == NULL)
	{
		LOG_ERROR("Cannot get next of a NULL section, returned NULL.");
		return NULL;
	}

	TSP_Section_setup_for_next(section);

	return (unsigned char*) section->buffer + (section->element_amount++ * section->stride);
}

TSP_Node_Coord* TSP_Section_get_next_Node_Coord(TSP_Section section)
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

	TSP_Section_setup_for_next(section);

	TSP_Node_Coord* buffer = (TSP_Node_Coord*) section->buffer;

	return &buffer[section->element_amount++];
}

TSP_Section_Type parse_TSP_Section_Type(const char* field)
{
	if     (strcmp(field, TSP_SECTION_TYPE_NODE_COORD_SECTION_STR)   == 0) return e_NODE_COORD_SECTION;
	else if(strcmp(field, TSP_SECTION_TYPE_DEPOT_SECTION_STR)        == 0) return e_DEPOT_SECTION;
	else if(strcmp(field, TSP_SECTION_TYPE_DEMAND_SECTION_STR)       == 0) return e_DEMAND_SECTION;
	else if(strcmp(field, TSP_SECTION_TYPE_EDGE_DATA_SECTION_STR)    == 0) return e_EDGE_DATA_SECTION;
	else if(strcmp(field, TSP_SECTION_TYPE_FIXED_EDGES_SECTION_STR)  == 0) return e_FIXED_EDGES_SECTION;
	else if(strcmp(field, TSP_SECTION_TYPE_DISPLAY_DATA_SECTION_STR) == 0) return e_DISPLAY_DATA_SECTION;
	else if(strcmp(field, TSP_SECTION_TYPE_TOUR_SECTION_STR)         == 0) return e_TOUR_SECTION;
	else if(strcmp(field, TSP_SECTION_TYPE_EDGE_WEIGHT_SECTION_STR)  == 0) return e_EDGE_WEIGHT_SECTION;

	// TODO uncomment this
	// LOG_ERROR("Could not find .TSP Section type for field : %s", field);

	return TSP_SECTION_UNDEFINED;
}

const char* TSP_Section_Type_to_str(TSP_Section_Type type)
{
	switch (type)
	{
		case e_NODE_COORD_SECTION   : return TSP_SECTION_TYPE_NODE_COORD_SECTION_STR  ;
		case e_DEPOT_SECTION        : return TSP_SECTION_TYPE_DEPOT_SECTION_STR       ;
		case e_DEMAND_SECTION       : return TSP_SECTION_TYPE_DEMAND_SECTION_STR      ;
		case e_EDGE_DATA_SECTION    : return TSP_SECTION_TYPE_EDGE_DATA_SECTION_STR   ;
		case e_FIXED_EDGES_SECTION  : return TSP_SECTION_TYPE_FIXED_EDGES_SECTION_STR ;
		case e_DISPLAY_DATA_SECTION : return TSP_SECTION_TYPE_DISPLAY_DATA_SECTION_STR;
		case e_TOUR_SECTION         : return TSP_SECTION_TYPE_TOUR_SECTION_STR        ;
		case e_EDGE_WEIGHT_SECTION  : return TSP_SECTION_TYPE_EDGE_WEIGHT_SECTION_STR ;
		
		case e_SECTION_TYPE_UNDEFINED: return TSP_SECTION_UNDEFINED_STR;
	}

	LOG_ERROR("Could not find .TSP string for SECTION_TYPE enum : %d", type);
	return TSP_SECTION_UNDEFINED_STR;
}

void TSP_Section_print_Node_Coord(TSP_Section section)
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

	TSP_Node_Coord* buffer = (TSP_Node_Coord*) section->buffer;

	for (size_t i = 0; i < section->element_amount; ++i)
	{
		printf("%zu : %zu (x: %lf, y: %lf, z: %lf)\n",
				i, (size_t) buffer[i].node_number,
				buffer[i].px, buffer[i].py, buffer[i].pz);
	}
}
