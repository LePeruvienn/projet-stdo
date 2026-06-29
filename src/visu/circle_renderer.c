#include "visu/circle_renderer.h"
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

typedef struct circle_rep circle_rep;

struct circle_rep
{
	float x, y;
};

static camera circle_camera = NULL;
static geometry circle_geometry = NULL;
static shader circle_shader = NULL;
static vertex_layout circle_layout = NULL;

static GLuint instance_VBO;

static circle_rep instances[MAX_INSTANCES_AMOUNT] = { 0 };
static size_t instances_amount = 0;


static color circle_color = { .rgba = {  0x78,  0xD9,  0x76, 0xFF },
                              .norm = { 0.471, 0.851, 0.463, 1.0  } };

static color border_color = { .rgba = {  0xD7,  0x76,  0xD9, 0xFF },
                              .norm = { 0.843, 0.463, 0.851, 1.0  } };

static float circle_scale = 10.f;
static float circle_radius = 1.f;
static float border_thikness = 0.1f;

static bool is_drawing = false;
static bool is_intialized = false;

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
	if (is_intialized)
	{
		LOG_ERROR("Already initialized !");
		return;
	}

	circle_geometry = create_circle_fan_geometry(50);

	circle_shader = create_shader("asset/shader/circle.vert",
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

	is_intialized = true;
}

void circle_begin_draw()
{
	if (is_intialized == false)
	{
		LOG_ERROR("Not initialized !");
		return;
	}

	if(circle_camera == NULL)
	{
		LOG_ERROR("Cannot draw on a NULL camera");
		return;
	}

	if(is_drawing == true)
	{
		LOG_ERROR("Already drawing !");
		return;
	}

	instances_amount = 0;
	is_drawing = true;
}

void circle_draw(float x, float y)
{
	if(is_drawing == false)
	{
		LOG_ERROR("Call draw but wasnt drawing.");
		return;
	}

	if(instances_amount == MAX_INSTANCES_AMOUNT)
	{
		LOG_ERROR("circleRep instances amount is full !");
		return;
	}

	instances[instances_amount].x = x;
	instances[instances_amount].y = y;

	++instances_amount;
}

void circle_end_draw()
{
	if(is_drawing == false)
	{
		LOG_ERROR("Call end draw but wasnt drawing.");
		return;
	}

	is_drawing = false;

	if (instances_amount == 0)
	{
		// LOG_WARNING("Draw on 0 instance");
		return;
	}

	bind_shader(circle_shader);

	set_shader_circle_color(circle_shader, circle_color);
	set_shader_circle_radius(circle_shader, circle_radius);

	set_shader_circle_border_color(circle_shader, border_color);
	set_shader_circle_border_thinkness(circle_shader, border_thikness);

	set_shader_model_scale(circle_shader, circle_scale, circle_scale);

	bind_geometry(circle_geometry);

	set_shader_camera(circle_shader, circle_camera);

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

void set_circle_renderer_camera(camera c)
{
	if(c == NULL)
	{
		LOG_ERROR("Camera cannot be NULL");
		return;
	}

	if (is_drawing)
	{
		LOG_ERROR("Cannot change camera while drawing!");
		return;
	}

	circle_camera = c;
}

void set_circle_renderer_fill_color(color_rgba c)
{
	if(is_drawing)
	{
		circle_end_draw();
		color_set_rgba(&circle_color, c);
		circle_begin_draw();
		return;
	}

	color_set_rgba(&circle_color, c);
}

void set_circle_renderer_border_color(color_rgba c)
{
	if(is_drawing)
	{
		circle_end_draw();
		color_set_rgba(&border_color, c);
		circle_begin_draw();
		return;
	}

	color_set_rgba(&border_color, c);
}

void set_circle_renderer_radius(float r)
{
	if(is_drawing)
	{
		circle_end_draw();
		circle_radius = r;
		circle_begin_draw();
		return;
	}

	circle_radius = r;
}

void set_circle_renderer_border_thickness(float t)
{
	if(is_drawing)
	{
		circle_end_draw();
		border_thikness = t;
		circle_begin_draw();
		return;
	}

	border_thikness = t;
}

void set_circle_renderer_scale(float s)
{
	if (is_drawing)
	{
		circle_end_draw();
		circle_scale = s;
		circle_begin_draw();
		return;
	}

	circle_scale = s;
}

void add_circle_renderer_scale(float s)
{
	if (is_drawing)
	{
		circle_end_draw();
		circle_scale += s;
		circle_begin_draw();
		return;
	}

	circle_scale += s;
}
