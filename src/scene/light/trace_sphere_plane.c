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

static t_color	get_reflection_color(t_reflection_ctx *ctx)
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

static void	process_plane_hit(t_trace_ctx *ctx, t_plane *pl, double t)
{
	t_vec3				hit_point;
	t_vec3				normal;
	t_color				local_color;
	t_lighting_ctx		light_ctx;
	t_reflection_ctx	refl_ctx;

	hit_point = ray_at(ctx->ray, t);
	normal = pl->normal;
	light_ctx = (t_lighting_ctx){hit_point, normal, pl->color,
		pl->specular, ctx->scene, ctx->scene->camera.position};
	local_color = compute_lighting(&light_ctx);
	if (pl->reflectivity > 0)
	{
		refl_ctx = (t_reflection_ctx){ctx->ray, hit_point, normal,
			pl->reflectivity, ctx->scene, ctx->depth};
		local_color = color_blend(local_color,
				get_reflection_color(&refl_ctx), pl->reflectivity);
	}
	*ctx->color = local_color;
	*ctx->closest = t;
}

void	trace_plane(t_trace_ctx *ctx)
{
	t_plane	*pl;
	double	t;

	pl = ctx->scene->planes;
	while (pl)
	{
		if (intersect_plane(ctx->ray, pl, &t) && t < *ctx->closest)
			process_plane_hit(ctx, pl, t);
		pl = pl->next;
	}
}

static void	process_sphere_hit(t_trace_ctx *ctx, t_sphere *sp, double t)
{
	t_vec3				hit_point;
	t_vec3				normal;
	t_color				local_color;
	t_lighting_ctx		light_ctx;
	t_reflection_ctx	refl_ctx;

	hit_point = ray_at(ctx->ray, t);
	normal = vec3_normalize(vec3_sub(hit_point, sp->center));
	light_ctx = (t_lighting_ctx){hit_point, normal, sp->color,
		sp->specular, ctx->scene, ctx->scene->camera.position};
	local_color = compute_lighting(&light_ctx);
	if (sp->reflectivity > 0)
	{
		refl_ctx = (t_reflection_ctx){ctx->ray, hit_point, normal,
			sp->reflectivity, ctx->scene, ctx->depth};
		local_color = color_blend(local_color,
				get_reflection_color(&refl_ctx), sp->reflectivity);
	}
	*ctx->color = local_color;
	*ctx->closest = t;
}

void	trace_sphere(t_trace_ctx *ctx)
{
	t_sphere	*sp;
	double		t;

	sp = ctx->scene->spheres;
	while (sp)
	{
		if (intersect_sphere(ctx->ray, sp, &t) && t < *ctx->closest)
			process_sphere_hit(ctx, sp, t);
		sp = sp->next;
	}
}
