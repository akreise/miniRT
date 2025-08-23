/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:22:22 by akreise           #+#    #+#             */
/*   Updated: 2025/08/23 18:37:03 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../mlx/minilibx-linux/mlx.h"
#include "../../includes/math_utils.h"
#include "../../includes/scene.h"
#include "../../includes/miniRT.h"
#include "../../includes/render.h"
#include <stdio.h>
#include <stdlib.h>

int	check_spheres(t_sphere *spheres)
{
	t_sphere	*current;

	current = spheres;
	while (current)
	{
		if (!check_sphere(current))
			return (0);
		current = current->next;
	}
	return (1);
}

int	check_planes(t_plane *planes)
{
	t_plane	*current;

	current = planes;
	while (current)
	{
		if (!check_plane(current))
			return (0);
		current = current->next;
	}
	return (1);
}

int	check_cylinders(t_cylinder *cylinders)
{
	t_cylinder	*current;

	current = cylinders;
	while (current)
	{
		if (!check_cylinder(current))
			return (0);
		current = current->next;
	}
	return (1);
}

int	check_scene(t_scene *scene)
{
	if (!check_ambient(&scene->ambient))
		return (0);
	if (!check_light(scene->lights))
		return (0);
	if (!check_camera(&scene->camera))
		return (0);
	if (!check_spheres(scene->spheres))
		return (0);
	if (!check_planes(scene->planes))
		return (0);
	if (!check_cylinders(scene->cylinders))
		return (0);
	return (1);
}
