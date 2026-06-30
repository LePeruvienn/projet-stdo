#ifndef RENDERER_H
#define RENDERER_H

#include "visu/camera.h"

#include "tsp/instance.h"
#include "tsp/section_datas.h"

void init_renderer();

void set_renderer_camera(camera c);

void render(TSP_Instance instance);

void free_renderer();

bool renderer_get_is_intialized();

TSP_Node_Coord* node_picking(TSP_Instance instance, float sx, float sy);


#endif // RENDERER_H
