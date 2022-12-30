#include "camera.h"
#include <stdlib.h>
#include "vec3.h"
#include "ray.h"

camera_s *camera_new_base(camera_s in) {
    camera_s *out = malloc(sizeof(camera_s));
    *out = in;
    out->origin = (vec3_s) {.e = {0.0, 0.0, 0.0}};
    out->horz =   (vec3_s) {.e = {out->viewport_w, 0.0, 0.0}};
    out->vert  =  (vec3_s) {.e = {0.0, out->viewport_h, 0.0}};
    out->low_left  = out->origin;
    this_sub_vec(&out->low_left, vec_div_c(out->horz, 2));
    this_sub_vec(&out->low_left, vec_div_c(out->vert, 2));
    this_sub_vec(&out->low_left, (vec3_s) {.e = {0.0, 0.0, out->focal_l}});
    return out;
}


void camera_delete(camera_s in) {
    // TODO
}


ray_s get_ray(camera_s *cam, const double u, const double v) {
    vec3_s dir = vec_sum(cam->low_left,
                         vec_mult_c(cam->horz, u),
                         vec_mult_c(cam->vert, v),
                         vec_neg(cam->origin));

    return (ray_s) {.orig = &cam->origin, .dir = &dir};
}
