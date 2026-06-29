#ifndef GRID_RENDERER_H
#define GRID_RENDERER_H

#include "visu/camera.h"
#include "visu/color.h"

void init_grid_renderer();

void draw_grid();

void free_grid_renderer();

void set_grid_renderer_camera(camera c);

void set_grid_renderer_bg_color(color_rgba rgba);
void set_grid_renderer_line_color(color_rgba rgba);

void set_grid_renderer_grid_size(float size);

void add_grid_renderer_grid_size(float size);

#endif // GRID_RENDERER_H
