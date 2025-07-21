/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:55:51 by pshcherb          #+#    #+#             */
/*   Updated: 2025/07/21 16:56:18 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H 

# define WIDTH 800
# define HEIGHT 600

# include "parser.h"
# include "math_utils.h"
# include "../mlx/minilibx-linux/mlx.h"

typedef struct  s_light_c
{
    t_color	ambient;
	t_color	diffuse_total;
	t_light	*light;
	t_vec3	light_dir;
	double	dot;
	double	intensity;
	t_color	diffuse;
}   t_light_c;

typedef struct s_mlx_data {
    void    *mlx_ptr;
    void    *win_ptr;
    t_image img;
    t_scene *scene;
} t_mlx_data;

// color_combine.c
t_color color_scale(t_color color, double factor);
t_color color_add(t_color a, t_color b);

// lightning_calculations.c
t_color	compute_lighting(t_vec3 hit_point, t_vec3 normal, t_color obj_color,
						 t_scene *scene);

// trace_ray.c
t_color trace_ray(t_ray ray, t_scene *scene);
void    trace_sphere(t_color *color, double *closest, t_ray ray, t_scene *scene);
void    trace_plane(t_color *color, double *closest, t_ray ray, t_scene *scene);
void    trace_cylinders(t_color *color, double *closest, t_ray ray, t_scene *scene);
t_vec3	get_cylinder_normal(t_cylinder *cy, t_vec3 hit);

// init
t_image	init_image(void *mlx);
int 	color_to_int(t_color color);
void	put_pixel(t_image *img, int x, int y, int color);
void 	initialize_scene(t_scene *scene);

#endif
