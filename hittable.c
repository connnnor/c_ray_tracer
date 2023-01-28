#include "hittable.h"
#include <stdlib.h> //malloc, free
#include "material.h"

// hit_s
// hit record
hit_s *hit_new(const ray_s *r, const double t, const point_s p, const vec3_s *outward_norm, material_s *mat) {
	hit_s *out = malloc(sizeof(hit_s));
	bool front = dot(&r->dir, outward_norm) < 0.0;

	 *out = (hit_s) {.t = t,
					 .pt = p, 
					 .front = front, 
					 .mat = mat,
					 .norm = front ? *outward_norm : vec_neg(*outward_norm)};
	return out;
}


// obj_s generic

obj_s *copy_obj(obj_s *obj) {
	obj_s *out = malloc(sizeof(obj_s));
	*out = (obj_s) {.private = obj->private , .hit_fp = obj->hit_fp};
	return out;
}

// hittable list

hit_s* list_hit(const ray_s *r, const double t_min, const double t_max, const obj_s *list_obj) {
	hit_s *out = NULL;
	list_obj_s *list = list_obj->private;
	double t_local_max = t_max;
	for (int i=0; i < list->len; i++) {
		obj_s *obj = list->objs[i];
		hit_s *hit = obj->hit_fp(r, t_min, t_local_max, obj);
		if (hit != NULL) {
			// found a closer one. delete
			if (out != NULL) { hit_delete(out); }
			out = hit;
			t_local_max = hit->t;
		}
	}
	return out;
}

obj_s *list_new_obj() {
	obj_s *out = malloc(sizeof(obj_s));
	list_obj_s *out_li = malloc(sizeof(list_obj_s));
	*out = (obj_s){.private=out_li};
	return out;
}

list_obj_s *list_new() {
	obj_s *obj = malloc(sizeof(obj_s));
	list_obj_s *list = malloc(sizeof(list_obj_s));
	*obj = (obj_s){.private=list};
	list->parent = obj;
	list->objs = malloc(sizeof(sizeof(obj_s*) * 1));
	list->len = 0;
	return list;
}

void list_delete(list_obj_s *list) {
	free(list->parent);
	for (int i=0; i < list->len; i++) {
		obj_s *sphere_obj = list->objs[i];
		sphere_delete(sphere_obj);
	}
	free(list->objs);
	free(list);
}

void list_add(list_obj_s *list, obj_s * obj) {
	list->len++;
	list->objs = realloc(list->objs, sizeof(obj_s*) * list->len);
	list->objs[list->len - 1] = obj;
}
void list_add_obj(obj_s *list_obj, obj_s * obj) {
	list_obj_s *list = list_obj->private;
	list_add(list, obj);
}

// sphere

typedef struct sphere_obj_s {
	point_s center; // center
	double rad;  // raidus
} sphere_obj_s;

obj_s *sphere_new(const point_s p, double r, material_s *mat) {
	obj_s *out = malloc(sizeof(obj_s));
	sphere_obj_s *out_sp = malloc(sizeof(sphere_obj_s));
	out_sp->center = p;
	out_sp->rad = r;
	*out = (obj_s){.private=out_sp, .hit_fp=sphere_hit, .mat=mat};
	return out;
}

void hit_delete(hit_s *obj) {
	free(obj);
}

void sphere_delete(obj_s *obj) {
	sphere_obj_s *sp = obj->private;
    mat_delete(obj->mat);
	free(sp);
	free(obj);
}

hit_s* sphere_hit(const ray_s *r, const double t_min, const double t_max, const obj_s *obj) {
	sphere_obj_s *sp = obj->private;

	vec3_s oc = vec_sub_vec(r->orig, sp->center);

	double a = length_sq(&r->dir);
	double half_b = dot(&oc, &r->dir);
	double c = length_sq(&oc) - sp->rad * sp->rad;

	double discr = half_b*half_b - a*c;
	if (discr < 0.0) { return NULL; }

	double sqrt_d = sqrt(discr);

	double root = (-half_b - sqrt_d) / a;
	if (root < t_min || t_max < root) {
		root = (-half_b + sqrt_d) / a;
		if (root < t_min || t_max < root) {
			return NULL;
		}
	}
	point_s hit_pt = point_at(r, root);
	vec3_s out_norm = vec_div_c(vec_sub_vec(hit_pt, sp->center), sp->rad);
	hit_s *out = hit_new(r, root, hit_pt, &out_norm, obj->mat);
	return out;
}

// other shapes
