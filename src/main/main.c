/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
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

int	handle_keypress(int keycode, t_app *app)
{
	if (keycode == 65307)
		cleanup_and_exit(app, 0);
	return (0);
}

int	close_window(t_app *app)
{
	cleanup_and_exit(app, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (!validate_arguments(argc, argv))
		return (1);
	if (!init_mlx(&app))
		return (1);
	init_app(&app);
	read_rt_file(argv[1], &app);
	if (!validate_parsed_scene(&app.scene))
	{
		printf("Error: Scene validation failed\n");
		cleanup_and_exit(&app, 1);
		return (1);
	}
	render_full_scene(&app);
	mlx_put_image_to_window(app.mlx_data.mlx_ptr, app.mlx_data.win_ptr,
		app.mlx_data.img.img, 0, 0);
	mlx_hook(app.mlx_data.win_ptr, 2, 1L << 0, handle_keypress, &app);
	mlx_hook(app.mlx_data.win_ptr, 17, 1L << 17, close_window, &app);
	mlx_loop(app.mlx_data.mlx_ptr);
	return (0);
}
