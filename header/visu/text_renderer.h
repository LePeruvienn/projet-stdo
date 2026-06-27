#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "visu/camera.h"
#include "visu/color.h"

void init_text_renderer();

void text_begin_draw();

void draw_char(char c, float x, float y);
void draw_text(const char* text, float x, float y);

void text_end_draw();

void free_text_renderer();

void set_text_renderer_camera(camera c);

void set_text_renderer_color(color_rgba rgba);

void set_text_renderer_char_space_size(float space);

void set_text_renderer_text_size(float size);

#endif // TEXT_RENDERER_H
