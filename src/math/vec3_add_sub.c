/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_add_sub.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 14:14:48 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/15 17:11:34 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h"

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	});
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	});
}
