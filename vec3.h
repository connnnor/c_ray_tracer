#ifndef VEC3_H
#define VEC3_H
#include <math.h>

#define vec3_new(...) vec3_new_base((vec3_s){.e = {0.0, 0.0, 0.0}, __VA_ARGS__})


typedef struct {
    double e[3];
} vec3_s;

typedef vec3_s color_s;
typedef vec3_s point_s;

vec3_s vec_rand();
vec3_s vec_rand_in(const double min, const double max);
vec3_s vec_rand_in_unit_sphere();

vec3_s *vec3_new_base(vec3_s in);
void vec_delete(vec3_s *in);

vec3_s *this_add_vec(vec3_s *this, const vec3_s v);
vec3_s vec_add_vec(const vec3_s u, const vec3_s v);
vec3_s *this_add_c(vec3_s *v, const double c);
vec3_s vec_add_c(const vec3_s v, const double c);

vec3_s vec_sub_vec(const vec3_s u, const vec3_s v);
vec3_s *this_sub_vec(vec3_s *this, const vec3_s v);
vec3_s *vec_sub_c(const vec3_s *u, double c);

vec3_s *this_mult_c(vec3_s *this, const double c);
vec3_s vec_mult_c(const vec3_s v, double c);
vec3_s *this_neg(vec3_s *this);
vec3_s vec_neg(const vec3_s v);

vec3_s *this_div_c(vec3_s *this, const double c);
vec3_s vec_div_c(const vec3_s u, const double c);

double length(const vec3_s *u);
double length_sq(const vec3_s *u);

vec3_s *this_unit_vec(vec3_s *this);
vec3_s vec_unit_vec(const vec3_s v);


void vec3_print(const vec3_s *in);

// utility
double dot(const vec3_s *u, const vec3_s *v);
vec3_s vec_cross(const vec3_s u, const vec3_s v);

vec3_s vec_add_vecs(vec3_s list[]);

#define vec_sum(...)  vec_add_vecs((vec3_s[]){__VA_ARGS__, (vec3_s) {.e = NAN, NAN, NAN}});
#endif
