/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_calculation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:48:07 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 20:51:29 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

static void	init_lighting_calc(t_light_c *lc, t_color obj_color, t_scene *scene)
{
	t_color	ambient_color;

	ambient_color = color_mul(obj_color, scene->ambient.color);
	lc->ambient = color_scale(ambient_color, scene->ambient.ratio);
	lc->diffuse_total = (t_color){0, 0, 0};
	lc->light = scene->lights;
	lc->scene = scene;
}

static t_color	calculate_specular(t_light_c *lc, t_vec3 view_dir,
	double specular)
{
	t_vec3	reflect_dir;
	double	spec;
	double	intensity;

	if (specular <= 0)
		return ((t_color){0, 0, 0});
	reflect_dir = reflect(vec3_scale(lc->light_dir, -1), lc->normal);
	spec = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), specular);
	intensity = lc->light->brightness * spec * lc->shadow;
	return (color_scale(lc->light->color, intensity));
}

static t_color	calculate_light_contribution(t_light_c *lc)
{
	t_color	result;
	t_color	diffuse;
	t_color	spec_color;
	t_vec3	light_vec;

	light_vec = vec3_sub(lc->light->position, lc->hit_point);
	lc->light_dir = vec3_normalize(light_vec);
	lc->dot = vec3_dot(lc->normal, lc->light_dir);
	result = (t_color){0, 0, 0};
	if (lc->dot <= 0)
		return (result);
	lc->shadow = shadow_factor(lc->hit_point, lc->light, lc->scene);
	if (lc->shadow <= 0)
		return (result);
	lc->intensity = lc->light->brightness * lc->dot * lc->shadow;
	diffuse = color_scale(lc->obj_color, lc->intensity);
	result = color_add(result, diffuse);
	spec_color = calculate_specular(lc, lc->view_dir, lc->specular);
	return (color_add(result, spec_color));
}

t_color	compute_lighting(t_lighting_ctx *ctx)
{
	t_light_c	lc;
	t_color		light_contrib;
	t_vec3		view_dir;

	init_lighting_calc(&lc, ctx->obj_color, ctx->scene);
	view_dir = vec3_normalize(vec3_sub(ctx->camera_pos, ctx->hit_point));
	lc.hit_point = ctx->hit_point;
	lc.normal = ctx->normal;
	lc.obj_color = ctx->obj_color;
	lc.specular = ctx->specular;
	lc.view_dir = view_dir;
	while (lc.light)
	{
		light_contrib = calculate_light_contribution(&lc);
		lc.diffuse_total = color_add(lc.diffuse_total, light_contrib);
		lc.light = lc.light->next;
	}
	return (color_add(lc.ambient, lc.diffuse_total));
}
