#include "visu/color.h"

static color_norm get_clamped_norm(color_norm norm)
{
	if (norm.r > 1.f) norm.r = 1.f;
	if (norm.r < 0.f) norm.r = 0.f;

	if (norm.g > 1.f) norm.g = 1.f;
	if (norm.g < 0.f) norm.g = 0.f;

	if (norm.b > 1.f) norm.b = 1.f;
	if (norm.b < 0.f) norm.b = 0.f;

	if (norm.a > 1.f) norm.a = 1.f;
	if (norm.a < 0.f) norm.a = 0.f;

	return norm;
}


static color_norm get_norm_from_rgba(color_rgba* c)
{
	return (color_norm)
	{
		(float) c->r / 255.f,
		(float) c->g / 255.f,
		(float) c->b / 255.f,
		(float) c->a / 255.f
	};
}

static color_rgba get_rgba_from_norm(color_norm* norm)
{
	color_norm c = get_clamped_norm(*norm);

	return (color_rgba)
	{
		(unsigned char) (c.r * 255.f),
		(unsigned char) (c.g * 255.f),
		(unsigned char) (c.b * 255.f),
		(unsigned char) (c.a * 255.f)
	};
}

color create_color_rgba(color_rgba rgba)
{
	color_norm norm = get_norm_from_rgba(&rgba);
	
	return (color) { rgba, norm };
}

color create_color_norm(color_norm norm)
{
	color_rgba rgba = get_rgba_from_norm(&norm);

	return (color) { rgba, norm };
}

void color_set_rgba(color* c, color_rgba rgba)
{
	c->rgba = rgba;
	c->norm = get_norm_from_rgba(&c->rgba);
}

void color_set_norm(color* c, color_norm norm)
{
	c->norm = norm;

	c->rgba = get_rgba_from_norm(&c->norm);
}

