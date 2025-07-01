/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:05:31 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/26 17:08:03 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

t_vec3	get_cylinder_normal(t_cylinder *cy, t_vec3 hit)
{
	t_vec3 from_base;
	double proj;
	t_vec3 proj_vec;

	from_base = vec3_sub(hit, cy->base);
	proj = vec3_dot(from_base, cy->direction);
	proj_vec = vec3_scale(cy->direction, proj);
	
	return (vec3_normalize(vec3_sub(from_base, proj_vec)));
}

void    trace_cylinders(t_color *color, double *closest, t_ray ray, t_scene *scene)
{
	t_cylinder *cy;
	t_vec3  hit_point;
	t_vec3  normal;
	double  t;

	cy = scene->cylinders;
	while (cy)
	{
		if (intersect_cylinder(ray, cy, &t) && t < *closest)
		{
			hit_point = ray_at(ray, t);
			normal = get_cylinder_normal(cy, hit_point);
			*color = compute_lighting(hit_point, normal, cy->color, scene);
			*closest = t;
		}
		cy = cy->next;
	}
}

void    trace_plane(t_color *color, double *closest, t_ray ray, t_scene *scene)
{
	t_plane *pl;
	t_vec3  hit_point;
	t_vec3  normal;
	double  t;

	pl = scene->planes;
	while (pl)
	{
		if (intersect_plane(ray, pl, &t) && t < *closest)
		{
			hit_point = ray_at(ray, t);
			normal = pl->normal;
			*color = compute_lighting(hit_point, normal, pl->color, scene);
			*closest = t;
		}
		pl = pl->next;
	}
}

void    trace_sphere(t_color *color, double *closest, t_ray ray, t_scene *scene)
{
	t_sphere *sp;
	double  t;
	t_vec3  hit_point;
	t_vec3  normal;

	sp = scene->spheres;
	while (sp)
	{
		if (intersect_sphere(ray, sp, &t) && t < *closest)
		{
			hit_point = ray_at(ray, t);
			normal = vec3_normalize(vec3_sub(hit_point, sp->center));
			*color = compute_lighting(hit_point, normal, sp->color, scene);
			*closest = t;
		}
		sp = sp->next;
	}
}

t_color trace_ray(t_ray ray, t_scene *scene)
{
	t_color color;
	double  closest;

	closest = 1e30;
	color = (t_color){0, 0, 0};
	trace_sphere(&color, &closest, ray, scene);
	trace_plane(&color, &closest, ray, scene);
	trace_cylinders(&color, &closest, ray, scene);
	return (color);
}