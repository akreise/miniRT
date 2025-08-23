/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:00:00 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 20:14:12 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/miniRT.h"
#include "../../includes/math_utils.h"

static int	parse_cylinder_params(char **tokens, t_cylinder *cylinder)
{
	cylinder->base = parse_vec3(tokens[1]);
	cylinder->direction = parse_vec3(tokens[2]);
	if (vec3_length(cylinder->direction) == 0.0)
	{
		ft_printf("Error: Cylinder direction vector cannot be zero\n");
		return (0);
	}
	if (!check_vec3_range(cylinder->direction, -1.0, 1.0))
	{
		ft_printf("Error: Cylinder direction vector out of range [-1,1]\n");
		return (0);
	}
	cylinder->direction = vec3_normalize(cylinder->direction);
	cylinder->radius = ft_atof(tokens[3]) / 2.0;
	cylinder->height = ft_atof(tokens[4]);
	if (!parse_color(tokens[5], &cylinder->color))
		return (0);
	return (1);
}

static void	set_cylinder_reflectivity(char **tokens, t_cylinder *cylinder)
{
	if (tokens[6])
	{
		cylinder->reflectivity = ft_atof(tokens[6]);
		if (tokens[7])
			cylinder->specular = ft_atof(tokens[7]);
		else
			cylinder->specular = 0;
	}
	else
	{
		cylinder->reflectivity = 0.0;
		cylinder->specular = 0;
	}
}

int	handle_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cylinder;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
		return (ft_printf("Error: Missing parameters for Cylinder\n"), 0);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (ft_printf("Error: Memory allocation failed"), 0);
	if (!parse_cylinder_params(tokens, cylinder))
	{
		free(cylinder);
		return (0);
	}
	set_cylinder_reflectivity(tokens, cylinder);
	if (cylinder->radius <= 0.0 || cylinder->height <= 0.0)
	{
		ft_printf("Error: Cylinder dimensions are invalid\n");
		free(cylinder);
		return (0);
	}
	cylinder->next = scene->cylinders;
	scene->cylinders = cylinder;
	return (1);
}
