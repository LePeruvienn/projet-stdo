#include "visu/grid_renderer.h"
#include "visu/geometry.h"
#include "visu/shader.h"
#include "visu/camera.h"
#include "visu/color.h"

#include "utils/logger.h"
#include "utils/ptr.h"

#include <stdbool.h>

static camera grid_camera = NULL;
static geometry grid_geometry = NULL;
static shader grid_shader = NULL;


static float grid_size = 5.f;

static color background_color = { .rgba = { 0x1A, 0x1A, 0x1A, 0xFF },
                                  .norm = { 0.1f, 0.1f, 0.1f, 1.f  } };

static color line_color       = { .rgba = { 0x4D, 0x4D, 0x4D, 0xFF },
                                  .norm = { 0.3f, 0.3f, 0.3f, 1.f  } };

static bool is_initialized = false;

void init_grid_renderer()
{
	if (is_initialized)
	{
		LOG_ERROR("Already initialized!");
		return;
	}

	grid_geometry = create_quad_geometry();
	grid_shader = create_shader("asset/shader/grid.vert", "asset/shader/grid.frag");

	is_initialized = true;
}

void draw_grid()
{
	if(is_initialized == false)
	{
		LOG_ERROR("Cannot draw before initializion !");
		return;
	}

	if(grid_camera == NULL)
	{
		LOG_ERROR("Cannot draw without camera !!");
		return;
	}

	bind_shader(grid_shader);

	set_shader_grid_size(grid_shader, grid_size);
	set_shader_grid_bg_color(grid_shader, background_color);
	set_shader_grid_line_color(grid_shader, line_color);

	set_shader_camera(grid_shader, grid_camera);
	
	bind_geometry(grid_geometry);
	draw_geometry(grid_geometry);
}

void free_grid_renderer()
{
	is_initialized = false;

	FREE_PTR_NOT_NULL(grid_geometry, free_geometry);
	FREE_PTR_NOT_NULL(grid_shader, free_shader);
}

void set_grid_renderer_camera(camera c)
{
	if (c == NULL)
	{
		LOG_ERROR("Camera cannot be NULL !!");
		return;
	}

	grid_camera = c;
}

void set_grid_renderer_bg_color(color_rgba rgba)
{
	color_set_rgba(&background_color, rgba);
}

void set_grid_renderer_line_color(color_rgba rgba)
{
	color_set_rgba(&line_color, rgba);
}

void set_grid_renderer_grid_size(float size)
{
	grid_size = size;
}

