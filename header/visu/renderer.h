#ifndef RENDERER_H
#define RENDERER_H

#include "visu/camera.h"

#include "tsp/instance.h"

void init_renderer();

void set_renderer_camera(camera c);

void render(TSP_Instance instance);

void free_renderer();

#endif // RENDERER_H
