/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:38:34 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 19:05:20 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/render.h"
#include "../../includes/miniRT.h"
#include <math.h>

static t_ray	create_camera_ray(t_camera camera, double px, double py)
{
	t_ray	ray;
	t_vec3	forward;
	t_vec3	up;
	t_vec3	right;
	t_vec3	dir;

	forward = vec3_normalize(camera.orientation);
	up = (t_vec3){0, 1, 0};
	if (fabs(forward.y) > 0.999)
		up = (t_vec3){0, 0, 1};
	right = vec3_normalize(vec3_cross(forward, up));
	up = vec3_cross(right, forward);
	dir = vec3_add(vec3_scale(right, px), vec3_scale(up, py));
	dir = vec3_add(dir, forward);
	ray.origin = camera.position;
	ray.direction = vec3_normalize(dir);
	return (ray);
}

t_ray	camera_ray(t_camera camera, int x, int y)
{
	t_ray		ray;
	double		aspect_ratio;
	double		fov_rad;
	double		px;
	double		py;

	aspect_ratio = (double)WIDTH / HEIGHT;
	fov_rad = camera.fov * M_PI / 180.0;
	px = (2 * ((x + 0.5) / WIDTH) - 1) * tan(fov_rad / 2.0) * aspect_ratio;
	py = (1 - 2 * ((y + 0.5) / HEIGHT)) * tan(fov_rad / 2.0);
	ray = create_camera_ray(camera, px, py);
	return (ray);
}

static void	render_row(t_app *app, int y)
{
	t_scene	*scene;
	t_ray	ray;
	t_color	color;
	int		rgb_color;
	int		x;

	scene = &app->scene;
	x = 0;
	while (x < WIDTH)
	{
		ray = camera_ray(scene->camera, x, y);
		color = trace_ray(ray, scene, 0);
		rgb_color = color_to_int(color);
		put_pixel(&app->mlx_data.img, x, y, rgb_color);
		x++;
	}
}

void	render_full_scene(t_app *app)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		render_row(app, y);
		y++;
	}
}
