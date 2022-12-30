#ifndef CAMERA_H
#define CAMERA_H
#include "vec3.h"
#include "ray.h"

#define camera_new(...) camera_new_base((camera_s) \
                   {.aspect_ratio  = ASPECT_RATIO_N / ASPECT_RATIO_D, \
                   .viewport_h     = VIEWPORT_H, \
                   .viewport_w     = ASPECT_RATIO_N / ASPECT_RATIO_D * VIEWPORT_H , \
                   .focal_l        = FOCAL_LEN, __VA_ARGS__}) 
///                {.aspect_ratio  = 16.0 / 9.0, \
///                .viewport_h     = 2.0, \
///                .focal_l        = 1.0, __VA_ARGS__}) 



typedef struct camera_s {
    double aspect_ratio;
    double viewport_h;
    double viewport_w;
    double focal_l;

    vec3_s origin;
    vec3_s horz;
    vec3_s vert;
    vec3_s low_left;
} camera_s;


camera_s *camera_new_base(camera_s in);
void camera_delete(camera_s in);
ray_s get_ray(camera_s *cam, const double u, const double v);

#endif
