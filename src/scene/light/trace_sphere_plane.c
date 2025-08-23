/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_sphere_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:00:00 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 00:00:00 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

static t_color	get_reflection_color(t_ray ray, t_vec3 hit_point, t_vec3 normal,
	double reflectivity, t_scene *scene, int depth)
{
	t_vec3	reflected_dir;
	t_ray	reflected_ray;

	if (reflectivity <= 0)
		return ((t_color){0, 0, 0});
	reflected_dir = vec3_normalize(reflect(ray.direction, normal));
	reflected_ray = create_ray(vec3_add(hit_point, vec3_scale(normal, 1e-4)),
			reflected_dir);
	return (trace_ray(reflected_ray, scene, depth + 1));
}

void	trace_plane(t_color *color, double *closest, t_ray ray,
	t_scene *scene, int depth)
{
	t_plane	*pl;
	t_vec3	hit_point;
	t_vec3	normal;
	double	t;
	t_color	local_color;

	pl = scene->planes;
	while (pl)
	{
		if (intersect_plane(ray, pl, &t) && t < *closest)
		{
			hit_point = ray_at(ray, t);
			normal = pl->normal;
			local_color = compute_lighting(hit_point, normal, pl->color,
					pl->specular, scene, scene->camera.position);
			if (pl->reflectivity > 0)
				local_color = color_blend(local_color,
						get_reflection_color(ray, hit_point, normal,
							pl->reflectivity, scene, depth), pl->reflectivity);
			*color = local_color;
			*closest = t;
		}
		pl = pl->next;
	}
}

void	trace_sphere(t_color *color, double *closest, t_ray ray,
	t_scene *scene, int depth)
{
	t_sphere	*sp;
	double		t;
	t_vec3		hit_point;
	t_vec3		normal;
	t_color		local_color;

	sp = scene->spheres;
	while (sp)
	{
		if (intersect_sphere(ray, sp, &t) && t < *closest)
		{
			hit_point = ray_at(ray, t);
			normal = vec3_normalize(vec3_sub(hit_point, sp->center));
			local_color = compute_lighting(hit_point, normal, sp->color,
					sp->specular, scene, scene->camera.position);
			if (sp->reflectivity > 0)
				local_color = color_blend(local_color,
						get_reflection_color(ray, hit_point, normal,
							sp->reflectivity, scene, depth), sp->reflectivity);
			*color = local_color;
			*closest = t;
		}
		sp = sp->next;
	}
}
