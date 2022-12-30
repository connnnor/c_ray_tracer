#include <stdlib.h> // malloc
#include <stdio.h>
#include <math.h>
#include "vec3.h"

vec3_s *vec3_new_base(vec3_s in) {
    vec3_s *out = malloc(sizeof(vec3_s));
    *out = (vec3_s) {.e[0] = in.e[0], .e[1] = in.e[1], .e[2] = in.e[2]};
    return out;
}

void vec_delete(vec3_s *in) {
    free(in);
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
