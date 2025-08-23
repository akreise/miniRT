/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_utils.c                              :+:      :+:    :+:   */
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

int	get_ambient_count(int reset)
{
	static int	count = 0;

	if (reset)
	{
		count = 0;
		return (count);
	}
	return (++count);
}

int	get_camera_count(int reset)
{
	static int	count = 0;

	if (reset)
	{
		count = 0;
		return (count);
	}
	return (++count);
}

int	get_light_count(int reset)
{
	static int	count = 0;

	if (reset)
	{
		count = 0;
		return (count);
	}
	return (++count);
}

void	reset_element_counters(void)
{
	get_ambient_count(1);
	get_camera_count(1);
	get_light_count(1);
}

int	validate_ambient_params(char **tokens, double *ratio, t_color *color)
{
	if (!tokens[1] || !tokens[2])
		return (ft_printf("Error: Missing parameters for Ambient light\n"), 0);
	*ratio = ft_atof(tokens[1]);
	if (*ratio < 0.0 || *ratio > 1.0)
	{
		ft_printf("Error: Ambient light ratio out of range [0.0, 1.0]\n");
		return (0);
	}
	if (!parse_color(tokens[2], color))
		return (0);
	return (1);
}
