/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:38:34 by pshcherb          #+#    #+#             */
/*   Updated: 2025/07/29 16:45:00 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"
#include "../../includes/miniRT.h"
#include <math.h>

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

void render_full_scene(t_app *app)
{
    t_scene *scene = &app->scene;
    
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            // Use your existing camera_ray function
            t_ray ray = camera_ray(scene->camera, x, y);
            
            // Use your existing trace_ray function for full scene
            t_color color = trace_ray(ray, scene);
            
            int rgb_color = color_to_int(color);
            put_pixel(&app->mlx_data.img, x, y, rgb_color);
        }
    }
}