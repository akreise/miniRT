/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:58:30 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/13 15:33:55 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

// Освобождает память, выделенную под массив строк (tokens)
void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])// Освобождаем каждую строку внутри массива
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);// Освобождаем сам массив указателей
}

// Вычисляет длину (модуль) 3D-вектора по формуле: sqrt(x^2 + y^2 + z^2)
// Используется, например, чтобы проверить, нормализован ли вектор (приведен к 1)
double	vec3_length(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

// Проверяет, входит ли значение цвета в допустимый диапазон [0, 255]
// Используется при парсинге цвета из строки
int	is_valid_color_value(int value)
{
	return (value >= 0 && value <= 255);
}

// Парсит строку формата "x,y,z" в структуру t_vec3
// Если формат некорректен, возвращает (0, 0, 0) и печатает ошибку
t_vec3	parse_vec3(char *str)
{
	t_vec3		vec3;
	char		**values;

	values = ft_split(str, ',');// Разбиваем строку по запятой
	if (!values[0] || !values[1] || !values[2] || values[3])// Проверка, что ровно три значения, иначе ошибка
	{
		ft_printf("Error: Invalid vector format: %s\n", str);
		free_tokens(values);
		return ((t_vec3){0, 0, 0});
	}// Конвертируем строки в float
	vec3.x = ft_atof(values[0]);
	vec3.y = ft_atof(values[1]);
	vec3.z = ft_atof(values[2]);
	free_tokens(values);// Освобождаем память
	return (vec3);
}

// Парсит строку формата "R,G,B" в структуру t_color
// Проверяет корректность диапазона [0-255]
// Если ошибка — возвращает цвет (0, 0, 0) и печатает сообщение
int parse_color(char *str, t_color *color)
{
	char		**values;

	values = ft_split(str, ',');// Разбиваем строку на три части по запятой
	if (!values[0] || !values[1] || !values[2])// Проверка на корректное количество значений
	{
		ft_printf("Error: Invalid color format: %s\n", str);
		free_tokens(values);
		return (0);
	}// Преобразуем строки в целые числа
	color->r = ft_atoi(values[0]);
	color->g = ft_atoi(values[1]);
	color->b = ft_atoi(values[2]);
	free_tokens(values);// Освобождаем память
	if (!is_valid_color_value(color->r) || !is_valid_color_value(color->g)
		|| !is_valid_color_value(color->b))// Проверяем, что значения находятся в допустимом диапазоне
	{
		ft_printf("Error: Color values out of range [0-255]: %s\n", str);
		return (0);// ошибка
	}
	return (1);// успешно
}
