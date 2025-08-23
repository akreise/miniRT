/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:22:53 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/23 18:55:13 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/miniRT.h"

// Читает .rt файл построчно и передаёт каждую строку на обработку
// filename — путь к .rt файлу
// scene — указатель на структуру сцены, которую заполняем
void	read_rt_file(const char *filename, t_app *app)
{
	int		fd;
	char	*line;

	reset_element_counters();
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(line, app);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	replace_tabs_with_spaces(char *line)
{
	while (*line)
	{
		if (*line == '\t')
			*line = ' ';
		line++;
	}
}

static void	trim_newline(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

// Обрабатывает одну строку из .rt файла: парсит и добавляет в сцену
// line — строка из .rt файла (например, "sp 0,0,0 10 255,0,0")
// scene — структура, в которую добавляем объект
void	process_line(char *line, t_app *app)
{
	char	**tokens;

	if (!line || !*line || line[0] == '\n')
		return ;
	replace_tabs_with_spaces(line);
	trim_newline(line);
	tokens = ft_split(line, ' ');
	if (!tokens)
		return ;
	if (!validate_line_tokens(tokens))
	{
		free_tokens(tokens);
		cleanup_and_exit(app, 1);
		return ;
	}
	if (!id_element(tokens, &app->scene))
	{
		free_tokens(tokens);
		cleanup_and_exit(app, 1);
		return ;
	}
	free_tokens(tokens);
}
