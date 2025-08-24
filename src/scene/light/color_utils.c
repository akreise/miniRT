/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:00:00 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 00:00:00 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

t_color	color_blend(t_color c1, t_color c2, double factor)
{
	t_color	result;

	result.r = c1.r * (1 - factor) + c2.r * factor;
	result.g = c1.g * (1 - factor) + c2.g * factor;
	result.b = c1.b * (1 - factor) + c2.b * factor;
	return (result);
}

t_color	trace_ray_recursive(t_ray ray, t_scene *scene, int depth)
{
	t_color		color;
	double		closest;
	t_trace_ctx	ctx;

	if (depth <= 0)
		return ((t_color){0, 0, 0});
	color = (t_color){0, 0, 0};
	closest = 1e30;
	ctx = (t_trace_ctx){&color, &closest, ray, scene, depth - 1};
	trace_sphere(&ctx);
	trace_plane(&ctx);
	trace_cylinder(&ctx);
	return (color);
}
