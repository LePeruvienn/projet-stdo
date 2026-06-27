#include "visu/edge_renderer.h"
#include "visu/vertex_layout.h"
#include "visu/geometry.h"
#include "visu/shader.h"
#include "visu/color.h"

#include "utils/logger.h"
#include "utils/ptr.h"

#include "glad/glad.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#define MAX_INSTANCES_AMOUNT 512

typedef struct edge_rep edge_rep;

struct edge_rep
{
	float x1, y1;
	float x2, y2;
};

static camera edge_camera = NULL;
static geometry edge_geometry = NULL;
static shader edge_shader = NULL;
static vertex_layout edge_layout = NULL;

static GLuint instance_VBO;

static edge_rep instances[MAX_INSTANCES_AMOUNT] = { 0 };
static size_t instances_amount = 0;


static float edge_thickness = 0.05f;
static color edge_color = (color) { .rgba = { 0x4D, 0x33, 0xFF, 0xFF },
                                    .norm = { 0.3f, 0.2f, 1.f, 1.f   } };

static bool is_drawing = false;
static bool is_intialized = false;

static vertex_layout create_instance_layout()
{
	unsigned int attributes_amount = 2;

	vertex_attr attributes[attributes_amount];

	attributes[0].id = INSTANCE_ATTR_LINE_P1;
	attributes[0].size = 2;
	attributes[0].type = GL_FLOAT;
	attributes[0].normalized = GL_FALSE;
	attributes[0].offset = offsetof(edge_rep, x1);
	attributes[0].divisor = 1;

	attributes[1].id = INSTANCE_ATTR_LINE_P2;
	attributes[1].size = 2;
	attributes[1].type = GL_FLOAT;
	attributes[1].normalized = GL_FALSE;
	attributes[1].offset = offsetof(edge_rep, x2);
	attributes[1].divisor = 1;

	return create_custom_layout(attributes, attributes_amount, sizeof(edge_rep));
}

void init_edge_renderer()
{
	if(is_intialized)
	{
		LOG_ERROR("Already intialized");
		return;
	}

	edge_geometry = create_quad_geometry();

	edge_shader = create_shader("asset/shader/edge.vert",
	                             "asset/shader/edge.frag");

	edge_layout = create_instance_layout();

	CHECK_IS_NULL(edge_geometry, "Failed to create edge geometry");
	CHECK_IS_NULL(edge_shader, "Failed to create edge shader");
	CHECK_IS_NULL(edge_layout, "Failed to create edge vertex layout");

	bind_geometry(edge_geometry);

	glGenBuffers(1, &instance_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	setup_vao_attributes(edge_layout);

	unbind_geometry(edge_geometry);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	is_intialized = true;
}

void edge_begin_draw()
{
	if(is_intialized == false)
	{
		LOG_ERROR("Renderer not initialized");
		return;
	}

	if(is_drawing)
	{
		LOG_ERROR("Draw has already begun");
		return;
	}

	if(edge_camera == NULL)
	{
		LOG_ERROR("Cannot draw with a NULL camera");
		return;
	}

	instances_amount = 0;
	is_drawing = true;
}

void edge_draw(float x1, float y1, float x2, float y2)
{
	if(is_drawing == false)
	{
		LOG_ERROR("Currently not drawing !!");
		return;
	}

	if(instances_amount == MAX_INSTANCES_AMOUNT)
	{
		LOG_ERROR("edgeRep instances amount is full !");
		return;
	}

	instances[instances_amount].x1 = x1;
	instances[instances_amount].y1 = y1;
	instances[instances_amount].x2 = x2;
	instances[instances_amount].y2 = y2;

	++instances_amount;
}

void edge_end_draw()
{
	if(is_drawing == false)
	{
		LOG_ERROR("Draw has not begun !");
		return;
	}

	is_drawing = false;

	if (instances_amount == 0)
	{
		// LOG_WARNING("Draw on 0 instance");
		return;
	}

	bind_shader(edge_shader);

	set_shader_edge_color(edge_shader, edge_color);
	set_shader_edge_thickness(edge_shader, edge_thickness);

	bind_geometry(edge_geometry);

	set_shader_camera(edge_shader, edge_camera);

	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);

	glBufferData(
		GL_ARRAY_BUFFER,
		instances_amount * sizeof(edge_rep),
		instances,
		GL_DYNAMIC_DRAW
	);

	draw_geometry_instanced(edge_geometry, instances_amount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void free_edge_renderer()
{
	glDeleteBuffers(1, &instance_VBO);

	FREE_PTR_NOT_NULL(edge_geometry, free_geometry);
	FREE_PTR_NOT_NULL(edge_shader, free_shader);
	FREE_PTR_NOT_NULL(edge_layout, free_vertex_layout);

	is_intialized = false;
}

void set_edge_renderer_camera(camera c)
{
	if (c == NULL)
	{
		LOG_ERROR("Cannot set a NULL camera");
		return;
	}

	if(is_drawing)
	{
		LOG_ERROR("Canno change camera during draw");
		return;
	}

	edge_camera = c;
}

void set_edge_renderer_color(color_rgba rgba)
{
	if(is_drawing)
	{
		edge_end_draw();
		color_set_rgba(&edge_color, rgba);
		edge_begin_draw();
		return;
	}

	color_set_rgba(&edge_color, rgba);
}

void set_edge_renderer_thickness(float t)
{
	if(is_drawing)
	{
		edge_end_draw();
		edge_thickness = t;
		edge_begin_draw();
		return;
	}

	edge_thickness = t;
}
