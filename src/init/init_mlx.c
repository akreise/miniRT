/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:50:29 by akreise           #+#    #+#             */
/*   Updated: 2025/08/23 18:36:59 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_image	init_image(void *mlx)
{
	t_image	image;

	image.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	image.addr = mlx_get_data_addr(image.img, &image.bpp,
			&image.line_length, &image.endian);
	return (image);
}

int	color_to_int(t_color color)
{
	return ((color.r << 16) | (color.g << 8) | color.b);
}

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	initialize_scene(t_scene *scene)
{
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	scene->lights = NULL;
	scene->camera.position = (t_vec3){0, 0, 0};
	scene->camera.orientation = (t_vec3){0, 0, 1};
	scene->camera.fov = 70.0;
	scene->ambient.ratio = 0.2;
	scene->ambient.color = (t_color){255, 255, 255};
}
