/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:56:16 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 16:48:13 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <math.h>
# include "math_utils.h"
# include "scene.h"
# include "miniRT.h"

t_ray	camera_ray(t_camera camera, int x, int y);
void	render_full_scene(t_app *app);

#endif