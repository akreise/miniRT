/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:22:22 by akreise           #+#    #+#             */
/*   Updated: 2025/07/29 16:42:02 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../mlx/minilibx-linux/mlx.h"
#include "../../includes/math_utils.h"
#include "../../includes/scene.h"
#include "../../includes/miniRT.h"
#include "../../includes/render.h"
#include <stdio.h>
#include <stdlib.h>

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Usage: %s <scene_file.rt>\n", argv[0]);
		return (0);
	}
	if (!has_rt_extension(argv[1]))
	{
		printf("Error: File must have .rt extension\n");
		return (0);
	}
	if (is_file_empty(argv[1]))
	{
		printf("Error: File is empty\n");
		return (0);
	}
	if (!check_rt_file(argv[1]))
		return (0);
	return (1);
}

int	init_mlx(t_app *app)
{
	app->mlx_data.mlx_ptr = mlx_init();
	if (!app->mlx_data.mlx_ptr)
	{
		printf("Error: Failed to initialize MLX\n");
		return (0);
	}
	app->mlx_data.win_ptr = mlx_new_window(app->mlx_data.mlx_ptr, WIDTH,
			HEIGHT, "miniRT");
	if (!app->mlx_data.win_ptr)
	{
		printf("Error: Failed to create window\n");
		mlx_destroy_display(app->mlx_data.mlx_ptr);
		free(app->mlx_data.mlx_ptr);
		return (0);
	}
	app->mlx_data.img = init_image(app->mlx_data.mlx_ptr);
	return (1);
}

void	init_app(t_app *app)
{
	initialize_scene(&app->scene);
	app->ambient_count = 0;
	app->camera_count = 0;
	app->light_count = 0;
}
