/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:49:06 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 21:34:14 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/miniRT.h"
#include "../../includes/math_utils.h"

static int	validate_camera_params(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (ft_printf("Error: Missing parameters for Camera\n"), 0);
	scene->camera.position = parse_vec3(tokens[1]);
	scene->camera.orientation = parse_vec3(tokens[2]);
	if (vec3_length(scene->camera.orientation) == 0.0)
	{
		ft_printf("Error: Camera orientation vector cannot be zero\n");
		return (0);
	}
	if (!check_vec3_range(scene->camera.orientation, -1.0, 1.0))
	{
		ft_printf("Error: Camera orientation vector out of range [-1,1]\n");
		return (0);
	}
	scene->camera.orientation = vec3_normalize(scene->camera.orientation);
	scene->camera.fov = ft_atof(tokens[3]);
	if (scene->camera.fov <= 0 || scene->camera.fov >= 180)
	{
		ft_printf("Error: Camera FOV out of range [0, 180]: %f\n",
			scene->camera.fov);
		return (0);
	}
	return (1);
}

int	handle_camera(char **tokens, t_scene *scene)
{
	if (get_camera_count(0) > 1)
	{
		ft_printf("Error: Multiple cameras detected\n");
		return (0);
	}
	return (validate_camera_params(tokens, scene));
}
