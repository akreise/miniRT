/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:22:22 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/15 17:14:06 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h"

static	t_sphere_i	init_sphere_i(t_ray ray, t_sphere *sphere, t_sphere_i s)
{
	s.oc = vec3_sub(ray.origin, sphere->center);
	s.a = vec3_dot(ray.direction, ray.direction);
	s.b = 2.0 * vec3_dot(s.oc, ray.direction);
	s.c = vec3_dot(s.oc, s.oc) - (sphere->radius * sphere->radius);
	s.discriminant = s.b * s.b - 4 * s.a * s.c;
	if (s.discriminant < 0)
	{
		s.valid = false;
		return (s);
	}
	s.valid = true;
	s.sqrt_d = sqrt(s.discriminant);
	s.t0 = (-s.b - s.sqrt_d) / (2.0 * s.a);
	s.t1 = (-s.b + s.sqrt_d) / (2.0 * s.a);
	return (s);
}

bool	intersect_sphere(t_ray ray, t_sphere *sphere, double *t)
{
	t_sphere_i	s;

	s = init_sphere_i(ray, sphere, s);
	if (!s.valid)
		return (false);
	return (min_pos(s.t0, s.t1, t));
}
