#ifndef RENDERER_H
#define RENDERER_H

#include "visu/camera.h"
#include "visu/circle_renderer.h"
#include "visu/line_renderer.h"
#include "visu/grid_renderer.h"
#include "visu/text_renderer.h"

#include "tsp/file.h"
#include "tsp/section.h"

#include "utils/logger.h"

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "visu/camera.h"

static camera main_camera = NULL;

static void draw_TSP(TSP_File tsp_file)
{
	TSP_Section_Data data = TSP_Section_get_data(tsp_file->NODE_COORD_SECTION);
	TSP_Node_Coord* nodes_coords = data.coords;

	circle_begin_draw();

	for (size_t i = 0; i < data.size; ++i)
	{
		float x = nodes_coords[i].px;
		float y = nodes_coords[i].py;

		circle_draw(x, y);
	}

	circle_end_draw();
}

void init_renderer()
{
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
}

void set_renderer_camera(camera c)
{
	main_camera = c;

	set_circle_renderer_camera(c);
	set_grid_renderer_camera(c);
	set_line_renderer_camera(c);
	set_text_renderer_camera(c);
}

void render(TSP_File tsp_file)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	set_grid_renderer_grid_size(10.f);
	set_grid_renderer_bg_color((color_rgba) {0x0F, 0x0F, 0x0F, 0xFF});
	set_grid_renderer_line_color((color_rgba) {0x44, 0x44, 0x44, 0xFF});
	
	draw_grid();

	draw_TSP(tsp_file);
}

void free_renderer()
{
	free_circle_renderer();
	free_line_renderer();
	free_grid_renderer();
	free_text_renderer();
}

#endif // RENDERER_H

