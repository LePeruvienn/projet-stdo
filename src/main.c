#include "visu/window.h"
#include "visu/camera.h"
#include "visu/node_renderer.h"

#include "utils/logger.h"

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <math.h>

static unsigned int window_width = 1280;
static unsigned int window_height = 960;

static window w = NULL;
static camera c = NULL;

void render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	node_begin_draw();

	node_draw(0.f, 0.f);
	node_draw(2.f, 2.f);
	node_draw(2.f, 0.f);
	node_draw(0.f, 2.f);

	node_end_draw(c);
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

	float speed = (1.f / 1000.f) * fmin(current_zoom, 1.f);
	float zoom_speed = 1.f / 10000.f;

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

	init_node_renderer();

	float aspect = (float) window_width / (float) window_height;

	c = create_camera(0.f, 0.f, 1.f, aspect);

	while(!window_should_close(w))
	{
		handle_input();
		render();
		window_update_events(w);
		handle_window_resize();
	}

	free_node_renderer();
	free_window(w);
}
