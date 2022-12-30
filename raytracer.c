#include <stdlib.h> //getenv, atoi
#include <stdio.h>
#include <math.h>
#include "vec3.h"
#include "camera.h"
#include "ray.h"
#include "rt_utils.h"
#include "hittable.h"

#define IMG_WIDTH  400
//#define IMG_HEIGHT 256

#define ASPECT_RATIO_N 16.0
#define ASPECT_RATIO_D 9.0
#define VIEWPORT_H 2.0
#define FOCAL_LEN  1.0
#define SAMPLES_PER_PIXEL  100

void write_color(FILE *stream, const color_s *in, int samples_per_pixel) {
    double scale = 1.0 / (samples_per_pixel + 0.0);
    // divide color by num samples
    vec3_s c = vec_mult_c(*in, scale);

    // remap values from [0.0, 1.0] to [0, 255]
    int ir = (256 * clamp(c.e[0], 0.0, 0.999));
    int ig = (256 * clamp(c.e[1], 0.0, 0.999));
    int ib = (256 * clamp(c.e[2], 0.0, 0.999));
    fprintf(stream, "%d %d %d\n", ir, ig, ib);
}

color_s ray_color(const ray_s *r, const list_obj_s *world) {
	hit_s *hit = list_hit(r, 0.0, INFINITY, world->parent);
	if (hit != NULL) {
		color_s out = vec_mult_c(vec_add_vec(hit->norm, (color_s) {.e = {1.0, 1.0, 1.0}}), 0.5);
		free(hit);
		return out;
	}
    vec3_s unit = vec_unit_vec(*(r->dir));
    double t = 0.5 * (unit.e[1] + 1.0);
    return vec_add_vec(vec_mult_c((vec3_s) {.e = {1.0, 1.0, 1.0}}, 1.0 - t),  vec_mult_c((vec3_s) {.e = {0.5, 0.7, 1.0}}, t));
} 

int main() {
    // Image
    const double aspect_ratio = ASPECT_RATIO_N / ASPECT_RATIO_D;
    const int img_w = IMG_WIDTH;
    const int img_h = (img_w+0.0) / aspect_ratio;
    fprintf(stderr, "width=%d\n" "height=%d\n", img_w, img_h);

    // World
    list_obj_s *world = list_new();
    obj_s *sphere1 = sphere_new((point_s) {.e = {0.0, 0.0, -1.0}}, 0.5);
    obj_s *sphere2 = sphere_new((point_s) {.e = {0.0, -100.5, -1.0}}, 100.0);
    list_add(world, sphere1);
    list_add(world, sphere2);

    // Camera
    camera_s *cam = camera_new();

    // Render

    printf("P3\n" "%d\t%d\n" "255\n", img_w, img_h);
    for (int i = img_h - 1; i >= 0; --i) {
        for (int j = 0; j < img_w; ++j) {
            color_s pixel_color = (vec3_s) {.e = 0.0, 0.0, 0.0};
            for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
                double u = (j+rand_double()) / (img_w-1);
                double v = (i+rand_double()) / (img_h-1);
                ray_s r = get_ray(cam, u, v);
                //vec3_s pixel_rgb = ray_color(&r, world);
                this_add_vec(&pixel_color, ray_color(&r, world));
            }
            write_color(stdout, &pixel_color, SAMPLES_PER_PIXEL);
        }
    }

	// Free
	sphere_delete(sphere1);
	sphere_delete(sphere2);
	list_delete(world);
}
