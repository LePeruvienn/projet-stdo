#include "visu/window.h"
#include "visu/camera.h"
#include "visu/renderer.h"
#include "visu/circle_renderer.h"
#include "visu/line_renderer.h"
#include "visu/grid_renderer.h"
#include "visu/text_renderer.h"

#include "utils/logger.h"

#include "glad/glad.h"

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <time.h>
#include <threads.h>

#define _10e9 1000000000.0

struct window_s {
	GLFWwindow* handle;
	int width;
	int height;
};

static float scroll_delta = 0.f;

static void scroll_callback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset)
{
	scroll_delta += (float) yoffset;
}

/**
 * \brief Fonction de rappel appelée lors du redimensionnement de la fenêtre.
 *
 * Cette fonction est déclenchée automatiquement par GLFW chaque fois que 
 * l'utilisateur (ou le système d'exploitation) modifie la taille de la fenêtre. 
 * Elle se charge de mettre à jour la zone d'affichage OpenGL (Viewport) ainsi que 
 * les dimensions internes stockées dans la structure d'abstraction.
 *
 * \param handle Le pointeur natif de la fenêtre GLFW ayant déclenché l'événement.
 * \param width La nouvelle largeur physique (framebuffer) en pixels.
 * \param height La nouvelle hauteur physique (framebuffer) en pixels.
 */
static void framebuffer_size_callback(GLFWwindow* handle, int width, int height)
{
	glViewport(0, 0, width, height);
	
	window w = (window)glfwGetWindowUserPointer(handle);
	if (w) {
		w->width = width;
		w->height = height;
	}
}

/**
 * \brief Affiche les érreurs GLFW dans la console
 *
 * \param error code d'érrreur
 * \param desc message d'erreur
 */
static void error_callback(int error, const char* desc)
{
	LOG("[GLFW ERROR] %d: %s", error, desc);
}

window create_window(int width, int height, const char* title)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		LOG_ERROR("Failed to initialize GLFW.");
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4); 

	window w = malloc(sizeof(struct window_s));
	if (!w) return NULL;

	w->width = width;
	w->height = height;
	w->handle = glfwCreateWindow(width, height, title, NULL, NULL);

	if (w->handle == NULL) {
		LOG_ERROR("Failed to create GLFW window.");
		free(w);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(w->handle);
	glfwSetWindowUserPointer(w->handle, w);
	glfwSetFramebufferSizeCallback(w->handle, framebuffer_size_callback);
	glfwSetScrollCallback(w->handle, scroll_callback);

	// On désactive le V-Sync
	glfwSwapInterval(0);

	return w;
}

void free_window(window w)
{
	if (!w) return;
	if (w->handle) glfwDestroyWindow(w->handle);
	free(w);
	glfwTerminate();
}

bool window_should_close(window w) 
{
	return glfwWindowShouldClose(w->handle); 
}

void window_update_events(window w) 
{
	glfwSwapBuffers(w->handle); 
	glfwPollEvents(); 
}

void window_wait_events(window w, double timeout)
{
	(void) w;

	struct timespec ts;

	ts.tv_sec  = (time_t) timeout;
	ts.tv_nsec = (long) ((timeout - ts.tv_sec) * _10e9);

	thrd_sleep(&ts, NULL);
}
int window_get_width(window w) 
{
	return w->width; 
}

int window_get_height(window w) 
{
	return w->height; 
}

float window_get_time(window w) 
{
	(void)w; 
	return (float)glfwGetTime(); 
}

void* window_get_native_handle(window w) 
{
	return w->handle; 
}

void window_get_framebuffer_size(window w, int* width, int* height) 
{
	if (w && w->handle)
	{
		glfwGetFramebufferSize(w->handle, width, height);
	}
}


void handle_window_input(window w, camera c)
{
	GLFWwindow* handle = w->handle;

	static bool dragging = false;
	static double last_mouse_x = 0.0;
	static double last_mouse_y = 0.0;

	float current_zoom = get_camera_zoom(c);
	float dx = 0.f;
	float dy = 0.f;

	float zoom_speed = 1.f / 5.f;
	float dzoom = scroll_delta / zoom_speed;
	scroll_delta = 0.f;

	int mouse_button = glfwGetMouseButton(handle, GLFW_MOUSE_BUTTON_LEFT);
	double mouse_x, mouse_y;
	glfwGetCursorPos(handle, &mouse_x, &mouse_y);

	if (mouse_button == GLFW_PRESS)
	{
		if (dragging)
		{
			float speed = current_zoom * 0.1f;

			dx = (float)(last_mouse_x - mouse_x) * speed * 0.01f;
			dy = (float)(mouse_y - last_mouse_y) * speed * 0.01f;
		}
		dragging = true;

		last_mouse_x = mouse_x;
		last_mouse_y = mouse_y;
	}
	else
	{
		dragging = false;
	}

	camera_move(c, dx, dy, dzoom);


	bool renderer_init = renderer_get_is_intialized();

	float circle_scale_speed = 1.f;
	float text_scale_speed = 0.5f;
	float line_scale_speed = 0.01f;
	float grid_scale_speed = 1.f;

	if (renderer_init)
	{
		bool shift = glfwGetKey(handle, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
		             glfwGetKey(handle, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS;

		bool scale_circle = glfwGetKey(handle, GLFW_KEY_C) == GLFW_PRESS;
		bool scale_line = glfwGetKey(handle, GLFW_KEY_L) == GLFW_PRESS;
		bool scale_grid = glfwGetKey(handle, GLFW_KEY_G) == GLFW_PRESS;

		bool toggle_draw_help = glfwGetKey(handle, GLFW_KEY_H) == GLFW_PRESS;

		if (toggle_draw_help)
		{
			renderer_set_draw_help(shift);
		}

		if (scale_circle)
		{
			if (shift)
			{
				add_circle_renderer_scale(+circle_scale_speed);
				add_text_renderer_text_size(+text_scale_speed);
			}
			else
			{
				add_circle_renderer_scale(-circle_scale_speed);
				add_text_renderer_text_size(-text_scale_speed);
			}
		}

		if (scale_line)
		{
			if (shift) add_line_renderer_thickness(-line_scale_speed);
			else       add_line_renderer_thickness(+line_scale_speed);
		}

		if(scale_grid)
		{
			if (shift) add_grid_renderer_grid_size(-grid_scale_speed);
			else       add_grid_renderer_grid_size(+grid_scale_speed);
		}
	}
}

void handle_window_resize(window w, camera c)
{
	int fb_w, fb_h;
	window_get_framebuffer_size(w, &fb_w, &fb_h);

	if (fb_h > 0) 
	{
		set_camera_aspect(c, (float) fb_w / (float) fb_h);
		glViewport(0, 0, fb_w, fb_h);
	}
}

mouse_status window_get_mouse_status(window w)
{
	int left_click = glfwGetMouseButton(w->handle, GLFW_MOUSE_BUTTON_LEFT);
	int right_click = glfwGetMouseButton(w->handle, GLFW_MOUSE_BUTTON_RIGHT);

	double x, y;

	glfwGetCursorPos(w->handle, &x, &y);

	return (mouse_status) {(float) x, (float) y, left_click, right_click};
}
