/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_factor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:00:00 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 20:30:19 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

double	shadow_factor(t_vec3 point, t_light *light, t_scene *scene)
{
	int		i;
	int		blocked;
	int		samples;
	double	shadow_val;

	blocked = 0;
	samples = 32;
	i = 0;
	while (i < samples)
	{
		shadow_val = calculate_sample_shadow(point, light, scene);
		blocked += (int)shadow_val;
		i++;
	}
	return (1.0 - ((double)blocked / samples));
}
