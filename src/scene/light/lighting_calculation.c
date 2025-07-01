/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning_calculation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:48:07 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/16 16:09:09 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

t_color	compute_lighting(t_vec3 hit_point, t_vec3 normal, t_color obj_color,
						 t_scene *scene)
{
	t_light_c	l;

	l.ambient = color_scale(scene->ambient.color, scene->ambient.ratio);
	l.diffuse_total = (t_color){0, 0, 0};
	l.light = scene->lights;
	while (l.light)
	{
		l.light_dir = vec3_sub(l.light->position, hit_point);
		l.light_dir = vec3_normalize(l.light_dir);
		l.dot = vec3_dot(normal, l.light_dir);
		if (l.dot > 0)
		{
			l.intensity = l.light->brightness * l.dot;
			l.diffuse = color_scale(obj_color, l.intensity);
			l.diffuse_total = color_add(l.diffuse_total, l.diffuse);
		}
		l.light = l.light->next;
	}
	return (color_add(l.ambient, l.diffuse_total));
}
