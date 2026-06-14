#ifndef LSP_SECTION_DATAS_H
#define LSP_SECTION_DATAS_H

#include <stdint.h>
#include <stddef.h>

typedef uint64_t LSP_Node_Number;

typedef struct LSP_Node_Coord LSP_Node_Coord;
// typedef struct LSP_Depot_Section LSP_Depot_Section UNSUPPORTED
typedef struct LSP_Demand LSP_Demand;
typedef struct LSP_Edge LSP_Edge;
typedef struct LSP_Display_Data LSP_Display_Data;
typedef struct LSP_Tour LSP_Tour;
typedef struct LSP_Edge_Weight LSP_Edge_Weight;

struct LSP_Node_Coord
{
	LSP_Node_Number node_number;
	double px, py, pz;
};

// UNSUPPORTED
// struct LSP_Depot_Section

struct LSP_Demand
{
	LSP_Node_Number node_number;
	uint32_t demand;
};

struct LSP_Edge
{
	LSP_Node_Number nx, ny;
};

struct LSP_Display_Data
{
	LSP_Node_Number node_number;
	double px, py, pz;
};

struct LSP_Tour
{
	LSP_Node_Number* nodes;
	size_t tour_size;
};

struct LSP_Edge_Weight
{
	LSP_Edge edge;
	double weight;
};

#endif // LSP_SECTION_DATAS_H

