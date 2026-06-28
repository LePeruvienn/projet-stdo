#include "visu/camera.h"

#include <stdlib.h>

#define ZOOM_MIN 0.5f
#define ZOOM_MAX 1000000.f

struct camera
{
	float x, y;
	float zoom;
	float aspect;
};

static void camera_zoom_cap(camera c)
{
	if (c->zoom > ZOOM_MAX)
	{
		c->zoom = ZOOM_MAX;
	}
	else if (c->zoom < ZOOM_MIN)
	{
		c->zoom = ZOOM_MIN;
	}
}

camera create_camera(float x, float y, float zoom, float aspect)
{
	camera c = malloc(sizeof(struct camera));

	c->x = x;
	c->y = y;

	c->zoom = zoom;
	c->aspect = aspect;

	return c;
}

void free_camera(camera c)
{
	free(c);
}

float get_camera_pos_x(camera c)
{
	return c->x;
}

float get_camera_pos_y(camera c)
{
	return c->y;
}

float get_camera_zoom(camera c)
{
	return c->zoom;
}

float get_camera_aspect(camera c)
{
	return c->aspect;
}

void set_camera_pos(camera c, float x, float y)
{
	c->x = x;
	c->x = y;
}
	
void set_camera_zoom(camera c, float zoom)
{
	c->zoom = zoom;
	camera_zoom_cap(c);
}
void set_camera_aspect(camera c, float aspect)
{
	c->aspect = aspect;
}


void camera_move(camera c, float dx, float dy, float dzoom)
{
	c->x += dx;
	c->y += dy;

	c->zoom += dzoom;
	
	camera_zoom_cap(c);
}

