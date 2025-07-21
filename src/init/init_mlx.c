/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:50:29 by akreise           #+#    #+#             */
/*   Updated: 2025/07/21 16:49:52 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Функция инициализирует структуру t_image — создаёт новое изображение и получает 
// доступ к его пикселям
t_image	init_image(void *mlx)
{
	t_image	image;
    
	// Создаём новое изображение шириной WIDTH и высотой HEIGHT
	image.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	// Получаем адрес начала данных изображения и информацию о формате
	// bpp — бит на пиксель, line_length — количество байт в строке, endian — порядок байтов
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_length, &image.endian);
	// Возвращаем заполненную структуру t_image
	return (image);
}

// Преобразует структуру цвета (r, g, b) в одно целое число типа int
int color_to_int(t_color color)
{
	// Сдвигаем красный компонент на 16 бит влево, зелёный — на 8, синий остаётся
	// Пример: (255, 0, 0) => 0xFF0000
	return ((color.r << 16) | (color.g << 8) | color.b);
}

// Рисует один пиксель на изображении по координатам (x, y) с заданным цветом
void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	// Проверяем, находится ли пиксель внутри границ изображения
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	// Вычисляем адрес памяти, где хранится нужный пиксель
	// line_length — байт в строке, bpp/8 — размер одного пикселя в байтах
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	// Записываем цвет по адресу пикселя
	*(unsigned int *)dst = color;
}

// In src/scene/scene.c or similar file
void initialize_scene(t_scene *scene)
{
    // Initialize all pointers to NULL
    scene->spheres = NULL;
    scene->planes = NULL;
    scene->cylinders = NULL;
    scene->lights = NULL;
    
    // Initialize camera with default values
    scene->camera.position = (t_vec3){0, 0, 0};
    scene->camera.orientation = (t_vec3){0, 0, 1};
    scene->camera.fov = 70.0;
    
    // Initialize ambient light
    scene->ambient.ratio = 0.2;
    scene->ambient.color = (t_color){255, 255, 255};
}