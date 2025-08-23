/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:22:22 by akreise           #+#    #+#             */
/*   Updated: 2025/08/23 18:37:03 by pshcherb         ###   ########.fr       */
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
#include <fcntl.h>
#include <unistd.h>

int	has_rt_extension(const char *filename)
{
	const char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strcmp(dot, ".rt") != 0)
		return (0);
	return (1);
}

int	check_rt_file(const char *filename)
{
	if (!has_rt_extension(filename))
		return (0);
	if (!check_file_exists(filename))
		return (0);
	return (1);
}

int	is_file_empty(const char *filename)
{
	int		fd;
	char	buffer[1];
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	bytes_read = read(fd, buffer, 1);
	close(fd);
	if (bytes_read <= 0)
		return (1);
	return (0);
}
