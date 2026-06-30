#ifndef TSP_INSTANCE_H
#define TSP_INSTANCE_H

#include "tsp/section_datas.h"

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum TSP_Algo TSP_Algo;

enum TSP_Algo
{
	e_TSP_DIJKSTRA = 0,
	e_TSP_A_STAR,

	e_TSP_ALGO_END
};

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
	bool is_unreachable;

	TSP_Instance_Edge* edges;
	size_t length;
	float cost;

	uint64_t compute_time;
	int edge_visited_amount;
};

TSP_Instance TSP_Instance_create(const char* path, float p);

void TSP_Instance_free(TSP_Instance instance);

TSP_Instance_Nodes TSP_Instance_get_nodes(TSP_Instance instance);

TSP_Instance_Edges TSP_Instance_get_edges(TSP_Instance instance);

void TSP_Instance_set_source(TSP_Instance instance, TSP_Node_Number source);
void TSP_Instance_set_target(TSP_Instance instance, TSP_Node_Number target);

void TSP_Instance_compute_shortest_path(TSP_Instance instance);

TSP_Path TSP_Instance_get_shortest_path(TSP_Instance instance);

bool TSP_Instance_have_shortest_path(TSP_Instance instance);

TSP_Node_Number TSP_Instance_get_source(TSP_Instance instance);
TSP_Node_Number TSP_Instance_get_target(TSP_Instance instance);

void TSP_Instance_set_random_source_target(TSP_Instance instance);

TSP_Algo TSP_Instance_get_algo(TSP_Instance instance);
const char* TSP_Instance_get_algo_name(TSP_Instance instance);

void TSP_Instance_set_algo(TSP_Instance instance, TSP_Algo algo);
void TSP_Instance_go_next_algo(TSP_Instance instance);

#endif // TSP_INSTANCE_H
