#include <stdlib.h> //getenv, atoi
#include <stdio.h>
#include <stdbool.h>
#include "vec3.h"
#include "ray.h"

#define IMG_WIDTH  256
#define IMG_HEIGHT 256

bool hit_sphere(const point_s *center, const double radius, const ray_s *r) {
    vec3_s *oc = vec_sub_vec(r->orig, center);

    double a = dot(r->dir, r->dir);
    double b = 2.0 * dot(oc, r->dir);
    double c = dot(oc, oc) - radius * radius;
    double discr = b*b - 4*a*c;

    vec_delete(oc);
    return (discr > 0);
}

void write_color(const color_s *in) {
    int ir = (255.999 * in->e[0]);
    int ig = (255.999 * in->e[1]);
    int ib = (255.999 * in->e[2]);
    printf("%d %d %d\n", ir, ig, ib);
}

color_s *ray_color(const ray_s *r) {
    if (hit_sphere(vec3_new(.e = {0.0, 0.0, -1.0}), 0.5, r)) {
        return vec3_new(.e = {1.0, 0.0, 0.0});
    }
    vec3_s *unit = vec_unit_vec(r->dir);
    double t = 0.5 * ((*unit).e[1] + 1.0);
    return vec_add_vec(this_mult_c(vec3_new(.e = {1.0, 1.0, 1.0}), 1.0 - t),  this_mult_c(vec3_new(.e = {0.5, 0.7, 1.0}), t));
} 

int main() {
    // Image
    const double aspect_ratio = 16.0 / 9.0;
    const int img_w = 400;
    const int img_h = (img_w+0.0) / aspect_ratio;
    fprintf(stderr, "aspectratio=%f\n" "width=%d\n" "height=%d\n", aspect_ratio, img_w, img_h);

    // Camera
    double viewport_h = 2.0;
    double viewport_w = aspect_ratio * viewport_h;
    double focal_l = 1.0;

    vec3_s *origin = vec3_new();
    vec3_s *horz = vec3_new(.e = {viewport_w, 0.0, 0.0});
    vec3_s *vert  = vec3_new(.e = {0.0, viewport_h, 0.0});
    vec3_s *low_left  = vec3_new();
    this_sub_vec(low_left, vec_div_c(horz, 2));
    this_sub_vec(low_left, vec_div_c(vert, 2));
    this_sub_vec(low_left, vec3_new(.e = {0.0, 0.0, focal_l}));

    // Render

    printf("P3\n" "%d\t%d\n" "255\n", img_w, img_h);
    for (int i = img_h - 1; i >= 0; --i) {
        for (int j = 0; j < img_w; ++j) {
            double u = (j+0.0) / (img_w-1);
            double v = (i+0.0) / (img_h-1);
//          fprintf(stderr, "u=%f v=%f\n", u, v);


//          vec3_s *pixel_rgb = vec3_new(.e = {r, g, b});

            vec3_s *dir = vec_add_c(low_left, 0.0);
            this_add_vec(dir, vec_mult_c(horz, u));
            this_add_vec(dir, vec_mult_c(vert, v));
            this_sub_vec(dir, origin);
//
            ray_s *r = ray_new_base((ray_s) {.orig = origin, .dir = dir});
            vec3_s *pixel_rgb = ray_color(r);
            write_color(pixel_rgb);
            vec_delete(pixel_rgb);
        }
    }

//  vec3_s *v1 = vec3_new(.e = {0.0, 1.0, 2.0});
//  vec3_s *v2 = vec3_new(.e = {0.5, 0.6, 0.9});
//  printf("before this_add_vecs(). v1: "); vec3_print(v1);
//  printf("before this_add_vecs(). v2: "); vec3_print(v2);
//  vec3_s *res = vec_add_vec(v1, v2);
//  printf("after this_add_vecs(). v1: "); vec3_print(v1);
//  printf("after this_add_vecs(). v2: "); vec3_print(v2);
//  printf("after this_add_vecs(). res: "); vec3_print(res);
}