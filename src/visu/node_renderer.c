#include "visu/node_renderer.h"
#include "visu/vertex_layout.h"
#include "visu/geometry.h"
#include "visu/shader.h"

#include "utils/logger.h"
#include "utils/ptr.h"

#include "glad/glad.h"

#include <stdlib.h>
#include <stddef.h>

#define MAX_INSTANCES_AMOUNT 512

typedef struct node_rep node_rep;

struct node_rep
{
	float x, y;
};

static geometry node_geometry = NULL;
static shader node_shader = NULL;
static vertex_layout node_layout = NULL;

static GLuint instance_VBO;

static node_rep instances[MAX_INSTANCES_AMOUNT] = { 0 };
static size_t instances_amount = 0;

vertex_layout create_instance_layout()
{
	unsigned int attributes_amount = 1;

	vertex_attr attributes[attributes_amount];

	attributes[0].id = INSTANCE_ATTR_POSITION;
	attributes[0].size = 2;
	attributes[0].type = GL_FLOAT;
	attributes[0].normalized = GL_FALSE;
	attributes[0].offset = offsetof(node_rep, x);
	attributes[0].divisor = 1;

	return create_custom_layout(attributes, attributes_amount, sizeof(node_rep));
}

void init_node_renderer()
{
	node_geometry = create_circle_fan_geometry(50);

	node_shader = create_shader("asset/shader/default.vert",
	                             "asset/shader/circle.frag");

	node_layout = create_instance_layout();

	CHECK_IS_NULL(node_geometry, "Failed to create node geometry");
	CHECK_IS_NULL(node_shader, "Failed to create node shader");
	CHECK_IS_NULL(node_layout, "Failed to create node vertex layout");

	bind_geometry(node_geometry);

	glGenBuffers(1, &instance_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	setup_vao_attributes(node_layout);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void node_begin_draw()
{
	instances_amount = 0;
}

void node_draw(float x, float y)
{
	if(instances_amount == MAX_INSTANCES_AMOUNT)
	{
		LOG_ERROR("NodeRep instances amount is full !");
		return;
	}

	instances[instances_amount].x = x;
	instances[instances_amount].y = y;

	++instances_amount;
}

void node_end_draw(camera c)
{
	bind_shader(node_shader);
	bind_geometry(node_geometry);

	set_shader_camera(node_shader, c);

	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);

	glBufferData(
		GL_ARRAY_BUFFER,
		instances_amount * sizeof(node_rep),
		instances,
		GL_DYNAMIC_DRAW
	);

	draw_geometry_instanced(node_geometry, instances_amount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void free_node_renderer()
{
	glDeleteBuffers(1, &instance_VBO);

	FREE_PTR_NOT_NULL(node_geometry, free_geometry);
	FREE_PTR_NOT_NULL(node_shader, free_shader);
	FREE_PTR_NOT_NULL(node_layout, free_vertex_layout);
}
