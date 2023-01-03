#include <stdlib.h> //getenv, atoi
#include <stdio.h>
#include <math.h>
#include "vec3.h"
#include "camera.h"
#include "ray.h"
#include "rt_utils.h"
#include "hittable.h"
#include "material.h"

#define IMG_WIDTH  1200
#define V_FOV_DEG      30.0
#define ASPECT_RATIO_N 16.0
#define ASPECT_RATIO_D 9.0
#define SAMPLES_PER_PIXEL  100 // Range 1 - 100
#define MAX_CHILD_RAYS 50     // Range 1 -  50

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

int main() {
    // Image
    const double aspect_ratio = ASPECT_RATIO_N / ASPECT_RATIO_D;
    const int img_w = IMG_WIDTH;
    const int img_h = (img_w+0.0) / aspect_ratio;
    fprintf(stderr, "width=%d\n" "height=%d\n", img_w, img_h);

    // World
    list_obj_s *world = list_new();

    material_s *lambert_ground = lambert_new(from_rgb(215, 169, 227));
    material_s *metal_center =    metal_new(from_rgb(74, 201, 227));
    material_s *lambert_left   = lambert_new(from_rgb(244, 175, 35));
    material_s *lambert_right  = lambert_new(from_rgb(137, 12, 88));

    obj_s *objs[] = {
        sphere_new((point_s) {.e = { 0.0, -100.5, -1.0}}, 100.0, lambert_ground),
        sphere_new((point_s) {.e = { 0.0,    0.0, -1.0}}, 0.5,   metal_center),
        sphere_new((point_s) {.e = {-1.0,    0.0, -1.0}}, 0.5,   lambert_left),
        sphere_new((point_s) {.e = { 1.0,    0.0, -1.0}}, 0.5,   lambert_right),
        NULL
    };
    // add objs to world
    for (obj_s **obj = objs; *obj; obj++) { list_add(world, *obj); }
    //list_add(world, right_sphere);

    // Camera
//  camera_s *cam = camera_new(.look_from = (vec3_s) {-2.0,  2.0,  1.0},
//                             .look_at   = (vec3_s) { 0.0,  0.0, -1.0});

    // Render loop (changing camera viewpoint)
//  fprintf(stderr, "fmod(180.0, 360) = %f\n", fmod(180.0, 360));
//  fprintf(stderr, "fmod(359.0, 360) = %f\n", fmod(359.0, 360));
//  fprintf(stderr, "fmod(361.0, 360) = %f\n", fmod(361.0, 360));
//  fprintf(stderr, "fmod(719.0, 360) = %f\n", fmod(719.0, 360));
//  fprintf(stderr, "fmod(722.0, 360) = %f\n", fmod(722.0, 360));
//
    //vec3_s look_from = (vec3_s) { .e = {0.0,  0.0,  1.0}};
    vec3_s look_from = (vec3_s) { .e = {2.0,  1.0,  1.0}};
    vec3_s look_at   = (vec3_s) { .e = {0.0,  0.0, -1.0}};
    double deg_per_frame = 3.0;
    double cur_deg = 0.0;
//  while(cur_deg < 361.0) {
        // X & Y positions will go along circle
        //look_from = (vec3_s) { .e = { 2.0 * cos_deg(cur_deg), 2.0, 2.0 * sin_deg(cur_deg)}};
        //cur_deg = fmod(cur_deg, 360);
        cur_deg += deg_per_frame;

        camera_s *cam = camera_new(.look_from = look_from, .look_at   = look_at);
        //printf("P3\n" "%d\t%d\n" "255\n", img_w, img_h);
        write_ppm_header(stdout, img_w, img_h);
        for (int i = img_h - 1; i >= 0; --i) {
            for (int j = 0; j < img_w; ++j) {
                color_s pixel_color = (vec3_s) {.e = 0.0, 0.0, 0.0};
                for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
                    double u = (j+rand_double()) / (img_w-1);
                    double v = (i+rand_double()) / (img_h-1);
                    ray_s r = get_ray(cam, u, v);
                    //vec3_s pixel_rgb = ray_color(&r, world);
                    this_add_vec(&pixel_color, ray_color(&r, world, MAX_CHILD_RAYS));
                }
                write_ppm_color(stdout, &pixel_color, SAMPLES_PER_PIXEL);
            }
            fprintf(stderr, "\rScalines remaining %04d", i);
        }
        fprintf(stderr, "\rProgress %.2f", cur_deg / 361.0);
//  }
//  fprintf(stderr, "\n");

//  write_ppm_header(stdout, img_w, img_h);
//  for (int i = img_h - 1; i >= 0; --i) {
//      for (int j = 0; j < img_w; ++j) {
//          color_s pixel_color = (vec3_s) {.e = 0.0, 0.0, 0.0};
//          for (int s = 0; s < SAMPLES_PER_PIXEL; ++s) {
//              double u = (j+rand_double()) / (img_w-1);
//              double v = (i+rand_double()) / (img_h-1);
//              ray_s r = get_ray(cam, u, v);
//              //vec3_s pixel_rgb = ray_color(&r, world);
//              this_add_vec(&pixel_color, ray_color(&r, world, MAX_CHILD_RAYS));
//          }
//          write_ppm_color(stdout, &pixel_color, SAMPLES_PER_PIXEL);
//      }
//  }

	// Free
    //material_delete_all(lambert_ground, lambert_center, lambert_left, lambert_right);
    //sphere_delete_all();
//  sphere_delete(sphere1);
//  sphere_delete(sphere1);
//  sphere_delete(left_sphere);
//  sphere_delete(right_sphere);
	list_delete(world);
}

