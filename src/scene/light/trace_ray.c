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
	t_color		color;
	double		closest;
	t_trace_ctx	ctx;

	if (depth > MAX_DEPTH)
		return (color_black());
	color = color_black();
	closest = INFINITY;
	ctx = (t_trace_ctx){&color, &closest, ray, scene, depth};
	trace_sphere(&ctx);
	trace_cylinder(&ctx);
	trace_plane(&ctx);
	return (color);
}
