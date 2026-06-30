#include "tsp/instance.h"
#include "tsp/section_datas.h"

#include "visu/window.h"
#include "visu/camera.h"
#include "visu/renderer.h"

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

static TSP_Instance tsp_instance;

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

	float zoom = fmaxf(span_x / (float) window_width, span_y / (float) window_height);

	zoom *= 1.1f;

	camera_move(c, center_x, center_y, zoom);
}


int main(void)
{
	w = create_window(window_width, window_height, "Projet STDO");

	init_renderer();
	
	const char* filepath = "TSPLIB/res/att48.tsp";
	tsp_instance = TSP_Instance_create(filepath, 0.5f);

	TSP_Instance_set_random_source_target(tsp_instance);

	TSP_Instance_compute_shortest_path(tsp_instance);

	float aspect = (float) window_width / (float) window_height;

	c = create_camera(0.f, 0.f, 10.f, aspect);

	fit_camera();

	set_renderer_camera(c);

	while(!window_should_close(w))
	{
		handle_window_input(w, c);

		handle_picking();
	
		render(tsp_instance);

		window_update_events(w);
		handle_window_resize(w, c);
	}

	free_renderer();

	free_window(w);
	TSP_Instance_free(tsp_instance);
}
