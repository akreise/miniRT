/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:05:31 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/03 17:18:41 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"
#include "../../../includes/math_utils.h"
#define MAX_DEPTH 5

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
void    trace_cylinder(t_color *color, double *closest, t_ray ray, t_scene *scene, int depth)
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
			t_color local_color = compute_lighting(hit_point, normal, cy->color, cy->specular, scene, scene->camera.position);// Освещение
			if (cy->reflectivity > 0)
			{
				t_vec3 reflected_dir = vec3_normalize(reflect(ray.direction, normal));
				t_ray reflected_ray = create_ray(vec3_add(hit_point, vec3_scale(normal, 1e-4)), reflected_dir);

				t_color reflected_color = trace_ray(reflected_ray, scene, depth + 1);
				local_color = color_blend(local_color, reflected_color, cy->reflectivity);
			}
			*color = local_color;
			*closest = t;// Запоминаем расстояние
		}
		cy = cy->next;
	}
}

// Проверяет пересечение луча со всеми плоскостями в сцене
void    trace_plane(t_color *color, double *closest, t_ray ray, t_scene *scene, int depth)
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
			t_color local_color = compute_lighting(hit_point, normal, pl->color, pl->specular, scene, scene->camera.position);// Освещение
			if (pl->reflectivity > 0)
			{
				t_vec3 reflected_dir = vec3_normalize(reflect(ray.direction, normal));
				t_ray reflected_ray = create_ray(vec3_add(hit_point, vec3_scale(normal, 1e-4)), reflected_dir);

				t_color reflected_color = trace_ray(reflected_ray, scene, depth + 1);
				local_color = color_blend(local_color, reflected_color, pl->reflectivity);
			}
			*color = local_color;
			*closest = t;// Запоминаем расстояние
		}
		pl = pl->next;
	}
}

// Проверяет пересечение луча со всеми сферами в сцене
void    trace_sphere(t_color *color, double *closest, t_ray ray, t_scene *scene, int depth)
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
			t_color local_color = compute_lighting(hit_point, normal, sp->color, sp->specular, scene, scene->camera.position);
			if (sp->reflectivity > 0)
			{
				t_vec3 reflected_dir = vec3_normalize(reflect(ray.direction, normal));
				t_ray reflected_ray = create_ray(vec3_add(hit_point, vec3_scale(normal, 1e-4)), reflected_dir);

				t_color reflected_color = trace_ray(reflected_ray, scene, depth + 1);
				local_color = color_blend(local_color, reflected_color, sp->reflectivity);
			}
			*color = local_color;
			*closest = t;
		}
		sp = sp->next;
	}
}

static t_color color_black(void)
{
	return ((t_color){0,0,0});
}
// Основная функция: ищет ближайший объект, с которым пересекается луч, и возвращает его цвет
t_color trace_ray(t_ray ray, t_scene *scene, int depth)
{
	if (depth > MAX_DEPTH)
        return color_black();

    // Инициализация результата и *closest
    t_color color = color_black();
    double closest = INFINITY;

    trace_sphere(&color, &closest, ray, scene, depth);
    trace_cylinder(&color, &closest, ray, scene, depth);
    trace_plane(&color, &closest, ray, scene, depth);

    return color;

}

t_color trace_ray_recursive(t_ray ray, t_scene *scene, int depth)
{
	if (depth <= 0)
		return (t_color){0, 0, 0};

	t_color color = {0, 0, 0};
	double closest = 1e30;

	// Аналог trace_sphere/plane/cylinder, но каждый должен вызывать:
	// trace_ray_recursive(..., depth - 1) для отражения

	trace_sphere(&color, &closest, ray, scene, depth - 1);
	trace_plane(&color, &closest, ray, scene, depth - 1);
	trace_cylinder(&color, &closest, ray, scene, depth - 1);

	return color;
}


t_color color_blend(t_color c1, t_color c2, double factor)
{
	t_color result;

	result.r = c1.r * (1 - factor) + c2.r * factor;
	result.g = c1.g * (1 - factor) + c2.g * factor;
	result.b = c1.b * (1 - factor) + c2.b * factor;
	return result;
}
