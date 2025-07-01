/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:22:38 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/15 17:14:55 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h"

static	t_plane_i	init_plane_i(t_ray ray, t_plane *plane, t_plane_i p)
{
	p.point_to_origin = vec3_sub(plane->point, ray.origin);
	p.denom = vec3_dot(plane->normal, ray.direction);
	if (fabs(p.denom) < 1e-6)
	{
		p.valid = false;
		return (p);
	}
	p.t = vec3_dot(p.point_to_origin, plane->normal) / p.denom;
	p.valid = (p.t > 0.001);
	return (p);
}

bool	intersect_plane(t_ray ray, t_plane *plane, double *t)
{
	t_plane_i	p;

	p = init_plane_i(ray, plane, p);
	if (!p.valid)
		return (false);
	*t = p.t;
	return (true);
}
