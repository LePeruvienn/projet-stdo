#ifndef CIRCLE_RENDERER_H
#define CIRCLE_RENDERER_H

#include "visu/camera.h"
#include "visu/color.h"

void init_circle_renderer();

void circle_begin_draw();

void circle_draw(float x, float y);

void circle_end_draw();

void free_circle_renderer();

void set_circle_renderer_camera(camera c);

void set_circle_renderer_fill_color(color_rgba c);
void set_circle_renderer_border_color(color_rgba c);

void set_circle_renderer_radius(float r);
void set_circle_renderer_border_thickness(float t);

#endif // CIRCLE_RENDERER_H
