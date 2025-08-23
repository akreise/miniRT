/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
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

static int	validate_light_params(char **tokens, t_light *light)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (ft_printf("Error: Missing parameters for Light\n"), 0);
	light->position = parse_vec3(tokens[1]);
	light->brightness = ft_atof(tokens[2]);
	if (!parse_color(tokens[3], &light->color))
		return (0);
	if (light->brightness < 0.0 || light->brightness > 1.0)
	{
		ft_printf("Error: Light brightness out of range [0.0, 1.0]: %f\n",
			light->brightness);
		return (0);
	}
	return (1);
}

int	handle_light(char **tokens, t_scene *scene)
{
	t_light	*light;

	if (get_light_count(0) > 1)
	{
		ft_printf("Error: Multiple lights detected\n");
		return (0);
	}
	light = malloc(sizeof(t_light));
	if (!light)
		return (ft_printf("Error: Memory allocation failed for Light\n"), 0);
	if (!validate_light_params(tokens, light))
	{
		free(light);
		return (0);
	}
	light->next = scene->lights;
	scene->lights = light;
	return (1);
}
