#include "../../includes/math_utils.h"

static t_triangle_i init_triangle_i(t_ray ray, t_triangle *tri)
{
	t_triangle_i i;

	i.edge1 = vec3_sub(tri->v1, tri->v0);
	i.edge2 = vec3_sub(tri->v2, tri->v0);
	i.h = vec3_cross(ray.direction, i.edge2);
	i.a = vec3_dot(i.edge1, i.h);

	if (fabs(i.a) < 1e-8)
	{
		i.valid = false;
		return i; // Луч параллелен треугольнику
	}
	i.f = 1.0 / i.a;
	i.s = vec3_sub(ray.origin, tri->v0);
	i.u = i.f * vec3_dot(i.s, i.h);
	if (i.u < 0.0 || i.u > 1.0)
	{
		i.valid = false;
		return i;
	}
	i.q = vec3_cross(i.s, i.edge1);
	i.v = i.f * vec3_dot(ray.direction, i.q);
	if (i.v < 0.0 || i.u + i.v > 1.0)
	{
		i.valid = false;
		return i;
	}
	i.t = i.f * vec3_dot(i.edge2, i.q);
	i.valid = (i.t > 1e-4); // Маленький ε для защиты от самопересечений
	return i;
}

bool intersect_triangle(t_ray ray, t_triangle *tri, double *t_out)
{
	t_triangle_i i = init_triangle_i(ray, tri);
	if (!i.valid)
		return false;
	*t_out = i.t;
	return true;
}
