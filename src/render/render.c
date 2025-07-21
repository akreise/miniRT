/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:38:34 by pshcherb          #+#    #+#             */
/*   Updated: 2025/07/21 16:57:58 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"
#include "../../includes/miniRT.h"

/*void	render_scene(t_scene *scene, void *mlx, void *win)
{
    int y;
    int x;

    y = 0;
    x = 0;
    while (y < HEIGHT)
    {
        while (x < WIDTH)
        {
            double u = (2.0 * x / WIDTH - 1.0) * tan(scene->camera.fov * 0.5 * M_PI / 180.0);
			double v = (1.0 - 2.0 * y / HEIGHT) * tan(scene->camera.fov * 0.5 * M_PI / 180.0);

			t_vec3 direction = vec3_add(
				scene->camera.orientation,
				vec3_add(
					vec3_scale(scene->camera.right, u),
					vec3_scale(scene->camera.up, v)
				)
			);

			t_ray ray = create_ray(scene->camera.position, vec3_normalize(direction));
			t_color color = trace_ray(ray, scene);

			int rgb = (color.r << 16) | (color.g << 8) | color.b;
			mlx_pixel_put(mlx, win, x, y, rgb);
            x++;
        }
        y++;
    }
}*/

//генерация луча из камеры в пиксель (x, y) на экране
t_ray camera_ray(t_camera camera, int x, int y)
{
    t_ray ray;

	// Соотношение сторон экрана (ширина / высота)
    double aspect_ratio = (double)WIDTH / HEIGHT;
	// Угол обзора (FOV) переводим из градусов в радианы
    double fov_rad = camera.fov * M_PI / 180.0;
	// Преобразуем координаты пикселя в нормализованное пространство (от -1 до 1)
    double px = (2 * ((x + 0.5) / WIDTH) - 1) * tan(fov_rad / 2.0) * aspect_ratio;
    double py = (1 - 2 * ((y + 0.5) / HEIGHT)) * tan(fov_rad / 2.0);

    // Создадим ортонормированный базис камеры:
    t_vec3 forward = vec3_normalize(camera.orientation);
	// Вектор "вверх". По умолчанию (0, 1, 0)
    t_vec3 up = (t_vec3){0, 1, 0};
	// Если камера смотрит почти вертикально — меняем "вверх", чтобы не было проблем с cross product
    if (fabs(forward.y) > 0.999)
        up = (t_vec3){0, 0, 1};
	// Вычисляем вектор "вправо" (right = forward × up)
    t_vec3 right = vec3_normalize(vec3_cross(forward, up));
	// Пересчитываем "вверх", чтобы он был ортогонален forward и right
    up = vec3_cross(right, forward);

    // Составляем направление луча: px * right + py * up + forward
    t_vec3 dir = vec3_add(vec3_add(vec3_scale(right, px), vec3_scale(up, py)), forward);
    // Начало луча — позиция камеры
	ray.origin = camera.position;
	// Направление нормализуем (иначе длина может быть > 1)
    ray.direction = vec3_normalize(dir);

    return ray;
}

void render_full_scene(t_mlx_data *data)
{
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            // Use your existing camera_ray function
            t_ray ray = camera_ray(data->scene->camera, x, y);
            
            // Use your existing trace_ray function for full scene
            t_color color = trace_ray(ray, data->scene);
            
            int rgb_color = color_to_int(color);
            put_pixel(&data->img, x, y, rgb_color);
        }
    }
}
/*
// Рендеринг: заполняет изображение, проверяя пересечение лучей со сферой
void render(t_image *img, t_camera camera, t_sphere *sphere)
{
	int x, y;

	// Проходим по каждому пикселю изображения
	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			// Строим луч из камеры через пиксель (x, y)
			t_ray ray = camera_ray(camera, x, y);
			double t;

			// Проверяем, пересекает ли луч сферу
			if (intersect_sphere(ray, sphere, &t))
			{
                printf("Hit at pixel (%d, %d), t=%.2f\n", x, y, t);
				// Есть пересечение — красим пиксель цветом сферы
				put_pixel(img, x, y, color_to_int(sphere->color));
			}
			else
			{
				// Нет пересечения — черный фон
				put_pixel(img, x, y, 0x000000);
			}
		}
	}
}*/