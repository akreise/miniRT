/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_calculation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:48:07 by pshcherb          #+#    #+#             */
/*   Updated: 2025/07/23 15:52:57 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

// Вычисляет итоговый цвет в точке пересечения с учётом освещения: Ambient + Diffuse освещение
// hit_point — точка пересечения луча и объекта
// normal — нормаль в точке пересечения
// obj_color — цвет объекта
// scene — сцена (включает источник света и ambient)
t_color	compute_lighting(t_vec3 hit_point, t_vec3 normal, t_color obj_color,
						 t_scene *scene)
{
	t_light_c	l;

	// Ambient lighting: масштабируем ambient color сцены по коэффициенту
	t_color ambient_color = color_mul(obj_color, scene->ambient.color);
	l.ambient = color_scale(ambient_color, scene->ambient.ratio);
	l.diffuse_total = (t_color){0, 0, 0};// Начальное значение для диффузного освещения — чёрный
	l.light = scene->lights;// Проходим по всем источникам света
	while (l.light)
	{// Вычисляем направление от точки к источнику света
		l.light_dir = vec3_sub(l.light->position, hit_point);
		l.light_dir = vec3_normalize(l.light_dir);
		//Скалярное произведение нормали и направления света
		// Если < 0 — свет падает с обратной стороны и не освещает
		l.dot = vec3_dot(normal, l.light_dir);
		if (l.dot > 0)
		{// Яркость зависит от угла: чем ближе к 0°, тем сильнее
			l.intensity = l.light->brightness * l.dot;
			l.diffuse = color_scale(obj_color, l.intensity);// Масштабируем цвет объекта по интенсивности
			l.diffuse_total = color_add(l.diffuse_total, l.diffuse);// Добавляем к общему диффузному свету
		}
		l.light = l.light->next;// Следующий источник света
	}
	return (color_add(l.ambient, l.diffuse_total));// Возвращаем сумму ambient + diffuse как итоговый цвет
}
