#include "tsp/parser.h"
#include "tsp/file.h"
#include "tsp/section.h"

#include "visu/window.h"
#include "visu/camera.h"
#include "visu/circle_renderer.h"
#include "visu/edge_renderer.h"
#include "visu/grid_renderer.h"
#include "visu/text_renderer.h"

#include "utils/logger.h"

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <math.h>

static unsigned int window_width = 1280;
static unsigned int window_height = 960;

static window w = NULL;
static camera c = NULL;

static TSP_File tsp_file = NULL;

void render()
{
	// TSP_Section_Data data = TSP_Section_get_data(tsp_file->NODE_COORD_SECTION);
	// TSP_Node_Coord* nodes_coords = data.coords;

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	set_grid_renderer_grid_size(10.f);
	set_grid_renderer_bg_color((color_rgba) {0x0F, 0x0F, 0x0F, 0xFF});
	set_grid_renderer_line_color((color_rgba) {0x44, 0x44, 0x44, 0xFF});
	
	draw_grid();

	float x1 = 5.f;
	float y1 = 5.f;

	float x2 =   5.f;
	float y2 = - 5.f;

	float x3 = - 5.f;
	float y3 = - 5.f;

	// IL FAUT SET AVANT DE DRAW (sinon bug jsp pk)
	set_edge_renderer_color((color_rgba) {0x00, 0xFF, 0x00, 0xFF});

	edge_begin_draw();

	edge_draw(x1, y1, x2, y2);
	
	set_edge_renderer_color((color_rgba) {0xFF, 0xFF, 0x00, 0xFF});

	edge_draw(x2, y2, x3, y3);

	edge_end_draw();

	// IL FAUT SET AVANT DE DRAW (sinon bug jsp pk)
	set_circle_renderer_fill_color((color_rgba) {0x00, 0x00, 0x00, 0xFF});

	circle_begin_draw();

	/*
	for (size_t i = 0; i < data.size; ++i)
	{
		float x = nodes_coords[i].px;
		float y = nodes_coords[i].py;

		circle_draw(x, y);
	}
	*/

	circle_draw(x1, y1);

	set_circle_renderer_fill_color((color_rgba) {0xFF, 0xFF, 0xFF, 0xFF});

	circle_draw(x3, y3);

	circle_end_draw();


	text_begin_draw();

	for (char i = 0; i < 100; ++i)
	{
		draw_char((char)('!' + i), (float) i * 2, 0.f);
	}


	text_end_draw();
}

void handle_input()
{
	GLFWwindow* handle = (GLFWwindow*) window_get_native_handle(w);

	bool up = glfwGetKey(handle, GLFW_KEY_W) == GLFW_PRESS;
	bool left = glfwGetKey(handle, GLFW_KEY_A) == GLFW_PRESS;
	bool down = glfwGetKey(handle, GLFW_KEY_S) == GLFW_PRESS;
	bool right = glfwGetKey(handle, GLFW_KEY_D) == GLFW_PRESS;

	bool zooming = glfwGetKey(handle, GLFW_KEY_SPACE) == GLFW_PRESS;
	bool dezooming = glfwGetKey(handle, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

	float current_zoom = get_camera_zoom(c);

	float speed = (1.f / 10.f) * fmin(current_zoom, 1.f);
	float zoom_speed = 1.f / 10.f;

	float dx = 0.f;
	float dy = 0.f;
	float dzoom = 0.f;

	if (up) dy += speed;
	if (down) dy -= speed;
	if (right) dx += speed;
	if (left) dx -= speed;

	if (zooming) dzoom += zoom_speed;
	if (dezooming) dzoom -= zoom_speed;

	camera_move(c, dx, dy, dzoom);
}

void handle_window_resize()
{
	int fb_w, fb_h;
	window_get_framebuffer_size(w, &fb_w, &fb_h);

	if (fb_h > 0) 
	{
		set_camera_aspect(c, (float) fb_w / (float) fb_h);
		glViewport(0, 0, fb_w, fb_h);
	}
}

int main(void)
{
	w = create_window(window_width, window_height, "Projet STDO");

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

	const char* filepath = "TSPLIB/res/a280.tsp";
	tsp_file = TSP_parse_file(filepath);

	init_circle_renderer();
	init_edge_renderer();
	init_grid_renderer();
	init_text_renderer();

	float aspect = (float) window_width / (float) window_height;

	c = create_camera(0.f, 0.f, 10.f, aspect);

	set_circle_renderer_camera(c);
	set_grid_renderer_camera(c);
	set_edge_renderer_camera(c);
	set_text_renderer_camera(c);

	while(!window_should_close(w))
	{
		handle_input();
		render();
		window_update_events(w);
		handle_window_resize();
	}

	free_circle_renderer();
	free_edge_renderer();
	free_grid_renderer();
	free_text_renderer();

	free_window(w);
	TSP_File_free(tsp_file);
}
