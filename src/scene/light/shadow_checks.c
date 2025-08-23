/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:00:00 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 20:30:16 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

bool	check_spheres_shadow(t_scene *scene, t_ray shadow_ray,
	double light_dist)
{
	double		t;
	t_sphere	*sp;

	sp = scene->spheres;
	while (sp)
	{
		if (intersect_sphere(shadow_ray, sp, &t))
		{
			if (t > 1e-4 && t < light_dist)
				return (true);
		}
		sp = sp->next;
	}
	return (false);
}

bool	check_planes_shadow(t_scene *scene, t_ray shadow_ray,
	double light_dist)
{
	double	t;
	t_plane	*pl;

	pl = scene->planes;
	while (pl)
	{
		if (intersect_plane(shadow_ray, pl, &t))
		{
			if (t > 1e-4 && t < light_dist)
				return (true);
		}
		pl = pl->next;
	}
	return (false);
}

bool	check_cylinders_shadow(t_scene *scene, t_ray shadow_ray,
	double light_dist)
{
	double		t;
	t_cylinder	*cy;

	cy = scene->cylinders;
	while (cy)
	{
		if (intersect_cylinder(shadow_ray, cy, &t))
		{
			if (t > 1e-4 && t < light_dist)
				return (true);
		}
		cy = cy->next;
	}
	return (false);
}

bool	check_all_objects_shadow(t_scene *scene, t_ray shadow_ray,
	double light_dist)
{
	if (check_spheres_shadow(scene, shadow_ray, light_dist))
		return (true);
	if (check_planes_shadow(scene, shadow_ray, light_dist))
		return (true);
	if (check_cylinders_shadow(scene, shadow_ray, light_dist))
		return (true);
	return (false);
}
