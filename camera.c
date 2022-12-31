#include "camera.h"
#include <stdlib.h>
#include "vec3.h"
#include "ray.h"
#include <math.h>
#include "rt_utils.h"

camera_s *camera_new_base(camera_s in) {
    camera_s *out = malloc(sizeof(camera_s));
    *out = in;
    double theta = deg_to_rad(out->v_fov);
    double h = tan(theta / 2.0);
    double viewport_ht = 2.0 * h;
    double viewport_wd = out->aspect_ratio * viewport_ht;
    double focal_len = 1.0;
    
    out->origin = (vec3_s) {.e = {0.0, 0.0, 0.0}};
    out->horz =   (vec3_s) {.e = {viewport_wd, 0.0, 0.0}};
    out->vert  =  (vec3_s) {.e = {0.0, viewport_ht, 0.0}};
    out->low_left  = out->origin;
    this_sub_vec(&out->low_left, vec_div_c(out->horz, 2));
    this_sub_vec(&out->low_left, vec_div_c(out->vert, 2));
    this_sub_vec(&out->low_left, (vec3_s) {.e = {0.0, 0.0, focal_len}});
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

    return (ray_s) {.orig = cam->origin, .dir = dir};
}
