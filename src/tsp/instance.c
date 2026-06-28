#include "tsp/instance.h"
#include "tsp/parser.h"

#include "core/graph.h"

#include "utils/logger.h"
#include "utils/ptr.h"

#include <math.h>
#include <stdlib.h>

struct TSP_Instance
{
	const char* path;
	TSP_File file;

	TSP_Instance_Nodes nodes;
	TSP_Instance_Edges edges;

	graph* g;
	float p;
};

static float node_dist(const TSP_Node_Coord* a, const TSP_Node_Coord* b)
{
	double dx = a->px - b->px;
	double dy = a->py - b->py;

	return (float) sqrt(dx * dx + dy * dy);
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

/*
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

		// Graphe non orienté donc les deux sens
		graph_add_edge(instance->g, src, dest, e->cost);
		graph_add_edge(instance->g, dest, src, e->cost);
	}

	LOG("Graph built with %d nodes", graph_get_node_number(instance->g));
}
*/

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
	// setup_graph(instance);
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
