#ifndef NODE_RENDERER_H
#define NODE_RENDERER_H

#include "visu/camera.h"

void init_node_renderer();

void node_begin_draw();

void node_draw(float x, float y);

void node_end_draw(camera c);

void free_node_renderer();

#endif // NODE_RENDERER_H
