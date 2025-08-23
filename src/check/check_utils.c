/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
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

int	check_file_exists(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	check_rgb_range(t_color *color)
{
	if (color->r < 0 || color->r > 255)
		return (0);
	if (color->g < 0 || color->g > 255)
		return (0);
	if (color->b < 0 || color->b > 255)
		return (0);
	return (1);
}

int	check_ratio_range(double ratio)
{
	if (ratio < 0.0 || ratio > 1.0)
		return (0);
	return (1);
}

int	check_fov_range(int fov)
{
	if (fov < 0 || fov > 180)
		return (0);
	return (1);
}

int	check_vec3_range(t_vec3 v, double min, double max)
{
	if (v.x < min || v.x > max)
		return (0);
	if (v.y < min || v.y > max)
		return (0);
	if (v.z < min || v.z > max)
		return (0);
	return (1);
}
