#include "tsp/instance.h"
#include "tsp/parser.h"

#include "core/graph.h"
#include "core/hashmap.h"
#include "core/dijkstra.h"

#include "utils/logger.h"
#include "utils/ptr.h"
#include "utils/bench.h"

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

struct TSP_Instance
{
	const char* path;
	TSP_File file;

	TSP_Instance_Nodes nodes;
	TSP_Instance_Edges edges;

	float p;
	graph* g;

	bool have_shortest_path;

	TSP_Node_Number source_node;
	TSP_Node_Number target_node;

	TSP_Path shortest_path;
};

static TSP_Node_Coord* find_node_by_number(TSP_Instance instance, TSP_Node_Number node_number)
{
	CHECK_IS_NULL(instance, "Instance is NULL");

	for (size_t i = 0; i < instance->nodes.size; i++)
	{
		if (instance->nodes.data[i].node_number == node_number)
			return &instance->nodes.data[i];
	}

	return NULL;
}

static float node_dist(const TSP_Node_Coord* a, const TSP_Node_Coord* b)
{
	double dx = a->px - b->px;
	double dy = a->py - b->py;

	return sqrtf(dx * dx + dy * dy);
}

static void setup_nodes(TSP_Instance instance)
{
	CHECK_IS_NULL(instance, "Instance is NULL");
	CHECK_IS_NULL(instance->file, "Instance TSP file is NULL");

	TSP_Section_Data data = TSP_Section_get_data(instance->file->NODE_COORD_SECTION);

	if (data.size == 0 || data.coords == NULL)
	{
		LOG_ERROR("TSP File Node Coords data is Empty");
		return;
	}

	instance->nodes.size = data.size;
	instance->nodes.data = malloc(sizeof(TSP_Node_Coord) * instance->nodes.size);

	for (size_t i = 0; i < data.size; ++i)
	{
		instance->nodes.data[i] = data.coords[i];
	}

	instance->source_node = (int) instance->nodes.data[0].node_number;
}

static void setup_edges(TSP_Instance instance)
{
	CHECK_IS_NULL(instance, "Instance is NULL");
	CHECK_IS_NULL(instance->nodes.data, "Instance nodes data is NULL");

	size_t n = instance->nodes.size;
	size_t max_possible = n * (n - 1) / 2;

	// Alloue le max, on realloc à la fin
	instance->edges.data = malloc(sizeof(TSP_Instance_Edge) * max_possible);
	instance->edges.size = 0;

	// Une seule passe : max_dist ET edges en même temps
	float max_dist = 0.f;
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = i + 1; j < n; ++j)
		{
			if (i == j)
				continue;

			float dist = node_dist(&instance->nodes.data[i], &instance->nodes.data[j]);
			if (dist > max_dist)
				max_dist = dist;
		}
	}

	float threshold = instance->p * max_dist;

	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = i + 1; j < n; ++j)
		{
			if (i == j)
				continue;

			float dist = node_dist(&instance->nodes.data[i], &instance->nodes.data[j]);
			if (dist <= threshold)
			{
				TSP_Instance_Edge* e = &instance->edges.data[instance->edges.size++];
				e->from = &instance->nodes.data[i];
				e->to   = &instance->nodes.data[j];
				e->cost = dist;
			}
		}
	}

	// Redimensionne à la taille réelle
	instance->edges.data = realloc(instance->edges.data, sizeof(TSP_Instance_Edge) * instance->edges.size);
	LOG("Built %zu edges (threshold: %f)", instance->edges.size, threshold);
}

static void setup_graph(TSP_Instance instance)
{
	CHECK_IS_NULL(instance, "Instance is NULL");
	CHECK_IS_NULL(instance->edges.data, "Instance edges data is NULL");

	instance->g = graph_new();

	for (size_t i = 0; i < instance->edges.size; ++i)
	{
		TSP_Instance_Edge* e = &instance->edges.data[i];

		int src  = (int) e->from->node_number;
		int dest = (int) e->to->node_number;

		graph_add_edge(instance->g, src, dest, e->cost);
	}

	LOG("Graph built with %d nodes", graph_get_node_number(instance->g));
}

