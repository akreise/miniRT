/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:22:53 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/15 17:18:25 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h" 

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

bool	intersect_cylinder(t_ray ray, t_cylinder *cylinder, double *t)
{
	t_cyl_i	c;
	bool	men_pos;
	bool	altura;

	c = init_cylinder_i(ray, cylinder, (t_cyl_i){0});
	if (!c.valid)
		return (false);
	men_pos = min_pos(c.t0, c.t1, t);
	if (!men_pos)
		return (false);
	altura = cut_cyl(cylinder, ray, t);
	if (!altura)
		return (false);
	return (true);
}
