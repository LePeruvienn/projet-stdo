#ifndef RENDERER_H
#define RENDERER_H

#include "visu/camera.h"

#include "tsp/file.h"

void init_renderer();

void set_renderer_camera(camera c);

void render();

void free_renderer();

#endif // RENDERER_H
