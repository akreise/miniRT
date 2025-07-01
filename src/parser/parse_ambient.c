/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:49:06 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/12 13:01:42 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	handle_ambient(char **tokens, t_scene *scene)
{
	double	ratio;
	t_color	color;

	if (!tokens[1] || !tokens[2])
		return (ft_printf("Error: Missing parameters for Ambient light\n"), 0);
	ratio = ft_atof(tokens[1]);
	if (ratio < 0.0 || ratio > 1.0)
	{
		ft_printf("Error: Ambient light ratio out of range [0.0, 1.0]: %f\n",
			ratio);
		return (0);
	}
	color = parse_color(tokens[2]);
	if (color.r == 0 && color.g == 0 && color.b == 0)
		return (ft_printf("Error: Failed to parse color for Ambient light\n"),
			0);
	scene->ambient.ratio = ratio;
	scene->ambient.color = color;
	return (1);
}

int	handle_camera(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (ft_printf("Error: Missing parameters for Camera\n"), 0);
	scene->camera.position = parse_vec3(tokens[1]);
	scene->camera.orientation = parse_vec3(tokens[2]);
	if (fabs(vec3_length(scene->camera.orientation) - 1.0) > 0.001)
	{
		ft_printf("Error: Camera orientation vector is not normalized");
		return (0);
	}
	scene->camera.fov = ft_atof(tokens[3]);
	if (scene->camera.fov <= 0 || scene->camera.fov >= 180)
	{
		ft_printf("Error: Camera FOV out of range [0, 180]: %f\n",
			scene->camera.fov);
		return (0);
	}
	return (1);
}

int	handle_light(char **tokens, t_scene *scene)
{
	t_light	*light;

	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (ft_printf("Error: Missing parameters for Light\n"), 0);
	light = malloc(sizeof(t_light));
	if (!light)
		return (ft_printf("Error: Memory allocation failed for Light\n"), 0);
	light->position = parse_vec3(tokens[1]);
	light->brightness = ft_atof(tokens[2]);
	light->color = parse_color(tokens[3]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
	{
		ft_printf("Error: Light brightness out of range [0.0, 1.0]: %f\n",
			light->brightness);
		free(light);
		return (0);
	}
	light->next = scene->lights;
	scene->lights = light;
	return (1);
}