static void setup_instance(TSP_Instance instance)
{
	instance->file = TSP_parse_file(instance->path);

	if (instance->file == NULL)
	{
		LOG_ERROR("Failed to parse file!");
		return;
	}

	setup_nodes(instance);
	setup_edges(instance);
	setup_graph(instance);
}

TSP_Instance TSP_Instance_create(const char* path, float p)
{
	TSP_Instance instance = malloc(sizeof(struct TSP_Instance));

	instance->path = path;
	instance->p = p;

	instance->file = NULL;
	instance->nodes.data = NULL;
	instance->nodes.size = 0;
	instance->edges.data = NULL;
	instance->edges.size = 0;
	instance->g = NULL;

	instance->have_shortest_path = false;


	instance->source_node = 0;
	instance->target_node = 0;
	instance->shortest_path.edges = NULL;
	instance->shortest_path.length = 0;
	instance->shortest_path.compute_time = 0;
	instance->shortest_path.cost = 0.f;

	instance->shortest_path.is_unreachable = true;

	setup_instance(instance);

	return instance;
}

void TSP_Instance_free(TSP_Instance instance)
{
	if (instance == NULL)
	{
		LOG_ERROR("Tried to free a NULL instance");
		return;
	}

	FREE_PTR_NOT_NULL(instance->nodes.data, free);
	FREE_PTR_NOT_NULL(instance->edges.data, free);
	FREE_PTR_NOT_NULL(instance->g, graph_free);
	FREE_PTR_NOT_NULL(instance->shortest_path.edges, free);

	free(instance);
}


TSP_Instance_Nodes TSP_Instance_get_nodes(TSP_Instance instance)
{
	return instance->nodes;
}

TSP_Instance_Edges TSP_Instance_get_edges(TSP_Instance instance)
{
	return instance->edges;
}

void TSP_Instance_set_source(TSP_Instance instance, TSP_Node_Number source)
{
	CHECK_IS_NULL(instance, "Instance is NULL.");

	if (instance->have_shortest_path)
	{
		FREE_PTR_NOT_NULL(instance->shortest_path.edges, free);

		instance->shortest_path.edges = NULL;
		instance->shortest_path.length = 0;
		instance->shortest_path.cost = 0.f;
		instance->shortest_path.compute_time = 0.f;
		instance->have_shortest_path   = false;
		instance->shortest_path.is_unreachable = true;

	}

	instance->source_node = source;
}

void TSP_Instance_set_target(TSP_Instance instance, TSP_Node_Number target)
{
	CHECK_IS_NULL(instance, "Instance is NULL.");

	if (instance->have_shortest_path)
	{
		FREE_PTR_NOT_NULL(instance->shortest_path.edges, free);

		instance->shortest_path.edges = NULL;
		instance->shortest_path.length = 0;
		instance->shortest_path.cost = 0.f;
		instance->shortest_path.compute_time = 0.f;
		instance->have_shortest_path   = false;
		instance->shortest_path.is_unreachable = true;
	}

	instance->target_node = target;
}

