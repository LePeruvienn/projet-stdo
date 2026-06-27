#ifndef LINE_RENDERER_H
#define LINE_RENDERER_H

#include "visu/camera.h"
#include "visu/color.h"

void init_line_renderer();

void line_begin_draw();

void line_draw(float x1, float y1, float x2, float y2);

void line_end_draw();

void free_line_renderer();

void set_line_renderer_camera(camera c);
void set_line_renderer_color(color_rgba rgba);
void set_line_renderer_thickness(float t);

#endif // LINE_RENDERER_H
