/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:05:31 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 18:36:44 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

#define MAX_DEPTH 5

t_vec3	get_cylinder_normal(t_cylinder *cy, t_vec3 hit)
{
	t_vec3	from_base;
	double	proj;
	t_vec3	proj_vec;

	from_base = vec3_sub(hit, cy->base);
	proj = vec3_dot(from_base, cy->direction);
	if (proj <= 1e-6)
		return (vec3_scale(cy->direction, -1));
	if (proj >= cy->height - 1e-6)
		return (cy->direction);
	proj_vec = vec3_scale(cy->direction, proj);
	return (vec3_normalize(vec3_sub(from_base, proj_vec)));
}

static t_color	color_black(void)
{
	return ((t_color){0, 0, 0});
}

t_color	trace_ray(t_ray ray, t_scene *scene, int depth)
{
	t_color	color;
	double	closest;

	if (depth > MAX_DEPTH)
		return (color_black());
	color = color_black();
	closest = INFINITY;
	trace_sphere(&color, &closest, ray, scene, depth);
	trace_cylinder(&color, &closest, ray, scene, depth);
	trace_plane(&color, &closest, ray, scene, depth);
	return (color);
}
