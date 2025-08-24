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

static t_color	calculate_reflection(t_reflection_ctx *ctx)
{
	t_vec3	reflected_dir;
	t_ray	reflected_ray;

	if (ctx->reflectivity <= 0)
		return ((t_color){0, 0, 0});
	reflected_dir = vec3_normalize(reflect(ctx->ray.direction, ctx->normal));
	reflected_ray = create_ray(vec3_add(ctx->hit_point,
				vec3_scale(ctx->normal, 1e-4)), reflected_dir);
	return (trace_ray(reflected_ray, ctx->scene, ctx->depth + 1));
}

static void	process_cylinder_hit(t_trace_ctx *ctx, t_cylinder *cy, double t)
{
	t_vec3				hit_point;
	t_vec3				normal;
	t_color				local_color;
	t_lighting_ctx		light_ctx;
	t_reflection_ctx	refl_ctx;

	hit_point = ray_at(ctx->ray, t);
	normal = get_cylinder_normal(cy, hit_point);
	light_ctx = (t_lighting_ctx){hit_point, normal, cy->color,
		cy->specular, ctx->scene, ctx->scene->camera.position};
	local_color = compute_lighting(&light_ctx);
	if (cy->reflectivity > 0)
	{
		refl_ctx = (t_reflection_ctx){ctx->ray, hit_point, normal,
			cy->reflectivity, ctx->scene, ctx->depth};
		local_color = color_blend(local_color,
				calculate_reflection(&refl_ctx), cy->reflectivity);
	}
	*ctx->color = local_color;
	*ctx->closest = t;
}

void	trace_cylinder(t_trace_ctx *ctx)
{
	t_cylinder	*cy;
	double		t;

	cy = ctx->scene->cylinders;
	while (cy)
	{
		if (intersect_cylinder(ctx->ray, cy, &t) && t < *ctx->closest)
			process_cylinder_hit(ctx, cy, t);
		cy = cy->next;
	}
}
