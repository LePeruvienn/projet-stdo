#include "visu/window.h"
#include "visu/shader.h"
#include "visu/geometry.h"

#include "utils/logger.h"

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <stdbool.h>

static unsigned int window_width = 1280;
static unsigned int window_height = 960;

static window w = NULL;
static camera c = NULL;
static geometry g = NULL;


void render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	bind_shader(global_default_shader);
	set_shader_camera(global_default_shader, c);

	bind_geometry(g);
	draw_geometry(g);
}

void handle_input()
{
	GLFWwindow* handle = (GLFWwindow*) window_get_native_handle(w);

	bool up = glfwGetKey(handle, GLFW_KEY_W) == GLFW_PRESS;
	bool left = glfwGetKey(handle, GLFW_KEY_A) == GLFW_PRESS;
	bool down = glfwGetKey(handle, GLFW_KEY_S) == GLFW_PRESS;
	bool right = glfwGetKey(handle, GLFW_KEY_D) == GLFW_PRESS;

	bool zoom = glfwGetKey(handle, GLFW_KEY_SPACE) == GLFW_PRESS;
	bool dezoom = glfwGetKey(handle, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;

	float speed = 1.f / 1000.f;
	float zoom_speed = 1.f / 10000.f;

	float dx = 0.f;
	float dy = 0.f;
	float dzoom = 0.f;

	if (up) dy += speed;
	if (down) dy -= speed;
	if (right) dx += speed;
	if (left) dx -= speed;

	if (zoom) dzoom += zoom_speed;
	if (dezoom) dzoom -= zoom_speed;

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

	create_global_shaders();

	float aspect = (float) window_width / (float) window_height;

	c = create_camera(0.f, 0.f, 1.f, aspect);
	g = create_quad_geometry();

	while(!window_should_close(w))
	{
		handle_input();
		render();
		window_update_events(w);
		handle_window_resize();
	}

	free_window(w);
}
