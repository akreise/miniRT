/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lighting.c                                   :+:      :+:    :+:   */
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

int	check_ambient(t_ambient *ambient)
{
	if (!check_ratio_range(ambient->ratio))
		return (0);
	if (!check_rgb_range(&ambient->color))
		return (0);
	return (1);
}

int	check_light(t_light *light)
{
	if (!check_ratio_range(light->brightness))
		return (0);
	if (!check_rgb_range(&light->color))
		return (0);
	return (1);
}

int	check_camera_properties(t_camera *camera)
{
	double	norm_squared;

	norm_squared = vec3_dot(camera->orientation, camera->orientation);
	if (norm_squared < 0.9 || norm_squared > 1.1)
		return (0);
	if (!check_fov_range(camera->fov))
		return (0);
	return (1);
}

int	check_camera(t_camera *camera)
{
	if (!check_camera_properties(camera))
		return (0);
	return (1);
}
