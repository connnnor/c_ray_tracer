#ifndef VEC3_H
#define VEC3_H

#define vec3_new(...) vec3_new_base((vec3_s){.e = {0.0, 0.0, 0.0}, __VA_ARGS__})

typedef struct {
    double e[3];
} vec3_s;


vec3_s *vec3_new_base(vec3_s in);

vec3_s *this_add_vec(vec3_s *this, vec3_s *v);
vec3_s *vec_add_vec(vec3_s *this, vec3_s *v);
vec3_s *vec_add_c(vec3_s *v, double c);

vec3_s *vec_sub_vec(vec3_s *this, vec3_s *v);
vec3_s *this_sub_vec(vec3_s *this, vec3_s *v);
vec3_s *vec_sub_c(vec3_s *this, double c);

vec3_s *this_mult_c(vec3_s *this, double c);
vec3_s *vec_mult_c(vec3_s *this, double c);
vec3_s *this_neg(vec3_s *this);
vec3_s *vec_neg(vec3_s *this);

vec3_s *this_div_c(vec3_s *this, double c);
vec3_s *vec_div_c(vec3_s *this, double c);

double length(vec3_s *this);
double length_sq(vec3_s *this);


vec3_s *this_unit_vec(vec3_s *this);
vec3_s *vec_unit_vec(vec3_s *v);


void vec3_print(vec3_s *in);
#endif
