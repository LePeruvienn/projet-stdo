#include "visu/circle_renderer.h"
#include "visu/vertex_layout.h"
#include "visu/geometry.h"
#include "visu/shader.h"

#include "utils/logger.h"
#include "utils/ptr.h"

#include "glad/glad.h"

#include <stdlib.h>
#include <stddef.h>

#define MAX_INSTANCES_AMOUNT 512

typedef struct circle_rep circle_rep;

struct circle_rep
{
	float x, y;
};

static geometry circle_geometry = NULL;
static shader circle_shader = NULL;
static vertex_layout circle_layout = NULL;

static GLuint instance_VBO;

static circle_rep instances[MAX_INSTANCES_AMOUNT] = { 0 };
static size_t instances_amount = 0;

static vertex_layout create_instance_layout()
{
	unsigned int attributes_amount = 1;

	vertex_attr attributes[attributes_amount];

	attributes[0].id = INSTANCE_ATTR_POSITION;
	attributes[0].size = 2;
	attributes[0].type = GL_FLOAT;
	attributes[0].normalized = GL_FALSE;
	attributes[0].offset = offsetof(circle_rep, x);
	attributes[0].divisor = 1;

	return create_custom_layout(attributes, attributes_amount, sizeof(circle_rep));
}

void init_circle_renderer()
{
	circle_geometry = create_circle_fan_geometry(50);

	circle_shader = create_shader("asset/shader/default.vert",
	                             "asset/shader/circle.frag");

	circle_layout = create_instance_layout();

	CHECK_IS_NULL(circle_geometry, "Failed to create circle geometry");
	CHECK_IS_NULL(circle_shader, "Failed to create circle shader");
	CHECK_IS_NULL(circle_layout, "Failed to create circle vertex layout");

	bind_geometry(circle_geometry);

	glGenBuffers(1, &instance_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	setup_vao_attributes(circle_layout);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void circle_begin_draw()
{
	instances_amount = 0;
}

void circle_draw(float x, float y)
{
	if(instances_amount == MAX_INSTANCES_AMOUNT)
	{
		LOG_ERROR("circleRep instances amount is full !");
		return;
	}

	instances[instances_amount].x = x;
	instances[instances_amount].y = y;

	++instances_amount;
}

void circle_end_draw(camera c)
{
	bind_shader(circle_shader);
	bind_geometry(circle_geometry);

	set_shader_camera(circle_shader, c);

	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);

	glBufferData(
		GL_ARRAY_BUFFER,
		instances_amount * sizeof(circle_rep),
		instances,
		GL_DYNAMIC_DRAW
	);

	draw_geometry_instanced(circle_geometry, instances_amount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void free_circle_renderer()
{
	glDeleteBuffers(1, &instance_VBO);

	FREE_PTR_NOT_NULL(circle_geometry, free_geometry);
	FREE_PTR_NOT_NULL(circle_shader, free_shader);
	FREE_PTR_NOT_NULL(circle_layout, free_vertex_layout);
}
