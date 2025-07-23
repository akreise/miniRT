/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_combine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:42:09 by pshcherb          #+#    #+#             */
/*   Updated: 2025/07/23 15:52:15 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/miniRT.h"

// Масштабирует цвет по заданному коэффициенту factor (0.0–1.0)
// Используется, например, при применении яркости (ambient ratio, light brightness)
// Значения ограничиваются 255, чтобы не выйти за пределы RGB
t_color	color_scale(t_color color, double factor)
{
	t_color	result;

	result.r = fmin(color.r * factor, 255);// Умножаем красный на factor, но максимум 255
	result.g = fmin(color.g * factor, 255);// То же для зелёного
	result.b = fmin(color.b * factor, 255);// И синего
	return (result);
}

t_color color_mul(t_color a, t_color b)
{
    return (t_color){
        (a.r * b.r) / 255.0,
        (a.g * b.g) / 255.0,
        (a.b * b.b) / 255.0
    };
}

//t_color base = {200, 100, 50};
//t_color ambient = color_scale(base, 0.2); // → {40, 20, 10}

// Складывает два цвета, по RGB-каналам
// Используется при комбинировании освещения: ambient + diffuse и т.д.
// Значения ограничиваются 255, чтобы избежать переполнения
t_color	color_add(t_color a, t_color b)
{
	t_color	result;

	result.r = fmin(a.r + b.r, 255);// Складываем R, максимум 255
	result.g = fmin(a.g + b.g, 255);// Складываем G
	result.b = fmin(a.b + b.b, 255);// Складываем B
	return (result);
}
//t_color ambient = {40, 20, 10};
//t_color diffuse = {100, 50, 0};
//t_color final = color_add(ambient, diffuse); // → {140, 70, 10}