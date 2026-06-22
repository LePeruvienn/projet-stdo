#ifndef EDGE_RENDERER_H
#define EDGE_RENDERER_H

#include "visu/camera.h"

void init_edge_renderer();

void edge_begin_draw();

void edge_draw(float x1, float y1, float x2, float y2);

void edge_end_draw(camera c);

void free_edge_renderer();

#endif // EDGE_RENDERER_H
