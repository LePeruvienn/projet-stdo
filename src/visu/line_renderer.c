#include "visu/line_renderer.h"
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

typedef struct line_rep line_rep;

struct line_rep
{
	float x1, y1;
	float x2, y2;
};

static camera line_camera = NULL;
static geometry line_geometry = NULL;
static shader line_shader = NULL;
static vertex_layout line_layout = NULL;

static GLuint instance_VBO;

static line_rep instances[MAX_INSTANCES_AMOUNT] = { 0 };
static size_t instances_amount = 0;


static float line_thickness = 0.05f;
static color line_color = (color) { .rgba = { 0x4D, 0x33, 0xFF, 0xFF },
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
	attributes[0].offset = offsetof(line_rep, x1);
	attributes[0].divisor = 1;

	attributes[1].id = INSTANCE_ATTR_LINE_P2;
	attributes[1].size = 2;
	attributes[1].type = GL_FLOAT;
	attributes[1].normalized = GL_FALSE;
	attributes[1].offset = offsetof(line_rep, x2);
	attributes[1].divisor = 1;

	return create_custom_layout(attributes, attributes_amount, sizeof(line_rep));
}

void init_line_renderer()
{
	if(is_intialized)
	{
		LOG_ERROR("Already intialized");
		return;
	}

	line_geometry = create_quad_geometry();

	line_shader = create_shader("asset/shader/line.vert",
	                             "asset/shader/line.frag");

	line_layout = create_instance_layout();

	CHECK_IS_NULL(line_geometry, "Failed to create line geometry");
	CHECK_IS_NULL(line_shader, "Failed to create line shader");
	CHECK_IS_NULL(line_layout, "Failed to create line vertex layout");

	bind_geometry(line_geometry);

	glGenBuffers(1, &instance_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	setup_vao_attributes(line_layout);

	unbind_geometry(line_geometry);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	is_intialized = true;
}

void line_begin_draw()
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

	if(line_camera == NULL)
	{
		LOG_ERROR("Cannot draw with a NULL camera");
		return;
	}

	instances_amount = 0;
	is_drawing = true;
}

void line_draw(float x1, float y1, float x2, float y2)
{
	if(is_drawing == false)
	{
		LOG_ERROR("Currently not drawing !!");
		return;
	}

	if(instances_amount == MAX_INSTANCES_AMOUNT)
	{
		LOG_ERROR("lineRep instances amount is full !");
		return;
	}

	instances[instances_amount].x1 = x1;
	instances[instances_amount].y1 = y1;
	instances[instances_amount].x2 = x2;
	instances[instances_amount].y2 = y2;

	++instances_amount;
}

void line_end_draw()
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

	bind_shader(line_shader);

	set_shader_line_color(line_shader, line_color);
	set_shader_line_thickness(line_shader, line_thickness);

	bind_geometry(line_geometry);

	set_shader_camera(line_shader, line_camera);

	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);

	glBufferData(
		GL_ARRAY_BUFFER,
		instances_amount * sizeof(line_rep),
		instances,
		GL_DYNAMIC_DRAW
	);

	draw_geometry_instanced(line_geometry, instances_amount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void free_line_renderer()
{
	glDeleteBuffers(1, &instance_VBO);

	FREE_PTR_NOT_NULL(line_geometry, free_geometry);
	FREE_PTR_NOT_NULL(line_shader, free_shader);
	FREE_PTR_NOT_NULL(line_layout, free_vertex_layout);

	is_intialized = false;
}

void set_line_renderer_camera(camera c)
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

	line_camera = c;
}

void set_line_renderer_color(color_rgba rgba)
{
	if(is_drawing)
	{
		line_end_draw();
		color_set_rgba(&line_color, rgba);
		line_begin_draw();
		return;
	}

	color_set_rgba(&line_color, rgba);
}

void set_line_renderer_thickness(float t)
{
	if(is_drawing)
	{
		line_end_draw();
		line_thickness = t;
		line_begin_draw();
		return;
	}

	line_thickness = t;
}
