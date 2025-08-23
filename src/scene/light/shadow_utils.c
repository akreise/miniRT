/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:00:00 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 20:51:46 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

static double	check_shadow_ray(t_vec3 point, t_vec3 to_perturbed,
	double light_dist, t_scene *scene)
{
	t_vec3	dir;
	t_ray	shadow_ray;

	dir = vec3_normalize(to_perturbed);
	shadow_ray = create_ray(vec3_add(point, vec3_scale(dir, 1e-4)), dir);
	if (check_all_objects_shadow(scene, shadow_ray, light_dist))
		return (1.0);
	return (0.0);
}

double	calculate_sample_shadow(t_vec3 point, t_light *light, t_scene *scene)
{
	t_vec3	offset;
	t_vec3	perturbed_light;
	t_vec3	to_perturbed;
	double	light_dist;

	offset = random_in_unit_disk();
	perturbed_light = vec3_add(light->position,
			(t_vec3){offset.x * 0.5, offset.y * 0.5, 0});
	to_perturbed = vec3_sub(perturbed_light, point);
	light_dist = vec3_length(to_perturbed);
	return (check_shadow_ray(point, to_perturbed, light_dist, scene));
}

t_vec3	random_in_unit_disk(void)
{
	t_vec3	p;

	p.x = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
	p.y = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
	p.z = 0;
	while (vec3_dot(p, p) >= 1.0)
	{
		p.x = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
		p.y = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
		p.z = 0;
	}
	return (p);
}
