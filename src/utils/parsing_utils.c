/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:58:30 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/15 17:10:22 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

double	vec3_length(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

int	is_valid_color_value(int value)
{
	return (value >= 0 && value <= 255);
}

t_vec3	parse_vec3(char *str)
{
	t_vec3		vec3;
	char		**values;

	values = ft_split(str, ',');
	if (!values[0] || !values[1] || !values[2] || values[3])
	{
		ft_printf("Error: Invalid vector format: %s\n", str);
		free_tokens(values);
		return ((t_vec3){0, 0, 0});
	}
	vec3.x = ft_atof(values[0]);
	vec3.y = ft_atof(values[1]);
	vec3.z = ft_atof(values[2]);
	free_tokens(values);
	return (vec3);
}

t_color	parse_color(char *str)
{
	t_color		color;
	char		**values;

	values = ft_split(str, ',');
	if (!values[0] || !values[1] || !values[2])
	{
		ft_printf("Error: Invalid color format: %s\n", str);
		free_tokens(values);
		return ((t_color){0, 0, 0});
	}
	color.r = ft_atoi(values[0]);
	color.g = ft_atoi(values[1]);
	color.b = ft_atoi(values[2]);
	if (!is_valid_color_value(color.r) || !is_valid_color_value(color.g)
		|| !is_valid_color_value(color.b))
	{
		ft_printf("Error: Color values out of range (0-255): %s\n", str);
		color = (t_color){0, 0, 0};
	}
	free_tokens(values);
	return (color);
}
