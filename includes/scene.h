/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:56:38 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/12 12:37:16 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct	s_vec3 {
    double	x;
    double	y;
    double	z;
} t_vec3;

typedef struct	s_color {
    int	r;
    int	g;
    int	b;
} t_color;

typedef struct  s_ambient {
	double      	ratio;
	t_color     	color;
} t_ambient;

typedef struct  s_camera {
	t_vec3      	position;
	t_vec3      	orientation;
	double      	fov;
} t_camera;

typedef struct  s_light {
	t_vec3      	position;
	double      	brightness;
	t_color     	color;
	struct s_light	*next;
} t_light;

typedef struct  s_sphere {
	t_vec3      	center;
	double      	radius;
	t_color     	color;
	struct s_sphere *next;
} t_sphere;

typedef struct 	s_plane {
	t_vec3 			point;
	t_vec3 			normal;
	t_color 		color;
	struct s_plane *next;
} t_plane;

typedef struct s_cylinder {
	t_vec3 				base;
	t_vec3 				direction;
	double 				radius;
	double 				height;
	t_color 			color;
	struct s_cylinder 	*next;
} t_cylinder;

typedef struct s_scene {
	t_ambient    ambient;
	t_camera     camera;
	t_light      *lights;
	t_sphere     *spheres;
	t_plane      *planes;
	t_cylinder   *cylinders;
} t_scene;

#endif