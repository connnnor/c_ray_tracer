#include <stdlib.h> // malloc
#include <stdio.h>
#include <math.h>
#include "vec3.h"
#include "rt_utils.h"

vec3_s *vec3_new_base(vec3_s in) {
    vec3_s *out = malloc(sizeof(vec3_s));
    *out = (vec3_s) {.e[0] = in.e[0], .e[1] = in.e[1], .e[2] = in.e[2]};
    return out;
}

void vec_delete(vec3_s *in) {
    free(in);
}


vec3_s vec_rand() {
    return (vec3_s) {.e = rand_double(), rand_double(), rand_double()};
}

vec3_s vec_rand_in(const double min, const double max) {
    return (vec3_s) {.e = rand_double_in(min, max), rand_double_in(min, max), rand_double_in(min, max)};
}

vec3_s vec_rand_in_unit_sphere() {
    while (1) {
        vec3_s p = vec_rand_in(-1.0, 1.0);
        double len_sq = length_sq(&p);
        if (len_sq >= 1.0) { continue; }
        return vec_unit_vec(p);
    }
}

vec3_s *this_add_vec(vec3_s *this, const vec3_s v) {
    (*this).e[0] += v.e[0];
    (*this).e[1] += v.e[1];
    (*this).e[2] += v.e[2];
    return this;
}

vec3_s vec_add_vec(const vec3_s u, const vec3_s v) {
    vec3_s out = {.e = {u.e[0], u.e[1], u.e[2]}};
    this_add_vec(&out, v);
    return out;
}

vec3_s *this_add_c(vec3_s *this, const double c) {
    (*this).e[0] += c;
    (*this).e[1] += c;
    (*this).e[2] += c;
    return this;
}


vec3_s vec_add_c(const vec3_s v, const double c) {
    vec3_s out = {.e = {v.e[0], v.e[1], v.e[2]}};
    this_add_c(&out, c);
    return out;
}

vec3_s *this_sub_vec(vec3_s *this, const vec3_s v) {
    (*this).e[0] -= v.e[0];
    (*this).e[1] -= v.e[1];
    (*this).e[2] -= v.e[2];
    return this;
}

vec3_s vec_sub_vec(const vec3_s u, const vec3_s v) {
    vec3_s out = {.e = {u.e[0], u.e[1], u.e[2]}};
    this_sub_vec(&out, v);
    return out;
}

vec3_s *this_sub_c(vec3_s *this, double c) {
    this_add_c(this, -1.0 * c);
    return this;
}

vec3_s *vec_sub_c(const vec3_s *v, double c) {
    vec3_s *out = vec3_new(.e = {(*v).e[0], (*v).e[1], (*v).e[2]});
    this_sub_c(out, c);
    return out;
}


vec3_s vec_mult_vec(const vec3_s u, const vec3_s v) {
    return (vec3_s) {.e = {u.e[0] * v.e[0],
                           u.e[1] * v.e[1],
                           u.e[2] * v.e[2]}};
}

vec3_s *this_mult_c(vec3_s *this, double c) {
    (*this).e[0] *= c;
    (*this).e[1] *= c;
    (*this).e[2] *= c;
    return this;
}

vec3_s vec_mult_c(const vec3_s v, double c) {
    vec3_s out = {.e = {v.e[0], v.e[1], v.e[2]}};
    this_mult_c(&out, c);
    return out;
}

vec3_s *this_div_c(vec3_s *this, const double c) {
    (*this).e[0] /= c;
    (*this).e[1] /= c;
    (*this).e[2] /= c;
    return this;
}

vec3_s vec_div_c(const vec3_s v, const double c) {
    vec3_s out = {.e = {v.e[0], v.e[1], v.e[2]}};
    this_div_c(&out, c);
    return out;
}

vec3_s *this_neg(vec3_s *this) {
    this_mult_c(this, -1.0);
    return this;
}

vec3_s vec_neg(const vec3_s v) {
    vec3_s out = {.e = {v.e[0], v.e[1], v.e[2]}};
    this_neg(&out);
    return out;
}

double length(const vec3_s *this) {
    return sqrt(length_sq(this));
}

double length_sq(const vec3_s *this) {
    return (*this).e[0] * (*this).e[0] + \
           (*this).e[1] * (*this).e[1] + \
           (*this).e[2] * (*this).e[2];
}

vec3_s *this_unit_vec(vec3_s *this) {
    return this_div_c(this, length(this));
}

vec3_s vec_unit_vec(const vec3_s v) {
    vec3_s out = {.e = {v.e[0], v.e[1], v.e[2]}};
    this_unit_vec(&out);
    return out;
}

// Utility

inline double dot(const vec3_s *u, const vec3_s *v) {
    return (*v).e[0] * (*u).e[0] +
           (*v).e[1] * (*u).e[1] +
           (*v).e[2] * (*u).e[2];
}

inline vec3_s vec_cross(const vec3_s u, const vec3_s v) {
    return (vec3_s) {.e = {
        u.e[1] * v.e[2] - u.e[2] * v.e[1],  // out[0]
        u.e[2] * v.e[0] - u.e[0] * v.e[2],  // out[1]
        u.e[0] * v.e[1] - u.e[1] * v.e[0],  // out[2]
        }};
}

void vec3_print(const vec3_s *in) {
    printf("v = (%f, %f, %f)\n", (*in).e[0], (*in).e[1], (*in).e[2]);
}


// last vec3_s in list should be {NAN, NAN, NAN}
vec3_s vec_add_vecs(vec3_s list[]) {
        vec3_s sum_v = {.e = {0.0, 0.0, 0.0}};
	for (int i=0; !isnan(list[i].e[0]); i++) {
	 this_add_vec(&sum_v, list[i]); 
	}
	return sum_v;
}

bool vec_near_zero(const vec3_s u) {
    const double s = 0.00000001;
    return (fabs(u.e[0]) < s) && (fabs(u.e[1]) < s) && (fabs(u.e[2]) < s);
}

vec3_s vec_reflect(const vec3_s v, const vec3_s n) {
    return vec_sub_vec(n, vec_mult_c(n, 2.0 * dot(&v, &n)));
}
