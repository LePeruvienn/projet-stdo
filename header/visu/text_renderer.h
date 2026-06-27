#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include "visu/camera.h"
#include "visu/color.h"

void init_text_renderer();

// void draw_text(const char* text);
void draw_text();

void free_text_renderer();

void set_text_renderer_camera(camera c);

void set_text_renderer_color(color_rgba rgba);

#endif // TEXT_RENDERER_H
