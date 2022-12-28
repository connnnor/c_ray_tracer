#ifndef RAY_H
#define RAY_H

#include "vec3.h"

//#define ray_new(...) ray_new_base((ray_s){.orig = {0.0, 0.0, 0.0}, .dir = {0.0, 0.0, 0.0}, __VA_ARGS__})

typedef struct {
    vec3_s *orig;
    vec3_s *dir;
} ray_s;

ray_s *ray_new_base(ray_s in);

point_s *point_at(const ray_s *this, const double t);
vec3_s ray_orig(ray_s *this);
vec3_s ray_dir(ray_s *this);

#endif
