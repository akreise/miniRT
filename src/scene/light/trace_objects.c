/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:00:00 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 00:00:00 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

static t_color	calculate_reflection(t_ray ray, t_vec3 hit_point, t_vec3 normal,
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

void	trace_cylinder(t_color *color, double *closest, t_ray ray,
	t_scene *scene, int depth)
{
	t_cylinder	*cy;
	t_vec3		hit_point;
	t_vec3		normal;
	double		t;
	t_color		local_color;

	cy = scene->cylinders;
	while (cy)
	{
		if (intersect_cylinder(ray, cy, &t) && t < *closest)
		{
			hit_point = ray_at(ray, t);
			normal = get_cylinder_normal(cy, hit_point);
			local_color = compute_lighting(hit_point, normal, cy->color,
					cy->specular, scene, scene->camera.position);
			if (cy->reflectivity > 0)
				local_color = color_blend(local_color,
						calculate_reflection(ray, hit_point, normal,
							cy->reflectivity, scene, depth), cy->reflectivity);
			*color = local_color;
			*closest = t;
		}
		cy = cy->next;
	}
}
