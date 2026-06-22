#include "visu/grid_renderer.h"
#include "visu/vertex_layout.h"
#include "visu/geometry.h"
#include "visu/shader.h"
#include "visu/camera.h"

#include "utils/ptr.h"

static geometry grid_geometry = NULL;
static shader grid_shader = NULL;

void init_grid_renderer()
{
	grid_geometry = create_quad_geometry();
	grid_shader = create_shader("asset/shader/grid.vert", "asset/shader/grid.frag");
}

void draw_grid(camera c)
{
	bind_shader(grid_shader);

	set_shader_camera(grid_shader, c);
	
	bind_geometry(grid_geometry);
	draw_geometry(grid_geometry);
}

void free_grid_renderer()
{
	FREE_PTR_NOT_NULL(grid_geometry, free_geometry);
	FREE_PTR_NOT_NULL(grid_shader, free_shader);
}


