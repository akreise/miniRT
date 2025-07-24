/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:56:16 by pshcherb          #+#    #+#             */
/*   Updated: 2025/07/24 15:51:58 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include <math.h>
# include "math_utils.h"
# include "scene.h"
# include "miniRT.h"
//#define M_PI 3.14159265358979323846

t_ray camera_ray(t_camera camera, int x, int y);
void render_full_scene(t_mlx_data *data);


#endif