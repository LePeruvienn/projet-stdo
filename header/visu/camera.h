#ifndef CAMERA_H
#define CAMERA_H

#include "glad/glad.h"

typedef struct camera* camera;

camera create_camera(float x, float y, float zoom, float aspect);

void free_camera(camera c);

float get_camera_pos_x(camera c);
float get_camera_pos_y(camera c);
float get_camera_zoom(camera c);
float get_camera_aspect(camera c);

void set_camera_pos(camera c, float x, float y);
void set_camera_zoom(camera c, float zoom);
void set_camera_aspect(camera c, float aspect);

void camera_move(camera c, float dx, float dy, float dzoom);

#endif // CAMERA_H
