/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:51:05 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/12 13:00:58 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

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
	sphere->color = parse_color(tokens[3]);
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
	plane->color = parse_color(tokens[3]);
	if (fabs(vec3_length(plane->normal) - 1.0) > 0.001)
	{
		ft_printf("Error: Plane normal vector is not normalized\n");
		free(plane);
		return (0);
	}
	plane->next = scene->planes;
	scene->planes = plane;
	return (1);
}

static int	error_handling(t_cylinder *cylinder)
{
	if (fabs(vec3_length(cylinder->direction) - 1.0) > 0.001)
	{
		ft_printf("Error: Cylinder direction vector is not normalized\n");
		free(cylinder);
		return (0);
	}
	if (cylinder->radius <= 0.0 || cylinder->height <= 0.0)
	{
		ft_printf("Error: Cylinder dimensions are invalid\n");
		free(cylinder);
		return (0);
	}
	return (1);
}

int	handle_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cylinder;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
		return (ft_printf("Error: Missing parameters for Cylinder\n"), 0);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (ft_printf("Error: Memory allocation failed for Cylinder\n"), 0);
	cylinder->base = parse_vec3(tokens[1]);
	cylinder->direction = parse_vec3(tokens[2]);
	cylinder->radius = ft_atof(tokens[3]) / 2.0;
	cylinder->height = ft_atof(tokens[4]);
	cylinder->color = parse_color(tokens[5]);
	if (!error_handling(cylinder))
		return (0);
	cylinder->next = scene->cylinders;
	scene->cylinders = cylinder;
	return (1);
}
