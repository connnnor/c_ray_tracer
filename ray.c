#include "ray.h"
#include <stdlib.h>

ray_s *ray_new_base(ray_s in) {
    ray_s *out = malloc(sizeof(ray_s));
    (*out).orig = vec3_new_base(*(in.orig));
    (*out).dir = vec3_new_base(*(in.dir));
    return out;
}

void ray_delete(ray_s *in) {
	vec_delete(in->orig);
	vec_delete(in->dir);
	free(in);
}

point_s point_at(const ray_s *this, const double t) {
    point_s out = *(this->dir);
    this_mult_c(&out, t);
    this_add_vec(&out, *this->orig);
    return out;
}
