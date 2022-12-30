#ifndef HITTABLE_H
#define HITTABLE_H
#include <stdbool.h>
#include "ray.h"

typedef struct {
    point_s pt;
    vec3_s norm;
    double t;
	bool front;
} hit_s;

// forward declare so i can use in func ptr def
struct obj_s;

typedef hit_s* (*hit_func)(const ray_s *, const double, const double, const struct obj_s *);

typedef struct obj_s {
	void *private;
    hit_func hit_fp;
} obj_s;


typedef struct list_obj_s {
	obj_s **objs;
	int len;
	obj_s *parent;
} list_obj_s;


void hit_delete(hit_s *obj);

obj_s *list_new_obj();
list_obj_s *list_new();
//void list_delete(obj_s *obj);
void list_delete(list_obj_s *list);
hit_s* list_hit(const ray_s *r, const double t_min, const double t_max, const struct obj_s *obj);
void list_add_obj(obj_s *list_obj, obj_s * obj);
void list_add(list_obj_s *list, obj_s * obj);

obj_s *sphere_new(const point_s p, double r);
void sphere_delete(obj_s *obj);
hit_s* sphere_hit(const ray_s *r, const double t_min, const double t_max, const struct obj_s *obj);
#endif
