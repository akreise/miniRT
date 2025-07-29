/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:49:06 by pshcherb          #+#    #+#             */
/*   Updated: 2025/07/28 18:33:04 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/math_utils.h"

// Обработка строки с параметрами Ambient light из .rt файла
// Формат строки: A <ratio> <R,G,B>
// ratio - коэффициент интенсивности освещения (0.0 - 1.0) color - цвет освещения (RGB 0-255)
// Записывает параметры в структуру scene->ambient, 1 при успехе, 0 при ошибке
int	handle_ambient(char **tokens, t_scene *scene)
{
	double	ratio;
	t_color	color;

	// Проверка наличия необходимых параметров
	if (!tokens[1] || !tokens[2])
		return (ft_printf("Error: Missing parameters for Ambient light\n"), 0);
	// Конвертация коэффициента освещения из строки в число с плавающей точкой
	ratio = ft_atof(tokens[1]);
	if (ratio < 0.0 || ratio > 1.0)// Проверка, что коэффициент в допустимом диапазоне [0.0, 1.0]
	{
		ft_printf("Error: Ambient light ratio out of range [0.0, 1.0]: %f\n",
			ratio);
		return (0);
	}
	color = parse_color(tokens[2]);// Парсинг цвета из строки формата "R,G,B"
	if (color.r == 0 && color.g == 0 && color.b == 0)// Проверка, цвет успешно распознан (не черный по умолчанию)
		{
			ft_printf("Error: Failed to parse color for Ambient light\n");
			return (0);
		}
	// Сохранение параметров ambient light в структуре сцены
	scene->ambient.ratio = ratio;
	scene->ambient.color = color;
	return (1);
}

// Обработка строки с параметрами камеры из .rt файла
// Формат строки: C <position> <orientation> <FOV>
// position - вектор позиции камеры (x,y,z)
// orientation - нормализованный вектор направления камеры (-1 <= each <= 1)
// FOV - угол обзора в градусах (0 < FOV < 180)
// Записывает параметры в структуру scene->camera, Возвращает 1 при успехе, 0 при ошибке
int	handle_camera(char **tokens, t_scene *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])// Проверка наличия всех трёх параметров
		return (ft_printf("Error: Missing parameters for Camera\n"), 0);
	scene->camera.position = parse_vec3(tokens[1]);// Парсинг позиции камеры из строки в вектор
	scene->camera.orientation = parse_vec3(tokens[2]);// Парсинг ориентации камеры (направления взгляда)
	if (vec3_length(scene->camera.orientation) == 0.0)
	{
		ft_printf("Error: Camera orientation vector cannot be zero\n");
		return (0);
	}
	scene->camera.orientation = vec3_normalize(scene->camera.orientation);
	scene->camera.fov = ft_atof(tokens[3]);	// Парсинг угла обзора (FOV)
	if (scene->camera.fov <= 0 || scene->camera.fov >= 180)// Проверка корректности угла обзора (от 0 до 180 гр)
	{
		ft_printf("Error: Camera FOV out of range [0, 180]: %f\n",
			scene->camera.fov);
		return (0);
	}
	return (1);
}

// Обработка строки с параметрами точечного источника света из .rt файла
// Формат строки: L <position> <brightness> <R,G,B>
// position - координаты источника света (x,y,z)
// brightness - яркость света (0.0 - 1.0)
// color - цвет света (RGB 0-255)
// Добавляет новый свет в связный список scene->lights, Возвращает 1 при успехе, 0 при ошибке
int	handle_light(char **tokens, t_scene *scene)
{
	t_light	*light;

	if (!tokens[1] || !tokens[2] || !tokens[3])// Проверка наличия всех необходимых параметров
		return (ft_printf("Error: Missing parameters for Light\n"), 0);
	light = malloc(sizeof(t_light));// Выделение памяти под структуру источника света
	if (!light)
		return (ft_printf("Error: Memory allocation failed for Light\n"), 0);
	light->position = parse_vec3(tokens[1]);// Парсинг позиции света
	light->brightness = ft_atof(tokens[2]);// Парсинг яркости света
	light->color = parse_color(tokens[3]);// Парсинг цвета света
	if (light->brightness < 0.0 || light->brightness > 1.0)// Проверка диапазона яркости [0.0, 1.0]
	{
		ft_printf("Error: Light brightness out of range [0.0, 1.0]: %f\n",
			light->brightness);
		free(light);
		return (0);
	}
	light->next = scene->lights;// Вставка нового света в начало списка источников сцены
	scene->lights = light;
	return (1);
}
