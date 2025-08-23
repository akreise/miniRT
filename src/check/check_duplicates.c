/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_duplicates.c                                 :+:      :+:    :+:   */
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

int	count_lights(t_light *lights)
{
	int		count;
	t_light	*current;

	count = 0;
	current = lights;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	check_required_elements(t_scene *scene)
{
	int	light_count;

	light_count = count_lights(scene->lights);
	if (light_count != 1)
	{
		printf("Error: Scene must have exactly one light (L)\n");
		return (0);
	}
	return (1);
}

int	validate_single_elements(t_app *app)
{
	if (app->ambient_count != 1)
	{
		printf("Error: Scene must have exactly one ambient light (A)\n");
		return (0);
	}
	if (app->camera_count != 1)
	{
		printf("Error: Scene must have exactly one camera (C)\n");
		return (0);
	}
	if (app->light_count != 1)
	{
		printf("Error: Scene must have exactly one light (L)\n");
		return (0);
	}
	return (1);
}

int	validate_parsed_scene(t_scene *scene)
{
	if (!check_required_elements(scene))
		return (0);
	if (!check_scene(scene))
		return (0);
	return (1);
}

int	validate_line_tokens(char **tokens)
{
	int	count;

	if (!tokens)
		return (0);
	count = 0;
	while (tokens[count])
		count++;
	if (count < 2)
		return (0);
	return (1);
}
