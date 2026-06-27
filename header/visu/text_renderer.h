#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "visu/camera.h"
#include "visu/color.h"

void init_text_renderer();

void text_begin_draw();

void draw_char(char c, float x, float y);

void text_end_draw();

void free_text_renderer();

void set_text_renderer_camera(camera c);

void set_text_renderer_color(color_rgba rgba);

#endif // TEXT_RENDERER_H
