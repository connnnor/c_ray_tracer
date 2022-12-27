#include <stdlib.h> // malloc
#include <stdio.h>
#include <math.h>
#include "vec3.h"

vec3_s *vec3_new_base(vec3_s in) {
//vec3_s *vec3_new() {
    vec3_s *out = malloc(sizeof(vec3_s));
    *out = (vec3_s) {.e[0] = in.e[0], .e[1] = in.e[1], .e[2] = in.e[2]};
    return out;
}

vec3_s *vec_add_vec(vec3_s *this, vec3_s *v) {
    (*this).e[0] += (*v).e[0];
    (*this).e[1] += (*v).e[1];
    (*this).e[2] += (*v).e[2];
}

vec3_s *vec_add_c(vec3_s *this, double c) {
    (*this).e[0] += c;
    (*this).e[1] += c;
    (*this).e[2] += c;
}

vec3_s *vec_sub_vec(vec3_s *this, vec3_s *v) {
    (*this).e[0] -= (*v).e[0];
    (*this).e[1] -= (*v).e[1];
    (*this).e[2] -= (*v).e[2];
}

vec3_s *vec_sub_c(vec3_s *this, double c) {
    vec_add_c(this, -1.0 * c);
}

vec3_s *vec_mult_c(vec3_s *this, double c) {
    (*this).e[0] *= c;
    (*this).e[1] *= c;
    (*this).e[2] *= c;
}

vec3_s *vec_div_c(vec3_s *this, double c) {
    (*this).e[0] /= c;
    (*this).e[1] /= c;
    (*this).e[2] /= c;
}

vec3_s *vec_neg(vec3_s *this) {
    vec_mult_c(this, -1.0);
}

double length(vec3_s *this) {
    return sqrt(length_sq(this));
}


double length_sq(vec3_s *this) {
    return (*this).e[0] * (*this).e[0] + \
           (*this).e[1] * (*this).e[1] + \
           (*this).e[2] * (*this).e[2];
}

void vec3_print(vec3_s *in) {
    printf("v = (%f, %f, %f)\n", (*in).e[0], (*in).e[1], (*in).e[2]);
}
