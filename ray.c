#include "ray.h"
#include <stdlib.h>

ray_s *ray_new_base(ray_s in) {
    ray_s *out = malloc(sizeof(ray_s));
    (*out).orig = vec3_new_base(*(in.orig));
    (*out).dir = vec3_new_base(*(in.dir));
    return out;
}

vec3_s point_at(double t) {

}
