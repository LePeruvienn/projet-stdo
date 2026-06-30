#ifndef RENDERER_H
#define RENDERER_H

#include "visu/camera.h"
#include "visu/circle_renderer.h"
#include "visu/line_renderer.h"
#include "visu/grid_renderer.h"
#include "visu/text_renderer.h"

#include "tsp/instance.h"
#include "tsp/section_datas.h"

#include "utils/logger.h"

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>

#include "visu/camera.h"

// static TSP_Node_Coord* last_picked_node = NULL;

static camera main_camera = NULL;

static bool is_intialized = false;

static bool draw_help = true;

static void draw_UI(TSP_Instance instance)
{
	set_text_renderer_to_screen_space(true);

	text_begin_draw();

	if (draw_help)
	{
			draw_text("Controles :", 0.0f, 0.9f);
			draw_text("- [C/c] : Agrandir/retrecir les cercles", 0.0f, 0.8f);
			draw_text("- [L/l] : Agrandir/retrecir les lignes", 0.0f, 0.7f);
			draw_text("- [G/g] : Agrandir/retrecir la grille", 0.0f, 0.6f);
			draw_text("- [H/h] : Afficher/cacher ce message !", 0.0f, 0.5f);
	}

	bool have_shortest = TSP_Instance_have_shortest_path(instance);

	if (have_shortest)
	{
		TSP_Path shortest = TSP_Instance_get_shortest_path(instance);
		uint64_t compute_time = shortest.compute_time;

		size_t str_size = 128;
		char temp[str_size];

		snprintf(temp, str_size, "Compute time : %ld ms", compute_time);

		draw_text(temp, 0.0f, - 0.9f);
	}

	text_end_draw();

	set_text_renderer_to_screen_space(false);
}

static void draw_TSP_nodes(TSP_Instance instance)
{
	TSP_Instance_Nodes nodes = TSP_Instance_get_nodes(instance);

	TSP_Node_Number source_node = TSP_Instance_get_source(instance);
	TSP_Node_Number target_node = TSP_Instance_get_target(instance);

	bool is_source_set = false;
	bool is_target_set = false;

	TSP_Node_Coord source = { 0 };
	TSP_Node_Coord target = { 0 };

	set_circle_renderer_fill_color((color_rgba){0x78,  0xD9,  0x76, 0xFF});

	text_begin_draw();
	circle_begin_draw();
	for (size_t i = 0; i < nodes.size; ++i)
	{
		TSP_Node_Number node = nodes.data[i].node_number;

		if (node == source_node)
		{
			source = nodes.data[i];
			is_source_set = true;
			continue;
		}

		if (node == target_node)
		{
			target = nodes.data[i];
			is_target_set = true;
			continue;
		}

		float x = nodes.data[i].px;
		float y = nodes.data[i].py;

		circle_draw(x, y);
		
		char node_str[32];

		snprintf(node_str, sizeof(node_str), "%zu", (size_t) node);

		// LOG("[%zu] > %s || %zu", i, node_str, (size_t) node);

		draw_text(node_str, x, y);
	}
	circle_end_draw();
	text_end_draw();

	set_circle_renderer_fill_color((color_rgba){0xFF,  0x00,  0x00, 0xFF});

	circle_begin_draw();

	if(is_source_set)
		circle_draw(source.px, source.py);

	if(is_target_set)
		circle_draw(target.px, target.py);

	circle_end_draw();

	text_begin_draw();

	char node_str[32];

	if(is_source_set)
	{
		snprintf(node_str, sizeof(node_str), "%zu", (size_t) source.node_number);
		draw_text(node_str, source.px, source.py);
	}
	if(is_target_set)
	{
		snprintf(node_str, sizeof(node_str), "%zu", (size_t) target.node_number);
		draw_text(node_str, target.px, target.py);
	}

	text_end_draw();
}

static void draw_TSP_edges(TSP_Instance instance)
{
	TSP_Instance_Edges edges = TSP_Instance_get_edges(instance);

	set_line_renderer_color((color_rgba) { 0x4D, 0x33, 0xFF, 0xFF });

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

	// vvv DRAW SHORTEST PATH
	
	TSP_Path path = TSP_Instance_get_shortest_path(instance);

	set_line_renderer_color((color_rgba) { 0xFF, 0x00, 0x00, 0xFF });

	line_begin_draw();
	for (size_t i = 0; i < path.length; ++i)
	{
		TSP_Node_Coord* n1 = path.edges[i].from;
		TSP_Node_Coord* n2 = path.edges[i].to;

		float x1 = (float) n1->px;
		float x2 = (float) n2->px;

		float y1 = (float) n1->py;
		float y2 = (float) n2->py;

		line_draw(x1, y1, x2, y2);
	}
	line_end_draw();

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

	draw_TSP_edges(instance);
	draw_TSP_nodes(instance);
	draw_UI(instance);
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

TSP_Node_Coord* node_picking(TSP_Instance instance, float sx, float sy)
{
	if(is_intialized == false)
	{
		LOG_ERROR("Cannot do picking before initialization.");
		return NULL;
	}

	if (main_camera == NULL)
	{
		LOG_ERROR("Cannot pick with a NULL camera");
		return NULL;
	}

	float cam_px = get_camera_pos_x(main_camera);
	float cam_py = get_camera_pos_y(main_camera);

	float zoom   = get_camera_zoom(main_camera);
	float aspect = get_camera_aspect(main_camera);

	float undone_y = sy / aspect;

	float world_x = sx * zoom + cam_px;
	float world_y = undone_y * zoom + cam_py;

	float circle_scale = get_circle_renderer_scale();
	float radius2 = circle_scale * circle_scale;

	TSP_Instance_Nodes nodes = TSP_Instance_get_nodes(instance);

	for (size_t i = 0; i < nodes.size; ++i)
	{
		float dx = nodes.data[i].px - world_x;
		float dy = nodes.data[i].py - world_y;
		float dist2 = dx * dx + dy * dy;

		if (dist2 <= radius2)
		{
			return &nodes.data[i];
		}
	}

	return NULL;
}

void renderer_set_draw_help(bool value)
{
	draw_help = value;
}

#endif // RENDERER_H

