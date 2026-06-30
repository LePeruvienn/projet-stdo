#include "tsp/instance.h"
#include "tsp/section_datas.h"

#include "visu/window.h"
#include "visu/camera.h"
#include "visu/renderer.h"
#include "visu/circle_renderer.h"
#include "visu/text_renderer.h"
#include "visu/line_renderer.h"
#include "visu/grid_renderer.h"

#include "utils/logger.h"
#include "utils/ptr.h"

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stddef.h>
#include <math.h>

static unsigned int window_width = 1280;
static unsigned int window_height = 960;

static window w = NULL;
static camera c = NULL;

static TSP_Instance tsp_instance = NULL;

static void handle_algo_switch()
{
	CHECK_IS_NULL(tsp_instance, "TSP instance is NULL");
	CHECK_IS_NULL(w, "Window is NULL");

	static bool last_pressed = false;

	bool pressed = window_get_key_pressed(w, GLFW_KEY_Q); // A en  AZERTY

	if (pressed && !last_pressed)
	{
		TSP_Instance_go_next_algo(tsp_instance);
		// reclaculer pour le nouvelle algo
		TSP_Instance_compute_shortest_path(tsp_instance);
	}

	last_pressed = pressed;
}

static void handle_picking()
{
	CHECK_IS_NULL(w, "Cannot do picking with NULL window");
	CHECK_IS_NULL(tsp_instance, "Cannot do picking with NULL TSP instance");

	mouse_status mouse = window_get_mouse_status(w);

	if (mouse.left_click == 0 && mouse.right_click == 0)
		return;

	int fb_w, fb_h;
	window_get_framebuffer_size(w, &fb_w, &fb_h);

	float x = (mouse.x / (float) fb_w)  * 2.f - 1.f;
	float y = 1.f - (mouse.y / (float) fb_h) * 2.f;

	TSP_Node_Coord* node = node_picking(tsp_instance, x, y);

	if (node == NULL)
		return;

	LOG_INFO("Picked node : %zu", (size_t) node->node_number);

	if(mouse.left_click != 0)
	{
		TSP_Node_Number target_node = TSP_Instance_get_target(tsp_instance);

		if (node->node_number != target_node)
		{
			TSP_Instance_set_target(tsp_instance, node->node_number);
			TSP_Instance_compute_shortest_path(tsp_instance);
			return;
		}
	}

	if(mouse.right_click != 0)
	{
		TSP_Node_Number source_node = TSP_Instance_get_source(tsp_instance);

		if (node->node_number != source_node)
		{
			TSP_Instance_set_source(tsp_instance, node->node_number);
			TSP_Instance_compute_shortest_path(tsp_instance);
			return;
		}
	}
}

static void fit_camera()
{
	TSP_Instance_Nodes nodes = TSP_Instance_get_nodes(tsp_instance);

	size_t n = nodes.size;

	float min_x = (float) nodes.data[0].px;
	float max_x = (float) nodes.data[0].px;
	float min_y = (float) nodes.data[0].py;
	float max_y = (float) nodes.data[0].py;

	for (size_t i = 1; i < n; ++i)
	{
		float x = (float) nodes.data[i].px;
		float y = (float) nodes.data[i].py;

		if (x < min_x) min_x = x;
		if (x > max_x) max_x = x;
		if (y < min_y) min_y = y;
		if (y > max_y) max_y = y;
	}

	float center_x = (min_x + max_x) / 2.f;
	float center_y = (min_y + max_y) / 2.f;

	float span_x = max_x - min_x;
	float span_y = max_y - min_y;

	float aspect = (float) window_width / (float) window_height;

	float zoom_x = span_x / 2.f;
	float zoom_y = (span_y / 2.f) * aspect;

	float zoom = fmaxf(zoom_x, zoom_y);
	zoom *= 1.1f;  // marge pour ne pas coller les bords

	camera_move(c, center_x, center_y, zoom);

	// On adapte les paramêtre de rendu à la taille du problème
	set_circle_renderer_scale(zoom * 0.015f);
	set_text_renderer_text_size(zoom * 0.0075f);
	set_line_renderer_thickness(zoom * 0.0002f);
	set_grid_renderer_grid_size(zoom * 0.5f);
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		LOG("Usage: %s <tsp_file> <p>", argv[0]);
		EXIT_PROGRAM(1);
	}

	const char* filepath = argv[1];

	char* end;
	float p = strtof(argv[2], &end);

	if (*end != '\0')
	{
		LOG("ERROR: Invalid value for p: '%s'", argv[2]);
		EXIT_PROGRAM(2);
	}

	if (p < 0.0f || p > 1.0f)
	{
		LOG("ERROR: p must be between 0 and 1.");
		EXIT_PROGRAM(3);
	}
	
	tsp_instance = TSP_Instance_create(filepath, p);

	if (tsp_instance == NULL)
	{
		LOG("ERROR: Failed to load TSP problem");
		EXIT_PROGRAM(4);
	}

	TSP_Instance_set_random_source_target(tsp_instance);

	TSP_Instance_compute_shortest_path(tsp_instance);

	w = create_window(window_width, window_height, "Projet STDO");

	init_renderer();

	float aspect = (float) window_width / (float) window_height;

	c = create_camera(0.f, 0.f, 10.f, aspect);

	fit_camera();

	set_renderer_camera(c);

	while(!window_should_close(w))
	{
		handle_window_input(w, c);

		handle_algo_switch();
		handle_picking();

		render(tsp_instance);

		window_update_events(w);
		handle_window_resize(w, c);
	}

	free_renderer();

	free_window(w);
	TSP_Instance_free(tsp_instance);
}
