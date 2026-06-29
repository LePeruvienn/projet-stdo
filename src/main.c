#include "tsp/instance.h"

#include "visu/window.h"
#include "visu/camera.h"
#include "visu/renderer.h"

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <math.h>

static unsigned int window_width = 1280;
static unsigned int window_height = 960;

static window w = NULL;
static camera c = NULL;

static TSP_Instance tsp_instance;

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

	TSP_Instance_set_source(tsp_instance, 1);
	TSP_Instance_set_target(tsp_instance, 2);

	TSP_Instance_compute_shortest_path(tsp_instance);

	float aspect = (float) window_width / (float) window_height;

	c = create_camera(0.f, 0.f, 10.f, aspect);

	fit_camera();

	set_renderer_camera(c);

	while(!window_should_close(w))
	{
		handle_window_input(w, c);

		render(tsp_instance);

		window_update_events(w);
		handle_window_resize(w, c);
	}

	free_renderer();

	free_window(w);
	TSP_Instance_free(tsp_instance);
}
