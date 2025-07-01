/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:22:53 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/12 12:59:26 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	read_rt_file(const char *filename, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(line, scene);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	process_line(char *line, t_scene *scene)
{
	char	**tokens;

	if (!line || !*line || line[0] == '\n')
		return ;
	tokens = ft_split(line, ' ');
	if (!tokens)
		return ;
	if (!id_element(tokens, scene))
	{
		ft_printf("Error: Failed to identify or parse element in line: %s\n",
			line);
		free_tokens(tokens);
		return ;
	}
	free_tokens(tokens);
}
