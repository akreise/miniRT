/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:51:05 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/13 14:15:10 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/miniRT.h"
#include "../../includes/math_utils.h"

// Обрабатывает строку, описывающую сферу
// Формат: sp <center> <diameter> <color> Например: sp 0,0,0 10 255,0,0
// center — координаты центра (vec3)
// diameter — диаметр сферы, делим на 2, чтобы получить радиус
// color — цвет в RGB
int	handle_sphere(char **tokens, t_scene *scene)
{
	t_sphere	*sphere;

	if (!tokens[1] || !tokens[2] || !tokens[3])// Проверка на наличие всех трёх параметров
		return (ft_printf("Error: Missing parameters for Sphere\n"), 0);
	sphere = malloc(sizeof(t_sphere));// Выделение памяти под сферу
	if (!sphere)
		return (ft_printf("Error: Memory allocation failed for Sphere\n"), 0);
	sphere->center = parse_vec3(tokens[1]);// Парсим параметры
	sphere->radius = ft_atof(tokens[2]) / 2.0;// Диаметр делим на 2
	if (!parse_color(tokens[3], &sphere->color))
	{
    	free(sphere);
    	return (0); // выходим с ошибкой
	}
	if (tokens[4])
	{
		sphere->reflectivity = ft_atof(tokens[4]);
		if (tokens[5])
			sphere->specular = ft_atof(tokens[5]);
		else
			sphere->specular = 0;
	}
	else
	{
		sphere->reflectivity = 0.0;
		sphere->specular = 0;
	}
	if (sphere->radius <= 0.0)// Проверка валидности радиуса
	{
		ft_printf("Error: Invalid diameter: %f\n", sphere->radius * 2);
		free(sphere);
		return (0);
	}// Добавляем сферу в начало связного списка сцен
	sphere->next = scene->spheres;
	scene->spheres = sphere;
	return (1);
}

// Обрабатывает плоскость - Формат: pl <point> <normal> <color>
// point — точка на плоскости (vec3)
// normal — нормализованный вектор нормали (vec3)
// color — RGB цвет
int	handle_plane(char **tokens, t_scene *scene)
{
	t_plane	*plane;

	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (ft_printf("Error: Missing parameters for Plane"), 0);
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (ft_printf("Error: Memory allocation failed for Plane"), 0);
	plane->point = parse_vec3(tokens[1]);// Парсим точку, нормаль и цвет
	plane->normal = parse_vec3(tokens[2]);
	if (vec3_length(plane->normal) == 0.0)
	{
    	ft_printf("Error: Plane normal vector cannot be zero\n");
    	free(plane);
    	return (0);
	}
	if (!check_vec3_range(plane->normal, -1.0, 1.0))
	{
   		ft_printf("Error: Plane normal vector out of range [-1,1]\n");
    	free(plane);
    	return (0);
	}
	plane->normal = vec3_normalize(plane->normal);
	if (!parse_color(tokens[3], &plane->color))
	{
    	free(plane);
    	return (0); // выходим с ошибкой
	}
	if (tokens[4])
	{
		plane->reflectivity = ft_atof(tokens[4]);
		if (tokens[5])
			plane->specular = ft_atof(tokens[5]);
		else
			plane->specular = 0;
	}
	else
	{
		plane->reflectivity = 0.0;
		plane->specular = 0;
	}	
	plane->next = scene->planes;
	scene->planes = plane;
	return (1);
}

// Проверка, что вектор направления цилиндра нормализован,
// и радиус и высота положительны
/*static int	error_handling(t_cylinder *cylinder)
{
	if (fabs(vec3_length(cylinder->direction) - 1.0) > 0.001)
	{
		ft_printf("Error: Cylinder direction vector is not normalized\n");
		free(cylinder);
		return (0);
	}
	if (cylinder->radius <= 0.0 || cylinder->height <= 0.0)
	{
		ft_printf("Error: Cylinder dimensions are invalid\n");
		free(cylinder);
		return (0);
	}
	return (1);
}*/

// Обрабатывает цилиндр - Формат: cy <base> <direction> <diameter> <height> <color>
// base — основание цилиндра (vec3)
// direction — нормализованный вектор направления (ось цилиндра)
// diameter — диаметр цилиндра (радиус = diameter / 2)
// height — высота цилиндра
// color — RGB
int	handle_cylinder(char **tokens, t_scene *scene)
{
	t_cylinder	*cylinder;

	// Проверка наличия всех 5 параметров
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] || !tokens[5])
		return (ft_printf("Error: Missing parameters for Cylinder\n"), 0);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (ft_printf("Error: Memory allocation failed for Cylinder\n"), 0);
	cylinder->base = parse_vec3(tokens[1]);// Парсим базовую точку, направление, радиус, высоту и цвет
	cylinder->direction = parse_vec3(tokens[2]);
	if (vec3_length(cylinder->direction) == 0.0)
	{
		ft_printf("Error: Cylinder direction vector cannot be zero\n");
		free(cylinder);
		return (0);
	}
	if (!check_vec3_range(cylinder->direction, -1.0, 1.0))
	{
   		ft_printf("Error: Cylinder direction vector out of range [-1,1]\n");
    	free(cylinder);
    	return (0);
	}
	cylinder->direction = vec3_normalize(cylinder->direction);// Нормализуем вектор направления
	cylinder->radius = ft_atof(tokens[3]) / 2.0;
	cylinder->height = ft_atof(tokens[4]);
	if (!parse_color(tokens[5], &cylinder->color))
	{
    	free(cylinder);
    	return (0); // выходим с ошибкой
	}
	if (tokens[6])
	{
		cylinder->reflectivity = ft_atof(tokens[6]);
		if (tokens[7])
			cylinder->specular = ft_atof(tokens[7]);
		else
			cylinder->specular = 0;
	}
	else
	{
		cylinder->reflectivity = 0.0;
		cylinder->specular = 0;
	}
	if (cylinder->radius <= 0.0 || cylinder->height <= 0.0)
    {
        ft_printf("Error: Cylinder dimensions are invalid\n");
        free(cylinder);
        return (0);
    }
	cylinder->next = scene->cylinders;
	scene->cylinders = cylinder;
	return (1);
}

// parser_triangle.c
#include "../../includes/parser.h"
#include "../../includes/math_utils.h"

int handle_triangle(char **tokens, t_scene *scene)
{
	t_triangle *tri;

	if (!tokens || !tokens[1] || !tokens[2] || !tokens[3] || !tokens[4])
		return (ft_printf("Error: Missing parameters for Triangle\n"), 0);
	if (!scene)
		return (ft_printf("Error: Scene is NULL\n"), 0);

	tri = malloc(sizeof(t_triangle));
	if (!tri)
		return (ft_printf("Error: Memory allocation failed for Triangle\n"), 0);

	tri->v0 = parse_vec3(tokens[1]);
	tri->v1 = parse_vec3(tokens[2]);
	tri->v2 = parse_vec3(tokens[3]);
	if (!parse_color(tokens[4], &tri->color))
	{
    	free(tri);
    	return (0); // выходим с ошибкой
	}
	if (tokens[5])
	{
		tri->reflectivity = ft_atof(tokens[5]);
		if (tokens[6])
			tri->specular = ft_atof(tokens[6]);
		else
			tri->specular = 0;
	}
	else
	{
		tri->reflectivity = 0.0;
		tri->specular = 0;
	}

	tri->next = scene->triangles;
	scene->triangles = tri;
	return (1);
}

