#include "visu/window.h"
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

