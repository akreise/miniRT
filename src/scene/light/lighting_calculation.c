/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_calculation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:48:07 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/02 12:28:18 by pshcherb         ###   ########.fr       */
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
		{
			double shadow = shadow_factor(hit_point, l.light, scene);
			// Проверка на тень
			if (shadow > 0)
			{
				l.intensity = l.light->brightness * l.dot * shadow;
				l.diffuse = color_scale(obj_color, l.intensity);
				l.diffuse_total = color_add(l.diffuse_total, l.diffuse);
			}
		}
		l.light = l.light->next;// Следующий источник света
	}
	return (color_add(l.ambient, l.diffuse_total));// Возвращаем сумму ambient + diffuse как итоговый цвет
}

double shadow_factor(t_vec3 point, t_light *light, t_scene *scene)
{
	int blocked = 0;
	int samples = 32; // Чем больше, тем мягче (но медленнее)
	double radius = 0.5; // Размер источника света

	for (int i = 0; i < samples; i++)
	{
		// Смещаем точку света немного случайно
		t_vec3 offset = random_in_unit_disk();
		t_vec3 offset3d = {
			offset.x * radius,
			offset.y * radius,
			0
		};
		t_vec3 perturbed_light = vec3_add(light->position, offset3d);

		t_vec3 to_perturbed = vec3_sub(perturbed_light, point);
		double light_dist = vec3_length(to_perturbed);
		t_vec3 dir = vec3_normalize(to_perturbed);

		t_ray shadow_ray = create_ray(vec3_add(point, vec3_scale(dir, 1e-4)), dir);
		double t;

		bool in_shadow = false;

		// Проверка на пересечение с любым объектом
		for (t_sphere *sp = scene->spheres; sp; sp = sp->next)
			if (intersect_sphere(shadow_ray, sp, &t) && t > 1e-4 && t < light_dist)
				in_shadow = true;
		for (t_plane *pl = scene->planes; pl; pl = pl->next)
			if (intersect_plane(shadow_ray, pl, &t) && t > 1e-4 && t < light_dist)
				in_shadow = true;
		for (t_cylinder *cy = scene->cylinders; cy; cy = cy->next)
			if (intersect_cylinder(shadow_ray, cy, &t) && t > 1e-4 && t < light_dist)
				in_shadow = true;

		if (in_shadow)
			blocked++;
	}

	return 1.0 - ((double)blocked / samples); // 1.0 — полностью освещён, 0.0 — полностью в тени
}

t_vec3 random_in_unit_disk(void)
{
	t_vec3 p;
	do {
		p.x = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
		p.y = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
		p.z = 0;
	} while (vec3_dot(p, p) >= 1.0);
	return p;
}

