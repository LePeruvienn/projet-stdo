#include "tsp/parser.h"
#include "tsp/instance.h"

#include "visu/window.h"
#include "visu/camera.h"
#include "visu/renderer.h"


#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <stdbool.h>

static unsigned int window_width = 1280;
static unsigned int window_height = 960;

static window w = NULL;
static camera c = NULL;

static TSP_Instance tsp_instance;

int main(void)
{
	w = create_window(window_width, window_height, "Projet STDO");

	init_renderer();
	
	const char* filepath = "TSPLIB/res/a280.tsp";
	tsp_instance = TSP_Instance_create(filepath, 0.05f);

	float aspect = (float) window_width / (float) window_height;

	c = create_camera(0.f, 0.f, 10.f, aspect);

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
