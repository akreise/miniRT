/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:27:13 by pshcherb          #+#    #+#             */
/*   Updated: 2025/07/19 19:48:41 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h"

// Функция создания луча
t_ray	create_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	// Начальная точка луча (камера или точка наблюдения)
	ray.origin = origin;
	// Направление нормализуется (приводится к длине 1), чтобы корректно работать с пересечениями
	ray.direction = vec3_normalize(direction);
	return (ray);// Возвращаем луч
}

// Функция для вычисления точки на луче на расстоянии t от начала
t_vec3	ray_at(t_ray ray, double t)
{
	// Вычисляем точку на луче по формуле:
	// P(t) = origin + direction * t
	return (vec3_add(ray.origin, vec3_scale(ray.direction, t)));
}
