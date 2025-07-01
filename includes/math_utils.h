/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:56:28 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/15 17:10:19 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

# include "parser.h"
# include <stdbool.h>

typedef struct	s_ray {
	t_vec3	origin;
	t_vec3	direction;
} t_ray;

typedef struct s_sphere_i
{
	t_vec3  oc;
	double  a;
	double  b;
	double  c;
	double 	discriminant;
	double 	sqrt_d;
	double 	t0;
	double 	t1;
	bool	valid;
} t_sphere_i;

typedef struct s_plane_i
{
	t_vec3	point_to_origin;
	double	denom;
	double	t;
	bool	valid;
}	t_plane_i;

typedef struct s_cyl_i {
	t_vec3	oc;
	t_vec3	d_proj;
	t_vec3	oc_proj;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t0;
	double	t1;
	bool	valid;
}	t_cyl_i;

// vec3_add_sub.c
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub(t_vec3 a, t_vec3 b);

// vec3_dot_cross.c
double	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_cross(t_vec3 a, t_vec3 b);

// vec3_scalar_normal.c
t_vec3	vec3_scale(t_vec3 v, double scalar);
t_vec3	vec3_normalize(t_vec3 v);

// ray.c
t_ray	create_ray(t_vec3 origin, t_vec3 direction);
t_vec3	ray_at(t_ray ray, double t);

// intersect_plane.c
bool    intersect_plane(t_ray ray, t_plane *plane, double *t);

// intersect_sphere.c
bool    intersect_sphere(t_ray ray, t_sphere *sphere, double *t);

// intercect_cylinder.c
bool intersect_cylinder(t_ray ray, t_cylinder *cylinder, double *t);

// intersect_utils.c
bool	min_pos(double t0, double t1, double *t);

#endif