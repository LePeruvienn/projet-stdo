#include "visu/text_renderer.h"
#include "visu/texture.h"
#include "visu/geometry.h"
#include "visu/shader.h"
#include "visu/color.h"

#include "utils/logger.h"
#include "utils/debug.h"
#include "utils/ptr.h"

#include <stdlib.h>
#include <stdbool.h>

#define BITMAP_PATH "asset/bitmap/kenpixel.png"

static texture bitmap_texture = NULL;
static geometry text_geo = NULL;
static shader text_shader = NULL;


static color text_color = (color) { .rgba = {255, 255, 0, 0 },
                                    .norm = {1.f, 1.f, 0, 0 } };

static bool is_intialized = false;

void init_text_renderer()
{
	if(is_intialized)
	{
		LOG_ERROR("Already intialized !");
		return;
	}

	bitmap_texture = create_texture(BITMAP_PATH);
	text_geo = create_quad_geometry();
	text_shader = create_shader("asset/shader/text.vert", "asset/shader/text.frag");

	CHECK_IS_NULL(bitmap_texture, "Failed to load bitmap texture.");
	CHECK_IS_NULL(text_geo, "Failed to load text geometry");
	CHECK_IS_NULL(text_shader, "Failed to load text shader");

	is_intialized = true;
}

// void draw_text(const char* text)
void draw_text()
{
	if(is_intialized == false)
	{
		LOG_ERROR("Cannot draw text if renderer not init");
		return;
	}

	bind_shader(text_shader);

	GLint texture_unit = 0;

	bind_texture(bitmap_texture, texture_unit);
	set_shader_texture_unit(text_shader, texture_unit);
	set_shader_text_color(text_shader, text_color);

	bind_geometry(text_geo);

	draw_geometry(text_geo);

	unbind_geometry(text_geo);
	unbind_texture(bitmap_texture);
	unbind_shader();
}

void free_text_renderer()
{
	FREE_PTR_NOT_NULL(text_shader, free_shader);
	FREE_PTR_NOT_NULL(bitmap_texture, free_texture);
	FREE_PTR_NOT_NULL(text_geo, free_geometry);
}
