#ifndef TSP_SECTION_DATAS_H
#define TSP_SECTION_DATAS_H

#include <stdint.h>
#include <stddef.h>

typedef size_t TSP_Node_Number;

typedef struct TSP_Node_Coord TSP_Node_Coord;
// typedef struct TSP_Depot_Section TSP_Depot_Section UNSUPPORTED
typedef struct TSP_Demand TSP_Demand;
typedef struct TSP_Edge TSP_Edge;
typedef struct TSP_Display_Data TSP_Display_Data;
typedef struct TSP_Tour TSP_Tour;
typedef struct TSP_Edge_Weight TSP_Edge_Weight;

struct TSP_Node_Coord
{
	TSP_Node_Number node_number;
	double px, py, pz;
};

// UNSUPPORTED
// struct TSP_Depot_Section

struct TSP_Demand
{
	TSP_Node_Number node_number;
	uint32_t demand;
};

struct TSP_Edge
{
	TSP_Node_Number nx, ny;
};

struct TSP_Display_Data
{
	TSP_Node_Number node_number;
	double px, py, pz;
};

struct TSP_Tour
{
	TSP_Node_Number* nodes;
	size_t tour_size;
};

struct TSP_Edge_Weight
{
	TSP_Edge edge;
	double weight;
};

#endif // TSP_SECTION_DATAS_H

