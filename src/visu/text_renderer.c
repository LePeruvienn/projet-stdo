#include "visu/text_renderer.h"
#include "visu/vertex_layout.h"
#include "visu/texture.h"
#include "visu/geometry.h"
#include "visu/shader.h"
#include "visu/color.h"
#include "visu/camera.h"

#include "utils/logger.h"
#include "utils/debug.h"
#include "utils/ptr.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define BITMAP_PATH "asset/bitmap/font.bmp"
#define MAX_INSTANCES_AMOUNT 1024

typedef struct char_rep char_rep;

struct char_rep
{
	uint8_t id;
	float x, y;
};

static camera text_camera = NULL;
static texture bitmap_texture = NULL;
static geometry text_geometry = NULL;
static shader text_shader = NULL;

static vertex_layout text_layout = NULL;

static GLuint instance_VBO;
static char_rep instances[MAX_INSTANCES_AMOUNT] = { 0 };
static size_t instances_amount = 0;

static color text_color = (color) { .rgba = {255, 255, 255, 255 },
                                    .norm = {1.f, 1.f, 1.f, 1.f } };

static float char_space_size = 1.5f;
static float text_size = 0.5f;

static bool is_intialized = false;
static bool is_drawing = false;

static vertex_layout create_instance_layout()
{
	unsigned int attributes_amount = 2;

	vertex_attr attributes[attributes_amount];

	attributes[0].id = INSTANCE_ATTR_CHAR_ID;
	attributes[0].size = 1;
	attributes[0].type = GL_UNSIGNED_BYTE;
	attributes[0].normalized = GL_FALSE;
	attributes[0].offset = offsetof(char_rep, id);
	attributes[0].divisor = 1;

	attributes[1].id = INSTANCE_ATTR_POSITION;
	attributes[1].size = 2;
	attributes[1].type = GL_FLOAT;
	attributes[1].normalized = GL_FALSE;
	attributes[1].offset = offsetof(char_rep, x);
	attributes[1].divisor = 1;

	return create_custom_layout(attributes, attributes_amount, sizeof(char_rep));
}

void init_text_renderer()
{
	if(is_intialized)
	{
		LOG_ERROR("Already intialized !");
		return;
	}

	bitmap_texture = create_texture(BITMAP_PATH);
	text_geometry = create_quad_geometry();
	text_shader = create_shader("asset/shader/text.vert", "asset/shader/text.frag");
	text_layout = create_instance_layout();

	CHECK_IS_NULL(bitmap_texture, "Failed to load bitmap texture.");
	CHECK_IS_NULL(text_geometry, "Failed to load text geometry");
	CHECK_IS_NULL(text_shader, "Failed to load text shader");

	bind_geometry(text_geometry);

	glGenBuffers(1, &instance_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);
	setup_vao_attributes(text_layout);

	unbind_geometry(text_geometry);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	is_intialized = true;
}

void text_begin_draw()
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

	if(text_camera == NULL)
	{
		LOG_ERROR("Cannot draw with a NULL camera");
		return;
	}

	instances_amount = 0;
	is_drawing = true;
}

void draw_char(char c, float x, float y)
{
	if(is_drawing == false)
	{
		LOG_ERROR("Currently not drawing !!");
		return;
	}

	if(instances_amount == MAX_INSTANCES_AMOUNT)
	{
		LOG_ERROR("textRep instances amount is full !");
		return;
	}

	instances[instances_amount].id = (int) (c - '!');
	instances[instances_amount].x  = x;
	instances[instances_amount].y  = y;

	// LOG_INFO("Char ID : %d", id);

	++instances_amount;
}

void draw_text(const char* text, float x, float y)
{
	size_t len = strlen(text);

	for(size_t i = 0; i < len; ++i)
	{
		char c = text[i];

		if (c == ' ')
		{
			continue;
		}

		float px = x + (i * char_space_size * text_size);
		float py = y;

		draw_char(c, px, py);
	}
}

void text_end_draw()
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

	bind_shader(text_shader);

	unsigned int texture_unit = 0;
	bind_texture(bitmap_texture, texture_unit);
	set_shader_texture_unit(text_shader, texture_unit);

	set_shader_text_size(text_shader, text_size);
	set_shader_text_color(text_shader, text_color);
	set_shader_camera(text_shader, text_camera);

	bind_geometry(text_geometry);

	glBindBuffer(GL_ARRAY_BUFFER, instance_VBO);

	GL_CALL(glBufferData(
		GL_ARRAY_BUFFER,
		instances_amount * sizeof(char_rep),
		instances,
		GL_DYNAMIC_DRAW
	));

	draw_geometry_instanced(text_geometry, instances_amount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void free_text_renderer()
{
	FREE_PTR_NOT_NULL(text_shader, free_shader);
	FREE_PTR_NOT_NULL(bitmap_texture, free_texture);
	FREE_PTR_NOT_NULL(text_geometry, free_geometry);
}

void set_text_renderer_camera(camera c)
{
	if(c == NULL)
	{
		LOG_ERROR("Camera cannot be NULL");
		return;
	}

	text_camera = c;
}

void set_text_renderer_color(color_rgba rgba)
{
	color_set_rgba(&text_color, rgba);
}

void set_text_renderer_char_space_size(float space)
{
	char_space_size = space;
}


void set_text_renderer_text_size(float size)
{
	text_size = size;
}
