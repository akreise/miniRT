/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
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

int	check_sphere(t_sphere *sphere)
{
	if (sphere->radius <= 0.0)
		return (0);
	if (!check_rgb_range(&sphere->color))
		return (0);
	return (1);
}

int	check_plane(t_plane *plane)
{
	double	norm_squared;

	norm_squared = vec3_dot(plane->normal, plane->normal);
	if (norm_squared < 0.9 || norm_squared > 1.1)
		return (0);
	if (!check_rgb_range(&plane->color))
		return (0);
	return (1);
}

int	check_cylinder_properties(t_cylinder *cylinder)
{
	double	norm_squared;

	if (cylinder->radius <= 0.0)
		return (0);
	if (cylinder->height <= 0.0)
		return (0);
	norm_squared = vec3_dot(cylinder->direction, cylinder->direction);
	if (norm_squared < 0.9 || norm_squared > 1.1)
		return (0);
	return (1);
}

int	check_cylinder(t_cylinder *cylinder)
{
	if (!check_cylinder_properties(cylinder))
		return (0);
	if (!check_rgb_range(&cylinder->color))
		return (0);
	return (1);
}
