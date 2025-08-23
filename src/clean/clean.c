/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:22:22 by akreise           #+#    #+#             */
/*   Updated: 2025/07/28 19:16:20 by akreise          ###   ########.fr       */
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

static void	free_lights(t_light *l)
{
	t_light	*tmp;

	while (l)
	{
		tmp = l->next;
		free(l);
		l = tmp;
	}
}

static void	free_spheres(t_sphere *s)
{
	t_sphere	*tmp;

	while (s)
	{
		tmp = s->next;
		free(s);
		s = tmp;
	}
}

static void	free_planes(t_plane *p)
{
	t_plane	*tmp;

	while (p)
	{
		tmp = p->next;
		free(p);
		p = tmp;
	}
}

static void	free_cylinders(t_cylinder *c)
{
	t_cylinder	*tmp;

	while (c)
	{
		tmp = c->next;
		free(c);
		c = tmp;
	}
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	free_lights(scene->lights);
	free_spheres(scene->spheres);
	free_planes(scene->planes);
	free_cylinders(scene->cylinders);
}
