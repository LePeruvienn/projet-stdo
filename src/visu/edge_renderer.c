#include "visu/edge_renderer.h"
#include "visu/vertex_layout.h"
#include "visu/geometry.h"
#include "visu/shader.h"

#include "utils/logger.h"
#include "utils/ptr.h"

#include "glad/glad.h"

#include <stdlib.h>
#include <stddef.h>

#define MAX_INSTANCES_AMOUNT 512

typedef struct edge_rep edge_rep;

struct edge_rep
{
	float x1, y1;
	float x2, y2;
};

static geometry edge_geometry = NULL;
static shader edge_shader = NULL;
static vertex_layout edge_layout = NULL;

static GLuint instance_VBO;

static edge_rep instances[MAX_INSTANCES_AMOUNT] = { 0 };
static size_t instances_amount = 0;

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
	edge_geometry = create_quad_geometry();

	edge_shader = create_shader("asset/shader/edge.vert",
	                             "asset/shader/default.frag");

	edge_layout = create_instance_layout();

	CHECK_IS_NULL(edge_geometry, "Failed to create edge geometry");
	CHECK_IS_NULL(edge_shader, "Failed to create edge shader");
	CHECK_IS_NULL(edge_layout, "Failed to create edge vertex layout");

	bind_geometry(edge_geometry);

	glGenBuffers(1, &instance_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	setup_vao_attributes(edge_layout);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void edge_begin_draw()
{
	instances_amount = 0;
}

void edge_draw(float x1, float y1, float x2, float y2)
{
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

void edge_end_draw(camera c)
{
	bind_shader(edge_shader);
	bind_geometry(edge_geometry);

	set_shader_camera(edge_shader, c);

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
}
