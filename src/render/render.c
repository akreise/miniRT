/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:38:34 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/26 17:44:07 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	render_scene(t_scene *scene, void *mlx, void *win)
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
}