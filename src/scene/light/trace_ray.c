/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:05:31 by pshcherb          #+#    #+#             */
/*   Updated: 2025/07/21 14:49:05 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"

// Вычисляет нормаль (перпендикуляр) к боковой поверхности цилиндра в точке пересечения
t_vec3	get_cylinder_normal(t_cylinder *cy, t_vec3 hit)
{
	t_vec3 from_base;// Вектор от основания цилиндра до точки попадания луча
	double proj;// Проекция этого вектора на ось цилиндра
	t_vec3 proj_vec;// Вектор вдоль оси цилиндра, длиной как проекция

	from_base = vec3_sub(hit, cy->base);
	proj = vec3_dot(from_base, cy->direction);
	proj_vec = vec3_scale(cy->direction, proj);
	// Вычитаем проекцию из вектора from_base, чтобы получить нормаль к поверхности
	return (vec3_normalize(vec3_sub(from_base, proj_vec)));
}

// Проверяет пересечение луча со всеми цилиндрами в сцене
void    trace_cylinders(t_color *color, double *closest, t_ray ray, t_scene *scene)
{
	t_cylinder *cy;
	t_vec3  hit_point;
	t_vec3  normal;
	double  t;

	cy = scene->cylinders;
	while (cy)
	{// Если луч пересекает цилиндр и это пересечение ближе предыдущего
		if (intersect_cylinder(ray, cy, &t) && t < *closest)
		{
			hit_point = ray_at(ray, t);// Точка пересечения
			normal = get_cylinder_normal(cy, hit_point);// Нормаль в этой точке
			*color = compute_lighting(hit_point, normal, cy->color, scene);// Освещение
			*closest = t;// Запоминаем расстояние
		}
		cy = cy->next;
	}
}

// Проверяет пересечение луча со всеми плоскостями в сцене
void    trace_plane(t_color *color, double *closest, t_ray ray, t_scene *scene)
{
	t_plane *pl;
	t_vec3  hit_point;
	t_vec3  normal;
	double  t;

	pl = scene->planes;
	while (pl)
	{// Если луч пересекает плоскость и она ближе предыдущей
		if (intersect_plane(ray, pl, &t) && t < *closest)
		{
			hit_point = ray_at(ray, t);// Точка пересечения
			normal = pl->normal;// Нормаль заранее задана
			*color = compute_lighting(hit_point, normal, pl->color, scene);// Освещение
			*closest = t;// Запоминаем расстояние
		}
		pl = pl->next;
	}
}

// Проверяет пересечение луча со всеми сферами в сцене
void    trace_sphere(t_color *color, double *closest, t_ray ray, t_scene *scene)
{
	t_sphere *sp;
	double  t;
	t_vec3  hit_point;
	t_vec3  normal;

	sp = scene->spheres;
	while (sp)
	{// Если луч пересекает сферу и она ближе предыдущей
		if (intersect_sphere(ray, sp, &t) && t < *closest)
		{
			hit_point = ray_at(ray, t);// Точка пересечения
			// Нормаль — направление от центра сферы к точке пересечения
			normal = vec3_normalize(vec3_sub(hit_point, sp->center));
			*color = compute_lighting(hit_point, normal, sp->color, scene);// Освещение
			*closest = t;
		}
		sp = sp->next;
	}
}

// Основная функция: ищет ближайший объект, с которым пересекается луч, и возвращает его цвет
t_color trace_ray(t_ray ray, t_scene *scene)
{
	t_color color;
	double  closest;

	closest = 1e30;// Очень большое число — считаем, что ничего не найдено
	color = (t_color){0, 0, 0};// Цвет по умолчанию — чёрный (фон)
	trace_sphere(&color, &closest, ray, scene);// Проверка пересечений со всеми типами объектов
	trace_plane(&color, &closest, ray, scene);
	trace_cylinders(&color, &closest, ray, scene);
	return (color);// Цвет ближайшего объекта (если найден)
}