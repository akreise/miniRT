/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:51:05 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 18:55:44 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/miniRT.h"
#include "../../includes/math_utils.h"

static void	set_sphere_reflectivity(char **tokens, t_sphere *sphere)
{
	if (tokens[4])
	{
		sphere->reflectivity = ft_atof(tokens[4]);
		if (tokens[5])
			sphere->specular = ft_atof(tokens[5]);
		else
			sphere->specular = 0;
	}
	else
	{
		sphere->reflectivity = 0.0;
		sphere->specular = 0;
	}
}

int	handle_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sphere;

	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (ft_printf("Error: Missing parameters for Sphere\n"), 0);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (ft_printf("Error: Memory allocation failed for Sphere\n"), 0);
	sphere->center = parse_vec3(tokens[1]);
	sphere->radius = ft_atof(tokens[2]) / 2.0;
	if (!parse_color(tokens[3], &sphere->color))
	{
		free(sphere);
		return (0);
	}
	set_sphere_reflectivity(tokens, sphere);
	if (sphere->radius <= 0.0)
	{
		ft_printf("Error: Invalid diameter: %f\n", sphere->radius * 2);
		free(sphere);
		return (0);
	}
	sphere->next = scene->spheres;
	scene->spheres = sphere;
	return (1);
}

static void	set_plane_reflectivity(char **tokens, t_plane *plane)
{
	if (tokens[4])
	{
		plane->reflectivity = ft_atof(tokens[4]);
		if (tokens[5])
			plane->specular = ft_atof(tokens[5]);
		else
			plane->specular = 0;
	}
	else
	{
		plane->reflectivity = 0.0;
		plane->specular = 0;
	}
}

static int	validate_plane_normal(t_plane *plane)
{
	if (vec3_length(plane->normal) == 0.0)
	{
		ft_printf("Error: Plane normal vector cannot be zero\n");
		return (0);
	}
	if (!check_vec3_range(plane->normal, -1.0, 1.0))
	{
		ft_printf("Error: Plane normal vector out of range [-1,1]\n");
		return (0);
	}
	plane->normal = vec3_normalize(plane->normal);
	return (1);
}

int	handle_plane(char **tokens, t_scene *scene)
{
	t_plane	*plane;

	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (ft_printf("Error: Missing parameters for Plane"), 0);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (ft_printf("Error: Memory allocation failed for Plane"), 0);
	plane->point = parse_vec3(tokens[1]);
	plane->normal = parse_vec3(tokens[2]);
	if (!validate_plane_normal(plane))
	{
		free(plane);
		return (0);
	}
	if (!parse_color(tokens[3], &plane->color))
	{
		free(plane);
		return (0);
	}
	set_plane_reflectivity(tokens, plane);
	plane->next = scene->planes;
	scene->planes = plane;
	return (1);
}
