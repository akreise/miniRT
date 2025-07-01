/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_scalar_normal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:28:41 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/16 16:21:39 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h"

double	vec3_length(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	vec3_scale(t_vec3 v, double scalar)
{
	return ((t_vec3){
		v.x * scalar,
		v.y * scalar,
		v.z * scalar
	});
}

t_vec3	vec3_normalize(t_vec3 v)
{
	double	length;

	length = vec3_length(v);
	if (length == 0)
		return ((t_vec3){0, 0, 0});
	return (vec3_scale(v, 1.0 / length));
}
