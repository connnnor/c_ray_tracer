#include "material.h"
#include "vec3.h"
#include <stdlib.h> // NULL

void mat_delete(material_s *mat) {
    free(mat->private);
    free(mat);
}

material_s *lambert_new(const color_s c) {
	material_s *mat = malloc(sizeof(material_s));
	metal_material_s *mat_lambert = malloc(sizeof(lambert_material_s));
	mat_lambert->parent = mat;
	*mat = (material_s){.private=mat_lambert, .scatter_fp=lambert_scatter, .c = c};
	return mat;
}

ray_s* lambert_scatter(const ray_s *r, const hit_s *hit, const material_s *mat) {
    vec3_s scatter_dir = vec_add_vec(hit->norm, vec_rand_in_unit_sphere());
    ray_s scattered = (ray_s) {.orig = hit->pt, .dir = scatter_dir};
    return ray_new_base((ray_s) {.orig = scattered.orig, .dir = scattered.dir});
}

material_s *metal_new(const color_s c) {
	material_s *mat = malloc(sizeof(material_s));
	metal_material_s *mat_metal = malloc(sizeof(metal_material_s));
	mat->c = c;
	mat_metal->parent = mat;
	*mat = (material_s){.private=mat_metal, .scatter_fp=metal_scatter, .c = c};
	return mat;
}


ray_s* metal_scatter(const ray_s *r, const hit_s *hit, const material_s *mat) {
    metal_material_s *m = mat->private;
    vec3_s reflected = vec_reflect(vec_unit_vec(r->dir), hit->norm);
    ray_s scattered = (ray_s) {.orig = hit->pt, .dir = reflected};
    if ( dot(&scattered.dir, &hit->norm) > 0.0) {
        return ray_new_base((ray_s) {.orig = scattered.orig, .dir = scattered.dir});
    } else {
        return NULL;
    }
}
