/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:56:06 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 18:36:52 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../libft/libft.h"
# include "scene.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

typedef struct s_app	t_app;
// read_rt_file.c
void	read_rt_file(const char *filename, t_app *app);
void	process_line(char *line, t_app *app);
void	replace_tabs_with_spaces(char *line);

// id_element.c
int		id_element(char **tokens, t_scene *scene);
int		parse_ambient(char **tokens, t_scene *scene);
int		parse_objects(char **tokens, t_scene *scene);

// parse_ambient.c
int		handle_ambient(char **tokens, t_scene *scene);

// parse_camera.c 
int		handle_camera(char **tokens, t_scene *scene);

// parse_light.c
int		handle_light(char **tokens, t_scene *scene);

// parse_ambient_utils.c
void	reset_element_counters(void);
int		get_ambient_count(int reset);
int		get_camera_count(int reset);
int		get_light_count(int reset);
int		validate_ambient_params(char **tokens, double *ratio, t_color *color);

// parse_objects.c
int		handle_sphere(char **tokens, t_scene *scene);
int		handle_plane(char **tokens, t_scene *scene);
int		handle_cylinder(char **tokens, t_scene *scene);

// parsing_utils.c
void	free_tokens(char **tokens);
int		is_valid_color_value(int value);
double	vec3_length(t_vec3 vec);
int		parse_color(char *str, t_color *color);
t_vec3	parse_vec3(char *str);

// check.c
int		has_rt_extension(const char *filename);
int		check_rt_file(const char *filename);
int		is_file_empty(const char *filename);

// check_utils.c
int		check_file_exists(const char *filename);
int		check_rgb_range(t_color *color);
int		check_ratio_range(double ratio);
int		check_fov_range(int fov);
int		validate_line_tokens(char **tokens);

// check_elements.c
int		check_sphere(t_sphere *sphere);
int		check_plane(t_plane *plane);
int		check_cylinder_properties(t_cylinder *cylinder);
int		check_cylinder(t_cylinder *cylinder);

// check_lighting.c
int		check_ambient(t_ambient *ambient);
int		check_light(t_light *light);
int		check_camera_properties(t_camera *camera);
int		check_camera(t_camera *camera);

// check_scene.c
int		check_spheres(t_sphere *spheres);
int		check_planes(t_plane *planes);
int		check_cylinders(t_cylinder *cylinders);
int		check_scene(t_scene *scene);

// check_duplicates.c
int		count_lights(t_light *lights);
int		check_required_elements(t_scene *scene);
int		validate_parsed_scene(t_scene *scene);

#endif