#include "ray.h"
#include <stdlib.h>

ray_s *ray_new_base(ray_s in) {
    ray_s *out = malloc(sizeof(ray_s));
    (*out).orig = vec3_new_base(*(in.orig));
    (*out).dir = vec3_new_base(*(in.dir));
    return out;
}

point_s *point_at(const ray_s *this, const double t) {
    return this_add_vec(vec_mult_c(this->dir, t), this->orig);
}
