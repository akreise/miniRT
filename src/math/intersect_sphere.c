/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:22:22 by pshcherb          #+#    #+#             */
/*   Updated: 2025/07/19 19:42:21 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/math_utils.h"

// вычисление параметров пересечения луча и сферы
// Вычисляет коэффициенты квадратного уравнения для пересечения луча и сферы
static	t_sphere_i	init_sphere_i(t_ray ray, t_sphere *sphere, t_sphere_i s)
{
	// Вектор от центра сферы до начала луча
	s.oc = vec3_sub(ray.origin, sphere->center);
	// Коэффициенты квадратного уравнения: at^2 + bt + c = 0
	s.a = vec3_dot(ray.direction, ray.direction);// a = D · D
	s.b = 2.0 * vec3_dot(s.oc, ray.direction);// b = 2 * (oc · D)
	s.c = vec3_dot(s.oc, s.oc) - (sphere->radius * sphere->radius);// c = oc · oc - R²
	s.discriminant = s.b * s.b - 4 * s.a * s.c;// Дискриминант квадратного уравнения
	if (s.discriminant < 0)// Если дискриминант < 0 — нет действительных корней => луч не пересекает сферу
	{
		s.valid = false;
		return (s);
	}
	s.valid = true;// Есть пересечение — вычисляем корни уравнения
	s.sqrt_d = sqrt(s.discriminant);
	// t0 и t1 — два решения (возможные расстояния до точек пересечения)
	s.t0 = (-s.b - s.sqrt_d) / (2.0 * s.a);
	s.t1 = (-s.b + s.sqrt_d) / (2.0 * s.a);
	return (s);
}

// Проверяет, пересекает ли луч заданную сферу
bool	intersect_sphere(t_ray ray, t_sphere *sphere, double *t)
{
	t_sphere_i	s;

	s = init_sphere_i(ray, sphere, s);// Сначала считаем всё, что нужно для пересечения
	if (!s.valid)// Если нет пересечения — возвращаем false
		return (false);
	// Есть два корня (t0 и t1) — выбираем минимальный положительный
	// и сохраняем его в *t
	return (min_pos(s.t0, s.t1, t));
}
