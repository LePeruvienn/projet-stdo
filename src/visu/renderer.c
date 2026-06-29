#ifndef RENDERER_H
#define RENDERER_H

#include "visu/camera.h"
#include "visu/circle_renderer.h"
#include "visu/line_renderer.h"
#include "visu/grid_renderer.h"
#include "visu/text_renderer.h"

#include "tsp/file.h"
#include "tsp/instance.h"
#include "tsp/section_datas.h"

#include "utils/logger.h"

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>

#include "visu/camera.h"

static camera main_camera = NULL;

static bool is_intialized = false;

static void draw_TSP(TSP_Instance instance)
{
	TSP_Instance_Nodes nodes = TSP_Instance_get_nodes(instance);
	TSP_Instance_Edges edges = TSP_Instance_get_edges(instance);

	line_begin_draw();
	for (size_t i = 0; i < edges.size; ++i)
	{
		TSP_Node_Coord* n1 = edges.data[i].from;
		TSP_Node_Coord* n2 = edges.data[i].to;

		float x1 = (float) n1->px;
		float x2 = (float) n2->px;

		float y1 = (float) n1->py;
		float y2 = (float) n2->py;

		line_draw(x1, y1, x2, y2);
	}
	line_end_draw();

	set_text_renderer_to_screen_space(false);

	text_begin_draw();
	circle_begin_draw();
	for (size_t i = 0; i < nodes.size; ++i)
	{
		TSP_Node_Number node = nodes.data[i].node_number;

		float x = nodes.data[i].px;
		float y = nodes.data[i].py;

		circle_draw(x, y);
		
		char node_str[32];

		snprintf(node_str, sizeof(node_str), "%zu", (size_t) node);

		LOG("[%zu] > %s || %zu", i, node_str, (size_t) node);

		draw_text(node_str, x, y);
	}
	circle_end_draw();
	text_end_draw();

	set_text_renderer_to_screen_space(true);

	text_begin_draw();
		draw_text("Salut le monde !", 0.f, 0.9f);
	text_end_draw();
}

void init_renderer()
{
	if (is_intialized)
	{
		LOG_ERROR("Renderer already initialized.");
		return;
	}

	if (!gladLoadGL())
	{
		LOG_ERROR("Failed to initialize glad.");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_MULTISAMPLE);
	glfwSwapInterval(1);

	init_circle_renderer();
	init_line_renderer();
	init_grid_renderer();
	init_text_renderer();

	is_intialized = true;
}

void set_renderer_camera(camera c)
{
	if (is_intialized == false)
	{
		LOG_ERROR("Renderer not initialized !");
		return;
	}

	main_camera = c;

	set_circle_renderer_camera(c);
	set_grid_renderer_camera(c);
	set_line_renderer_camera(c);
	set_text_renderer_camera(c);
}

void render(TSP_Instance instance)
{
	if (is_intialized == false)
	{
		LOG_ERROR("Renderer not initialized !");
		return;
	}

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	draw_grid();

	draw_TSP(instance);
}

void free_renderer()
{
	free_circle_renderer();
	free_line_renderer();
	free_grid_renderer();
	free_text_renderer();
}

bool renderer_get_is_intialized()
{
	return is_intialized;
}

#endif // RENDERER_H

