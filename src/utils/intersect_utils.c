/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:21:20 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 19:33:23 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h"

bool	min_pos(double t0, double t1, double *t)
{
	if (t0 > 0.001 && t1 > 0.001)
	{
		if (t0 < t1)
			*t = t0;
		else
			*t = t1;
	}
	else if (t0 > 0.001)
		*t = t0;
	else if (t1 > 0.001)
		*t = t1;
	else
		return (false);
	return (true);
}

t_vec3	reflect(t_vec3 incident, t_vec3 normal)
{
	t_vec3	result;

	result = vec3_scale(normal, 2 * vec3_dot(incident, normal));
	return (vec3_sub(incident, result));
}
