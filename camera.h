#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "ray.h"

typedef double degrees;

#define camera_new(...) camera_new_base((camera_s) \
                   {.v_fov        = V_FOV_DEG, \
                   .aspect_ratio  = ASPECT_RATIO_N / ASPECT_RATIO_D, \
                   .look_from     = (vec3_s) {-1.0, 1.0, 1.0}, \
                   .look_at       = (vec3_s) {0.0, 0.0, 0.0}, \
                   .view_up       = (vec3_s) {0.0, 1.0, 0.0}, \
                   __VA_ARGS__}) 


typedef struct camera_s {
    point_s look_from;
    point_s look_at;
    vec3_s view_up;

    degrees v_fov;
    double aspect_ratio;

    vec3_s origin;
    vec3_s horz;
    vec3_s vert;
    vec3_s low_left;
} camera_s;

camera_s *camera_new_base(camera_s in);
void camera_delete(camera_s in);
ray_s get_ray(camera_s *cam, const double u, const double v);

#endif
