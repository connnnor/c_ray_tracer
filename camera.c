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

    // camera view orientation
    vec3_s w = vec_unit_vec(vec_sub_vec(out->look_from, out->look_at));
    vec3_s u = vec_unit_vec(vec_cross(out->view_up, w));
    vec3_s v = vec_cross(w, u);
    
    out->origin = out->look_from;
    out->horz =   vec_mult_c(u, viewport_wd);
    out->vert  =  vec_mult_c(v, viewport_ht);
    out->low_left = vec_sum(out->origin,
                         vec_mult_c(out->horz, -0.5),
                         vec_mult_c(out->vert, -0.5),
                         vec_neg(w));
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
