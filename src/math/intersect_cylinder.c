/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:22:53 by pshcherb          #+#    #+#             */
/*   Updated: 2025/07/24 19:21:26 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h" 

static bool intersect_disk(t_vec3 center, t_vec3 normal, t_ray ray, double *t_out)
{
	double denom = vec3_dot(ray.direction, normal);
	if (fabs(denom) < 1e-6) // Луч почти параллелен
		return false;

	double t = vec3_dot(vec3_sub(center, ray.origin), normal) / denom;
	if (t < 0)
		return false;

	t_vec3 p = ray_at(ray, t);
	double dist = vec3_length(vec3_sub(p, center));

	if (dist <= 1e-6 || dist <= *t_out)
	{
		*t_out = t;
		return true;
	}
	return false;
}

static bool intersect_caps(t_ray ray, t_cylinder *cylinder, double *t)
{
	bool hit = false;
	double t_cap;

	// Нижняя крышка
	t_cap = *t;
	if (intersect_disk(cylinder->base, cylinder->direction, ray, &t_cap))
	{
		t_vec3 p = ray_at(ray, t_cap);
		double dist = vec3_length(vec3_sub(p, cylinder->base));
		if (dist <= cylinder->radius && t_cap < *t)
		{
			*t = t_cap;
			hit = true;
		}
	}

	// Верхняя крышка
	t_cap = *t;
	t_vec3 top_center = vec3_add(cylinder->base, vec3_scale(cylinder->direction, cylinder->height));
	if (intersect_disk(top_center, cylinder->direction, ray, &t_cap))
	{
		t_vec3 p = ray_at(ray, t_cap);
		double dist = vec3_length(vec3_sub(p, top_center));
		if (dist <= cylinder->radius && t_cap < *t)
		{
			*t = t_cap;
			hit = true;
		}
	}
	return hit;
}


static	t_vec3	project_onto(t_vec3 a, t_vec3 b)
{
	return (vec3_scale(b, vec3_dot(a, b)));
}

static	bool	cut_cyl(t_cylinder *cylinder, t_ray ray, double *t)
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

static	t_cyl_i	init_cylinder_i(t_ray ray, t_cylinder *cylinder, t_cyl_i cyl)
{
	double	sqrt_d;

	cyl.oc = vec3_sub(ray.origin, cylinder->base);
	cyl.d_proj = vec3_sub(ray.direction,
			project_onto(ray.direction, cylinder->direction));
	cyl.oc_proj = vec3_sub(cyl.oc,
			project_onto(cyl.oc, cylinder->direction));
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

bool intersect_cylinder(t_ray ray, t_cylinder *cylinder, double *t)
{
	t_cyl_i	c;
	bool	found = false;
	double	t_side = INFINITY;
	double	t_cap = INFINITY;

	c = init_cylinder_i(ray, cylinder, (t_cyl_i){0});
	if (c.valid)
	{
		if (min_pos(c.t0, c.t1, &t_side) && cut_cyl(cylinder, ray, &t_side))
		{
			*t = t_side;
			found = true;
		}
	}

	if (intersect_caps(ray, cylinder, &t_cap))
	{
		if (!found || t_cap < *t)
		{
			*t = t_cap;
			found = true;
		}
	}

	return found;
}
