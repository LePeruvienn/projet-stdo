#include "tsp/section_unstream.h"
#include "tsp/section_datas.h"
#include "tsp/section.h"
#include "tsp/file.h"
#include "utils/logger.h"

#include <stdio.h>
#include <string.h>

#define MAX_LINE_SIZE 256
#define EOF_STR "EOF"

void TSP_Node_Coord_Section_unstream(FILE* str, TSP_File lsp_file)
{
	lsp_file->NODE_COORD_SECTION = TSP_Section_create(e_NODE_COORD_SECTION);

	char line[MAX_LINE_SIZE];

	size_t node;
	double px, py, pz;

	while(fgets(line, sizeof(line), str) != NULL)
	{
		// replace first \r \n by \0 for cmp
		line[strcspn(line, "\r\n")] = '\0';

		if (strcmp(line, EOF_STR) == 0)
		{
			// LOG("EOF!!");
			break;
		}

		sscanf(line, "%zu %lf %lf %lf", &node, &px, &py, &pz);

		if(node == 0 && px == 0 && py == 0 && pz == 0)
		{
			LOG_WARNING("NODE_COORD_SECTION unstream ended prematurly");
			break;
		}
	
		TSP_Node_Coord* node_coord =
			TSP_Section_get_next_Node_Coord(lsp_file->NODE_COORD_SECTION);

		if (node_coord == NULL)
		{
			LOG_ERROR("Failed to get node coord struct.");
			return;
		}

		node_coord->node_number = node;
		node_coord->px = px;
		node_coord->py = py;
		node_coord->pz = pz;
	
		LOG("> Node Coord: %zu %lf %lf %lf",
			node_coord->node_number,
			node_coord->px, node_coord->py, node_coord->pz);
	}
}

/*
void TSP_Depot_Section_unstream(FILE* str, TSP_File lsp_file)
{

}

void TSP_Demand_Section_unstream(FILE* str, TSP_File lsp_file)
{

}

void TSP_Edge_Data_Section_unstream(FILE* str, TSP_File lsp_file)
{

}

void TSP_Fixed_Edges_Section_unstream(FILE* str, TSP_File lsp_file)
{

}

void TSP_Display_Data_Section_unstream(FILE* str, TSP_File lsp_file)
{

}

void TSP_Tour_Section_unstream(FILE* str, TSP_File lsp_file)
{

}

void TSP_Edge_Weight_Section_unstream(FILE* str, TSP_File lsp_file)
{

}
*/
