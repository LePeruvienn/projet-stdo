#ifndef TSP_INSTANCE_H
#define TSP_INSTANCE_H

#include "tsp/section_datas.h"

#include <stddef.h>

typedef struct TSP_Instance* TSP_Instance;

typedef struct TSP_Instance_Edge TSP_Instance_Edge;
typedef struct TSP_Instance_Edges TSP_Instance_Edges;
typedef struct TSP_Instance_Nodes TSP_Instance_Nodes;

struct TSP_Instance_Edge
{
	TSP_Node_Coord* from;
	TSP_Node_Coord* to;
	float           cost;
};

struct TSP_Instance_Edges
{
	TSP_Instance_Edge* data;
	size_t size;
};

struct TSP_Instance_Nodes
{
	TSP_Node_Coord* data;
	size_t size;
};

TSP_Instance TSP_Instance_create(const char* path, float p);

void TSP_Instance_free(TSP_Instance instance);

TSP_Instance_Nodes TSP_Instance_get_nodes(TSP_Instance instance);

TSP_Instance_Edges TSP_Instance_get_edges(TSP_Instance instance);

#endif // TSP_INSTANCE_H
