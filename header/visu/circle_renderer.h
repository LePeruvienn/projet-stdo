#ifndef CIRCLE_RENDERER_H
#define CIRCLE_RENDERER_H

#include "visu/camera.h"

void init_circle_renderer();

void circle_begin_draw();

void circle_draw(float x, float y);

void circle_end_draw(camera c);

void free_circle_renderer();

#endif // CIRCLE_RENDERER_H
