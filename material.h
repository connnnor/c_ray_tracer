#ifndef MATERIAL_H
#define MATERIAL_H
#include "ray.h"
#include "hittable.h"

// generic material

struct material_s;

typedef ray_s* (*scatter_func)(const ray_s *, const hit_s *hit, const struct material_s *);

typedef struct material_s {
	void *private;
    scatter_func scatter_fp;
    color_s c;
} material_s;

// lambertian material

typedef struct lambert_material_s {
	material_s *parent;
} lambert_material_s;

material_s *lambert_new(const color_s c);
ray_s* lambert_scatter(const ray_s *r, const hit_s *hit, const material_s *mat);

// metal material

typedef struct metal_material_s {
	material_s *parent;
} metal_material_s;

material_s *metal_new(const color_s c);
ray_s* metal_scatter(const ray_s *r, const hit_s *hit, const material_s *mat);

#endif
