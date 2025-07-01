/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_combine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:42:09 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/16 14:05:37 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

t_color	color_scale(t_color color, double factor)
{
	t_color	result;

	result.r = fmin(color.r * factor, 255);
	result.g = fmin(color.g * factor, 255);
	result.b = fmin(color.b * factor, 255);
	return (result);
}

t_color	color_add(t_color a, t_color b)
{
	t_color	result;

	result.r = fmin(a.r + b.r, 255);
	result.g = fmin(a.g + b.g, 255);
	result.b = fmin(a.b + b.b, 255);
	return (result); 
}