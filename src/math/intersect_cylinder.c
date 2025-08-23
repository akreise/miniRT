/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:22:53 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 18:15:13 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h"

static bool	cut_cyl(t_cylinder *cylinder, t_ray ray, double *t)
{
	t_vec3	hit;
	t_vec3	from_base;
	double	h;

	hit = ray_at(ray, *t);
	from_base = vec3_sub(hit, cylinder->base);
	h = vec3_dot(from_base, cylinder->direction);
	if (h < 0 || h > cylinder->height)
		return (false);
	return (true);
}

static bool	check_cylinder_side(t_ray ray, t_cylinder *cylinder, double *t)
{
	t_cyl_i	c;
	double	t_side;

	c = (t_cyl_i){0};
	c = init_cylinder_i(ray, cylinder, c);
	if (c.valid)
	{
		t_side = INFINITY;
		if (min_pos(c.t0, c.t1, &t_side) && cut_cyl(cylinder, ray, &t_side))
		{
			*t = t_side;
			return (true);
		}
	}
	return (false);
}

bool	intersect_cylinder(t_ray ray, t_cylinder *cylinder, double *t)
{
	bool	found;
	double	t_cap;

	found = false;
	*t = INFINITY;
	if (check_cylinder_side(ray, cylinder, t))
		found = true;
	t_cap = INFINITY;
	if (intersect_caps(ray, cylinder, &t_cap))
	{
		if (!found || t_cap < *t)
		{
			*t = t_cap;
			found = true;
		}
	}
	return (found);
}
