/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:55:51 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 20:51:34 by pshcherb         ###   ########.fr       */
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

typedef struct s_light_c
{
	t_color	ambient;
	t_color	diffuse_total;
	t_light	*light;
	t_vec3	light_dir;
	t_vec3	normal;
	t_vec3	hit_point;
	t_vec3	view_dir;
	t_color	obj_color;
	double	specular;
	double	dot;
	double	intensity;
	double	shadow;
	t_color	diffuse;
	t_scene	*scene;
}	t_light_c;

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
}	t_mlx_data;

typedef struct s_app
{
	t_mlx_data	mlx_data;
	t_scene		scene;
	int			ambient_count;
	int			camera_count;
	int			light_count;
}	t_app;

typedef struct s_trace_ctx
{
	t_color	*color;
	double	*closest;
	t_ray	ray;
	t_scene	*scene;
	int		depth;
}	t_trace_ctx;

typedef struct s_lighting_ctx
{
	t_vec3	hit_point;
	t_vec3	normal;
	t_color	obj_color;
	double	specular;
	t_scene	*scene;
	t_vec3	camera_pos;
}	t_lighting_ctx;

typedef struct s_reflection_ctx
{
	t_ray	ray;
	t_vec3	hit_point;
	t_vec3	normal;
	double	reflectivity;
	t_scene	*scene;
	int		depth;
}	t_reflection_ctx;

// color_combine.c
t_color	color_scale(t_color color, double factor);
t_color	color_add(t_color a, t_color b);
t_color	color_mul(t_color a, t_color b);

// lightning_calculations.c
t_color	compute_lighting(t_lighting_ctx *ctx);
double	shadow_factor(t_vec3 point, t_light *light, t_scene *scene);
t_vec3	random_in_unit_disk(void);
double	calculate_sample_shadow(t_vec3 point, t_light *light, t_scene *scene);
bool	check_all_objects_shadow(t_scene *scene, t_ray shadow_ray,
			double light_dist);
bool	check_spheres_shadow(t_scene *scene, t_ray shadow_ray,
			double light_dist);
bool	check_planes_shadow(t_scene *scene, t_ray shadow_ray,
			double light_dist);
bool	check_cylinders_shadow(t_scene *scene, t_ray shadow_ray,
			double light_dist);
// trace_ray.c
t_color	trace_ray(t_ray ray, t_scene *scene, int depth);
void	trace_sphere(t_trace_ctx *ctx);
void	trace_plane(t_trace_ctx *ctx);
void	trace_cylinder(t_trace_ctx *ctx);
t_vec3	get_cylinder_normal(t_cylinder *cy, t_vec3 hit);
t_color	color_blend(t_color c1, t_color c2, double factor);
t_color	trace_ray_recursive(t_ray ray, t_scene *scene, int depth);

// init
t_image	init_image(void *mlx);
int		color_to_int(t_color color);
void	put_pixel(t_image *img, int x, int y, int color);
void	initialize_scene(t_scene *scene);

// check
int		has_rt_extension(const char *filename);
int		is_file_empty(const char *filename);
int		check_vec3_range(t_vec3 v, double min, double max);
int		validate_scene(t_scene *scene);
int		validate_line_tokens(char **tokens);
int		check_rt_file(const char *filename);

// clean
void	free_scene(t_scene *scene);
void	cleanup_mlx(t_mlx_data *data);
void	cleanup_and_exit(t_app *app, int msg);

// main
int		validate_arguments(int argc, char **argv);
int		init_mlx(t_app *app);
void	init_app(t_app *app);

#endif
