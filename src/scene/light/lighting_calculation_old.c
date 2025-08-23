/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_calculation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:48:07 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 20:14:25 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

static t_color	calculate_specular(t_vec3 light_dir, t_vec3 normal,
	t_vec3 view_dir, t_light *light, double specular, double shadow)
{
	t_vec3	reflect_dir;
	double	spec;
	t_color	specular_color;

	reflect_dir = reflect(vec3_scale(light_dir, -1), normal);
	spec = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), specular);
	specular_color = color_scale(light->color, light->brightness * spec * shadow);
	return (specular_color);
}

static t_color	process_light(t_light *light, t_vec3 hit_point, t_vec3 normal,
	t_color obj_color, double specular, t_scene *scene, t_vec3 view_dir)
{
	t_vec3	light_dir;
	double	dot;
	double	shadow;
	double	intensity;
	t_color	diffuse;
	t_color	result;

	light_dir = vec3_sub(light->position, hit_point);
	light_dir = vec3_normalize(light_dir);
	dot = vec3_dot(normal, light_dir);
	result = (t_color){0, 0, 0};
	if (dot > 0)
	{
		shadow = shadow_factor(hit_point, light, scene);
		if (shadow > 0)
		{
			intensity = light->brightness * dot * shadow;
			diffuse = color_scale(obj_color, intensity);
			result = color_add(result, diffuse);
			if (specular > 0)
				result = color_add(result, calculate_specular(light_dir,
						normal, view_dir, light, specular, shadow));
		}
	}
	return (result);
}

t_color	compute_lighting(t_vec3 hit_point, t_vec3 normal, t_color obj_color,
	double specular, t_scene *scene, t_vec3 camera_pos)
{
	t_color	ambient_color;
	t_color	ambient;
	t_color	diffuse_total;
	t_vec3	view_dir;
	t_light	*light;

	ambient_color = color_mul(obj_color, scene->ambient.color);
	ambient = color_scale(ambient_color, scene->ambient.ratio);
	diffuse_total = (t_color){0, 0, 0};
	view_dir = vec3_normalize(vec3_sub(camera_pos, hit_point));
	light = scene->lights;
	while (light)
	{
		diffuse_total = color_add(diffuse_total, process_light(light,
				hit_point, normal, obj_color, specular, scene, view_dir));
		light = light->next;
	}
	return (color_add(ambient, diffuse_total));
}

static bool	check_sphere_shadow(t_scene *scene, t_ray shadow_ray,
	double light_dist, double *t)
{
	t_sphere	*sp;

	sp = scene->spheres;
	while (sp)
	{
		if (intersect_sphere(shadow_ray, sp, t) && *t > 1e-4 && *t < light_dist)
			return (true);
		sp = sp->next;
	}
	return (false);
}

static bool	check_plane_shadow(t_scene *scene, t_ray shadow_ray,
	double light_dist, double *t)
{
	t_plane	*pl;

	pl = scene->planes;
	while (pl)
	{
		if (intersect_plane(shadow_ray, pl, t) && *t > 1e-4 && *t < light_dist)
			return (true);
		pl = pl->next;
	}
	return (false);
}

static bool	check_cylinder_shadow(t_scene *scene, t_ray shadow_ray,
	double light_dist, double *t)
{
	t_cylinder	*cy;

	cy = scene->cylinders;
	while (cy)
	{
		if (intersect_cylinder(shadow_ray, cy, t) && *t > 1e-4 && *t < light_dist)
			return (true);
		cy = cy->next;
	}
	return (false);
}

static bool	is_in_shadow(t_scene *scene, t_ray shadow_ray, double light_dist)
{
	double	t;

	if (check_sphere_shadow(scene, shadow_ray, light_dist, &t))
		return (true);
	if (check_plane_shadow(scene, shadow_ray, light_dist, &t))
		return (true);
	if (check_cylinder_shadow(scene, shadow_ray, light_dist, &t))
		return (true);
	return (false);
}

static double	calculate_sample_shadow(t_vec3 point, t_light *light,
	t_scene *scene, int i)
{
	t_vec3	offset;
	t_vec3	offset3d;
	t_vec3	perturbed_light;
	t_vec3	to_perturbed;
	double	light_dist;
	t_vec3	dir;
	t_ray	shadow_ray;

	(void)i;
	offset = random_in_unit_disk();
	offset3d.x = offset.x * 0.5;
	offset3d.y = offset.y * 0.5;
	offset3d.z = 0;
	perturbed_light = vec3_add(light->position, offset3d);
	to_perturbed = vec3_sub(perturbed_light, point);
	light_dist = vec3_length(to_perturbed);
	dir = vec3_normalize(to_perturbed);
	shadow_ray = create_ray(vec3_add(point, vec3_scale(dir, 1e-4)), dir);
	if (is_in_shadow(scene, shadow_ray, light_dist))
		return (1.0);
	return (0.0);
}

double	shadow_factor(t_vec3 point, t_light *light, t_scene *scene)
{
	int		i;
	int		blocked;
	int		samples;
	double	shadow_total;

	blocked = 0;
	samples = 32;
	i = 0;
	while (i < samples)
	{
		shadow_total = calculate_sample_shadow(point, light, scene, i);
		blocked += (int)shadow_total;
		i++;
	}
	return (1.0 - ((double)blocked / samples));
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