void TSP_Instance_compute_shortest_path(TSP_Instance instance)
{
	CHECK_IS_NULL(instance, "Instance is NULL");
	CHECK_IS_NULL(instance->g, "Instance graph is NULL");

	if(instance->have_shortest_path == true)
	{
		LOG_WARNING("Already computed the shortest_path.");
		return;
	}

	uint64_t bench_start = bench_now_ms();

	hashmap* h = dijkstra(instance->g, instance->source_node);

	uint64_t bench_end = bench_now_ms();

	int tmp_size = 4096;

	int* tmp = malloc(sizeof(int) * tmp_size);
	int len = 0;

	int target  = (int) instance->target_node;
	int current = target;
	int source  = (int) instance->source_node;

	size_t max_iterations = (size_t) graph_get_node_number(instance->g);
	size_t iterations = 0;

	bool unreachable = false;
	bool cycle_detected = false;

	while (current != source)
	{
		if (iterations >= max_iterations)
		{
			LOG_WARNING("Nb iterations %zu : Cycle detected while getting path from %d to %d", iterations, target, source);
			cycle_detected = true;
			break;
		}

		++iterations;

		edge* e = hashmap_get(h, current);

		if (e == NULL)
		{
			LOG_WARNING("Node %d is unreachable from source %d", current, source);
			unreachable = true;
			break;
		}
		
		if (tmp_size == len)
		{
			tmp_size *= 2;
			tmp = realloc(tmp, sizeof(int) * tmp_size);
			CHECK_IS_NULL(tmp, "Failed to realloc tmp");
		}
		
		tmp[len++] = current;
		current    = edge_node(e);
	}

	if (unreachable || cycle_detected)
	{
		instance->shortest_path.is_unreachable = true;

		instance->shortest_path.edges = NULL;
		instance->shortest_path.length = 0;
		instance->shortest_path.cost = - 1.f;
		instance->shortest_path.compute_time = bench_end - bench_start;
		instance->have_shortest_path = true;

		hashmap_free(h);
		free(tmp);
		return;
	}

	tmp[len++] = instance->source_node;

	edge* e_target = hashmap_get(h, target);
	float total_cost = e_target ? edge_distance(e_target) : - 1.f;

	instance->shortest_path.length = (size_t)(len - 1);
	instance->shortest_path.cost = total_cost;
	instance->shortest_path.edges = malloc(sizeof(TSP_Instance_Edge) * instance->shortest_path.length);
	instance->shortest_path.compute_time = bench_end - bench_start;

	for (size_t i = 0; i < instance->shortest_path.length; i++)
	{
		int from_num = tmp[len - 1 - (int)i];
		int to_num   = tmp[len - 2 - (int)i];

		TSP_Node_Coord* from = find_node_by_number(instance, from_num);
		TSP_Node_Coord* to   = find_node_by_number(instance, to_num);

		instance->shortest_path.edges[i].from = from;
		instance->shortest_path.edges[i].to = to;
		instance->shortest_path.edges[i].cost = 0.f; // pas besoin pour le rendu
	}

	instance->have_shortest_path = true;
	instance->shortest_path.is_unreachable = false;

	hashmap_free(h);
	free(tmp);
}

TSP_Path TSP_Instance_get_shortest_path(TSP_Instance instance)
{
	CHECK_IS_NULL(instance, "Instance is NULL");

	if (instance->have_shortest_path == false)
	{
		LOG_ERROR("shortest_path has not been computed yet.");
	}

	return instance->shortest_path;
}

bool TSP_Instance_have_shortest_path(TSP_Instance instance)
{
	return instance->have_shortest_path;
}

TSP_Node_Number TSP_Instance_get_source(TSP_Instance instance)
{
	return instance->source_node;
}

TSP_Node_Number TSP_Instance_get_target(TSP_Instance instance)
{
	return instance->target_node;
}

void TSP_Instance_set_random_source_target(TSP_Instance instance)
{
	CHECK_IS_NULL(instance, "Instance is NULL.");
	CHECK_IS_NULL(instance->nodes.data, "Instance nodes are NULL");

	if (instance->nodes.size < 2)
	{
		LOG_ERROR("No enought nodes");
		return;
	}

	size_t source_idx = (size_t) rand() % instance->nodes.size;
	size_t target_idx = (size_t) rand() % instance->nodes.size;

	TSP_Node_Number source = instance->nodes.data[source_idx].node_number;
	TSP_Node_Number target = instance->nodes.data[target_idx].node_number;

	TSP_Instance_set_source(instance, source);
	TSP_Instance_set_target(instance, target);
}
