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

static t_color	calculate_light_contribution(t_light_c *lc, t_vec3 hit_point,
	t_vec3 normal, t_color obj_color, double specular, t_vec3 view_dir)
{
	t_color	result;
	t_color	diffuse;
	t_color	spec_color;

	lc->light_dir = vec3_normalize(vec3_sub(lc->light->position, hit_point));
	lc->dot = vec3_dot(normal, lc->light_dir);
	lc->normal = normal;
	result = (t_color){0, 0, 0};
	if (lc->dot <= 0)
		return (result);
	lc->shadow = shadow_factor(hit_point, lc->light, lc->scene);
	if (lc->shadow <= 0)
		return (result);
	lc->intensity = lc->light->brightness * lc->dot * lc->shadow;
	diffuse = color_scale(obj_color, lc->intensity);
	result = color_add(result, diffuse);
	spec_color = calculate_specular(lc, view_dir, specular);
	return (color_add(result, spec_color));
}

t_color	compute_lighting(t_vec3 hit_point, t_vec3 normal, t_color obj_color,
	double specular, t_scene *scene, t_vec3 camera_pos)
{
	t_light_c	lc;
	t_color		light_contrib;
	t_vec3		view_dir;

	init_lighting_calc(&lc, obj_color, scene);
	view_dir = vec3_normalize(vec3_sub(camera_pos, hit_point));
	while (lc.light)
	{
		light_contrib = calculate_light_contribution(&lc, hit_point,
				normal, obj_color, specular, view_dir);
		lc.diffuse_total = color_add(lc.diffuse_total, light_contrib);
		lc.light = lc.light->next;
	}
	return (color_add(lc.ambient, lc.diffuse_total));
}
