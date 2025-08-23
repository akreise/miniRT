/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:00:00 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 18:14:56 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h"

bool	intersect_disk(t_vec3 center, t_vec3 normal, t_ray ray, double *t_out)
{
	double	denom;
	double	t;
	t_vec3	p;
	double	dist;

	denom = vec3_dot(ray.direction, normal);
	if (fabs(denom) < 1e-6)
		return (false);
	t = vec3_dot(vec3_sub(center, ray.origin), normal) / denom;
	if (t < 0)
		return (false);
	p = ray_at(ray, t);
	dist = vec3_length(vec3_sub(p, center));
	if (dist <= 1e-6 || dist <= *t_out)
	{
		*t_out = t;
		return (true);
	}
	return (false);
}

static t_vec3	project_onto_cyl(t_vec3 a, t_vec3 b)
{
	return (vec3_scale(b, vec3_dot(a, b)));
}

static bool	check_cap_hit(t_vec3 center, t_cylinder *cyl, t_ray ray, double *t)
{
	t_vec3	p;
	double	dist;
	double	t_cap;

	t_cap = *t;
	if (intersect_disk(center, cyl->direction, ray, &t_cap))
	{
		p = ray_at(ray, t_cap);
		dist = vec3_length(vec3_sub(p, center));
		if (dist <= cyl->radius && t_cap < *t)
		{
			*t = t_cap;
			return (true);
		}
	}
	return (false);
}

bool	intersect_caps(t_ray ray, t_cylinder *cylinder, double *t)
{
	bool	hit;
	t_vec3	top_center;

	hit = false;
	if (check_cap_hit(cylinder->base, cylinder, ray, t))
		hit = true;
	top_center = vec3_add(cylinder->base,
			vec3_scale(cylinder->direction, cylinder->height));
	if (check_cap_hit(top_center, cylinder, ray, t))
		hit = true;
	return (hit);
}

t_cyl_i	init_cylinder_i(t_ray ray, t_cylinder *cylinder, t_cyl_i cyl)
{
	double	sqrt_d;

	cyl.oc = vec3_sub(ray.origin, cylinder->base);
	cyl.d_proj = vec3_sub(ray.direction,
			project_onto_cyl(ray.direction, cylinder->direction));
	cyl.oc_proj = vec3_sub(cyl.oc,
			project_onto_cyl(cyl.oc, cylinder->direction));
	cyl.a = vec3_dot(cyl.d_proj, cyl.d_proj);
	cyl.b = 2.0 * vec3_dot(cyl.d_proj, cyl.oc_proj);
	cyl.c = vec3_dot(cyl.oc_proj, cyl.oc_proj)
		- cylinder->radius * cylinder->radius;
	cyl.discriminant = cyl.b * cyl.b - 4 * cyl.a * cyl.c;
	if (cyl.discriminant < 0)
	{
		cyl.valid = false;
		return (cyl);
	}
	sqrt_d = sqrt(cyl.discriminant);
	cyl.t0 = (-cyl.b - sqrt_d) / (2 * cyl.a);
	cyl.t1 = (-cyl.b + sqrt_d) / (2 * cyl.a);
	cyl.valid = true;
	return (cyl);
}
