#include <stdlib.h> //getenv, atoi
#include <stdio.h>
#include <math.h>
#include "vec3.h"
#include "camera.h"
#include "ray.h"
#include "rt_utils.h"
#include "hittable.h"
#include "material.h"

#define IMG_WIDTH  800
#define V_FOV_DEG      90.0
#define ASPECT_RATIO_N 3.0
#define ASPECT_RATIO_D 2.0
#define SAMPLES_PER_PIXEL 50  // Range 1 - 100
#define MAX_CHILD_RAYS  30     // Range 2 -  50
#define WORLD_NUM_OBJS  169   // make it something x^2

void write_ppm_header(FILE *stream, const int width, const int height) {
    fprintf(stream, "P3\n" "%d\t%d\n" "255\n", width, height);
}

void write_ppm_color(FILE *stream, const color_s *in, int samples_per_pixel) {
    double scale = 1.0 / (samples_per_pixel + 0.0);
    // divide color by num samples
    vec3_s c = vec_mult_c(*in, scale);

    // remap values from [0.0, 1.0] to [0, 255]
    int ir = (256 * clamp(sqrt(c.e[0]), 0.0, 0.999));
    int ig = (256 * clamp(sqrt(c.e[1]), 0.0, 0.999));
    int ib = (256 * clamp(sqrt(c.e[2]), 0.0, 0.999));
    fprintf(stream, "%d %d %d\n", ir, ig, ib);
}

color_s ray_color(const ray_s *r, const list_obj_s *world, int depth) {
    if (depth <= 0) { return (color_s) {.e = 0.0, 0.0, 0.0}; }
    hit_s *hit = list_hit(r, 0.001, INFINITY, world->parent);
    if (hit != NULL) {
        ray_s *scatter = hit->mat->scatter_fp(r, hit, hit->mat);
        color_s color_out = (color_s) {.e = 0.0, 0.0, 0.0};
        if (scatter != NULL) {
            color_s attenu = hit->mat->c;
            color_out = vec_mult_vec(attenu, ray_color(scatter, world, depth - 1));
            free(scatter);
        }
        free(hit);
        return color_out;
    }
    vec3_s unit = vec_unit_vec(r->dir);
    double t = 0.5 * (unit.e[1] + 1.0);
    return vec_add_vec(vec_mult_c((vec3_s) {.e = {1.0, 1.0, 1.0}}, 1.0 - t),  vec_mult_c((vec3_s) {.e = {0.5, 0.7, 1.0}}, t));
} 

color_s from_rgb(unsigned char r, unsigned char g, unsigned char b) {
    return (color_s) {.e = (r+0.0) / 255.0, (g+0.0) / 255.0, (b+0.0) / 255.0};
}

list_obj_s *rand_world(int num_objs) {
    list_obj_s *world = list_new();

    material_s *ground_mat = lambert_new((color_s) {.e = {0.5, 0.5, 0.5}});
    obj_s *ground = sphere_new((point_s) {.e = { 0.0, -1000.0, 0.0}}, 1000.0, ground_mat);
    list_add(world, ground);

    int sqrt_n = sqrt(num_objs);

    for (int a = -sqrt_n; a < sqrt_n; a++) {
        for (int b = -sqrt_n; b < sqrt_n; b++) {
            point_s center = {.e = {a + 0.9 * rand_double(),
                                    0.2, 
                                    b + 0.9 * rand_double()}};
            double mat_choice = rand_double();
            material_s *mat;
            if (mat_choice < 0.66) {
                mat = lambert_new(rand_color());
            } else {
                mat = metal_new(rand_color());
            }
            obj_s *obj = sphere_new(center, 0.2 + rand_double_in(0.0, 0.1), mat);
            list_add(world, obj);
        }
    }

    return world;
}

int main() {
    // Image
    const double aspect_ratio = ASPECT_RATIO_N / ASPECT_RATIO_D;
    const int img_w = IMG_WIDTH;
    const int img_h = (img_w+0.0) / aspect_ratio;
    fprintf(stderr, "width=%d\n" "height=%d\n", img_w, img_h);

    // World
    list_obj_s *world = rand_world(WORLD_NUM_OBJS);

    // Camera
    camera_s *cam = camera_new(.look_from = (vec3_s) { 9.0,  1.5,  2.0},
                               .look_at   = (vec3_s) { 0.0, -3.5,  1.0});

    // Render
    write_ppm_header(stdout, img_w, img_h);
    for (int i = img_h - 1; i >= 0; --i) {
        for (int j = 0; j < img_w; ++j) {
            color_s pixel_color = (vec3_s) {.e = 0.0, 0.0, 0.0};
            for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
                double u = (j+rand_double()) / (img_w-1);
                double v = (i+rand_double()) / (img_h-1);
                ray_s r = get_ray(cam, u, v);
                this_add_vec(&pixel_color, ray_color(&r, world, MAX_CHILD_RAYS));
            }
            write_ppm_color(stdout, &pixel_color, SAMPLES_PER_PIXEL);
        }
        fprintf(stderr, "\rScalines remaining %04d", i);
    }

    // Free
    list_delete(world);
}

