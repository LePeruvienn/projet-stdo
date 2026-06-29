#ifndef TSP_INSTANCE_H
#define TSP_INSTANCE_H

#include "tsp/section_datas.h"

#include "core/hashmap.h"

#include <stddef.h>
#include <stdint.h>

typedef struct TSP_Instance* TSP_Instance;

typedef struct TSP_Instance_Edge TSP_Instance_Edge;
typedef struct TSP_Instance_Edges TSP_Instance_Edges;
typedef struct TSP_Instance_Nodes TSP_Instance_Nodes;

typedef struct TSP_Path TSP_Path;

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

struct TSP_Path
{
	TSP_Instance_Edge* edges;
	size_t length;
	float cost;
	uint64_t compute_time;
};

TSP_Instance TSP_Instance_create(const char* path, float p);

void TSP_Instance_free(TSP_Instance instance);

TSP_Instance_Nodes TSP_Instance_get_nodes(TSP_Instance instance);

TSP_Instance_Edges TSP_Instance_get_edges(TSP_Instance instance);

void TSP_Instance_set_source(TSP_Instance instance, TSP_Node_Number source);
void TSP_Instance_set_target(TSP_Instance instance, TSP_Node_Number target);
 
void TSP_Instance_compute_shortest_path(TSP_Instance instance);

TSP_Path TSP_Instance_get_shortest_path(TSP_Instance instance);

#endif // TSP_INSTANCE_H
