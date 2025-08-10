/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:55:51 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/10 20:56:17 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H 

# define WIDTH 800
# define HEIGHT 800

# include "parser.h"
# include "math_utils.h"
# include "scene.h"
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
    //t_scene *scene;
} t_mlx_data;

typedef struct s_app
{
    t_mlx_data mlx_data;
    t_scene    scene;
} t_app;

// color_combine.c
t_color color_scale(t_color color, double factor);
t_color color_add(t_color a, t_color b);
t_color color_mul(t_color a, t_color b);

// lightning_calculations.c
t_color	compute_lighting(t_vec3 hit_point, t_vec3 normal, t_color obj_color,
						 double specular, t_scene *scene, t_vec3 camera_pos);
double shadow_factor(t_vec3 point, t_light *light, t_scene *scene);
t_vec3 random_in_unit_disk(void);
// trace_ray.c
t_color trace_ray(t_ray ray, t_scene *scene, int depth);
void    trace_sphere(t_color *color, double *closest, t_ray ray, t_scene *scene, int depth);
void    trace_plane(t_color *color, double *closest, t_ray ray, t_scene *scene, int depth);
void    trace_cylinder(t_color *color, double *closest, t_ray ray, t_scene *scene, int depth);
t_vec3	get_cylinder_normal(t_cylinder *cy, t_vec3 hit);
t_color color_blend(t_color c1, t_color c2, double factor);
t_color trace_ray_recursive(t_ray ray, t_scene *scene, int depth);

// init
t_image	init_image(void *mlx);
int 	color_to_int(t_color color);
void	put_pixel(t_image *img, int x, int y, int color);
void 	initialize_scene(t_scene *scene);

//check
int 	has_rt_extension(const char *filename);
int 	is_file_empty(const char *filename);
int 	validate_scene(t_scene *scene);
int 	validate_line_tokens(char **tokens);
int 	check_rt_file(const char *filename);

//clean
void 	cleanup_mlx(t_mlx_data *data);
void	cleanup_and_exit(t_app *app, int msg);

#endif
