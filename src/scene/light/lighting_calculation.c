/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_calculation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:48:07 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 20:21:58 by pshcherb         ###   ########.fr       */
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
}

static t_color	calculate_light_contribution(t_light_c *lc, t_vec3 hit_point,
	t_vec3 normal, t_color obj_color)
{
	lc->light_dir = vec3_normalize(vec3_sub(lc->light->position, hit_point));
	lc->dot = vec3_dot(normal, lc->light_dir);
	if (lc->dot <= 0)
		return ((t_color){0, 0, 0});
	lc->intensity = lc->light->brightness * lc->dot;
	return (color_scale(obj_color, lc->intensity));
}

static t_color	compute_lighting_internal(t_vec3 hit_point, t_vec3 normal,
	t_color obj_color, t_scene *scene)
{
	t_light_c	lc;
	t_color		light_contrib;

	init_lighting_calc(&lc, obj_color, scene);
	while (lc.light)
	{
		light_contrib = calculate_light_contribution(&lc, hit_point,
				normal, obj_color);
		lc.diffuse_total = color_add(lc.diffuse_total, light_contrib);
		lc.light = lc.light->next;
	}
	return (color_add(lc.ambient, lc.diffuse_total));
}

t_color	compute_lighting(t_vec3 hit_point, t_vec3 normal, t_color obj_color,
	double specular, t_scene *scene, t_vec3 camera_pos)
{
	(void)specular;
	(void)camera_pos;
	return (compute_lighting_internal(hit_point, normal, obj_color, scene));
}
