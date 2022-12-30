#include <stdlib.h> //getenv, atoi
#include <stdio.h>
#include <math.h>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

#define IMG_WIDTH  256
#define IMG_HEIGHT 256

void write_color(const color_s *in) {
    int ir = (255.999 * in->e[0]);
    int ig = (255.999 * in->e[1]);
    int ib = (255.999 * in->e[2]);
    printf("%d %d %d\n", ir, ig, ib);
}

color_s ray_color(const ray_s *r, const list_obj_s *world) {
	hit_s *hit = list_hit(r, 0.0, INFINITY, world->parent);
	if (hit != NULL) {
		return vec_mult_c(vec_add_vec(hit->norm, (color_s) {.e = {1.0, 1.0, 1.0}}), 0.5);
	}
    vec3_s unit = vec_unit_vec(*(r->dir));
    double t = 0.5 * (unit.e[1] + 1.0);
    return vec_add_vec(vec_mult_c((vec3_s) {.e = {1.0, 1.0, 1.0}}, 1.0 - t),  vec_mult_c((vec3_s) {.e = {0.5, 0.7, 1.0}}, t));
} 

int main() {
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int img_w = 400;
    const int img_h = (img_w+0.0) / aspect_ratio;
    fprintf(stderr, "aspectratio=%f\n" "width=%d\n" "height=%d\n", aspect_ratio, img_w, img_h);

    // World
    list_obj_s *world = list_new();
    obj_s *sphere1 = sphere_new((point_s) {.e = {0.0, 0.0, -1.0}}, 0.5);
    obj_s *sphere2 = sphere_new((point_s) {.e = {0.0, -100.5, -1.0}}, 100.0);
    list_add(world, sphere1);
    list_add(world, sphere2);

    // Camera
    double viewport_h = 2.0;
    double viewport_w = aspect_ratio * viewport_h;
    double focal_l = 1.0;

    vec3_s origin = {.e = {0.0, 0.0, 0.0}};
    vec3_s horz = {.e = {viewport_w, 0.0, 0.0}};
    vec3_s vert  = {.e = {0.0, viewport_h, 0.0}};
    
    vec3_s low_left  = origin;
    this_sub_vec(&low_left, vec_div_c(horz, 2));
    this_sub_vec(&low_left, vec_div_c(vert, 2));
    this_sub_vec(&low_left, (vec3_s) {.e = {0.0, 0.0, focal_l}});

    // Render

    printf("P3\n" "%d\t%d\n" "255\n", img_w, img_h);
    for (int i = img_h - 1; i >= 0; --i) {
        for (int j = 0; j < img_w; ++j) {
            double u = (j+0.0) / (img_w-1);
            double v = (i+0.0) / (img_h-1);
            vec3_s dir = vec_sum(low_left,
                                 vec_mult_c(horz, u),
                                 vec_mult_c(vert, v),
                                 vec_neg(origin));

            ray_s r = {.orig = &origin, .dir = &dir};
            vec3_s pixel_rgb = ray_color(&r, world);
	    // for debug
	    //list_hit(&r, 0.5, 10.0, world);
	    // end debug
            write_color(&pixel_rgb);
        }
    }
}
