/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:00:00 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 00:00:00 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

static bool	check_sphere_shadow(t_scene *scene, t_ray shadow_ray,
	double light_dist, double *t)
{
	t_sphere	*sp;

	sp = scene->spheres;
	while (sp)
	{
		if (intersect_sphere(shadow_ray, sp, t))
		{
			if (*t > 1e-4 && *t < light_dist)
				return (true);
		}
		sp = sp->next;
	}
	return (false);
}

static bool	check_plane_shadow(t_scene *scene, t_ray shadow_ray,
	double light_dist, double *t)
{
	t_plane	*pl;

	pl = scene->planes;
	while (pl)
	{
		if (intersect_plane(shadow_ray, pl, t) && *t > 1e-4 && *t < light_dist)
			return (true);
		pl = pl->next;
	}
	return (false);
}

static bool	check_cylinder_shadow(t_scene *scene, t_ray shadow_ray,
	double light_dist, double *t)
{
	t_cylinder	*cy;

	cy = scene->cylinders;
	while (cy)
	{
		if (intersect_cylinder(shadow_ray, cy, t) && *t > 1e-4 && *t < light_dist)
			return (true);
		cy = cy->next;
	}
	return (false);
}

bool	is_in_shadow(t_scene *scene, t_ray shadow_ray, double light_dist)
{
	double	t;

	if (check_sphere_shadow(scene, shadow_ray, light_dist, &t))
		return (true);
	if (check_plane_shadow(scene, shadow_ray, light_dist, &t))
		return (true);
	if (check_cylinder_shadow(scene, shadow_ray, light_dist, &t))
		return (true);
	return (false);
}

double	calculate_sample_shadow(t_vec3 point, t_light *light, t_scene *scene)
{
	t_vec3	offset;
	t_vec3	offset3d;
	t_vec3	perturbed_light;
	t_vec3	to_perturbed;

	offset = random_in_unit_disk();
	offset3d.x = offset.x * 0.5;
	offset3d.y = offset.y * 0.5;
	offset3d.z = 0;
	perturbed_light = vec3_add(light->position, offset3d);
	to_perturbed = vec3_sub(perturbed_light, point);
	return (calculate_ray_shadow(to_perturbed, point));
}

static double	calculate_ray_shadow(t_vec3 to_perturbed, t_vec3 point)
{
	double	light_dist;
	t_vec3	dir;
	t_ray	shadow_ray;

	light_dist = vec3_length(to_perturbed);
	dir = vec3_normalize(to_perturbed);
	shadow_ray = create_ray(vec3_add(point, vec3_scale(dir, 1e-4)), dir);
	if (is_in_shadow(scene, shadow_ray, light_dist))
		return (1.0);
	return (0.0);
}

t_vec3	random_in_unit_disk(void)
{
	t_vec3	p;

	p.x = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
	p.y = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
	p.z = 0;
	while (vec3_dot(p, p) >= 1.0)
	{
		p.x = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
		p.y = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
		p.z = 0;
	}
	return (p);
}
