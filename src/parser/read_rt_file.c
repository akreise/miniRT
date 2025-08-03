/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:22:53 by pshcherb          #+#    #+#             */
/*   Updated: 2025/07/28 19:31:24 by akreise          ###   ########.fr       */
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

	fd = open(filename, O_RDONLY);// Открываем файл на чтение
	if (fd < 0)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);// Завершаем программу, если не удалось открыть файл
	}
	line = get_next_line(fd);// Читаем построчно с помощью get_next_line
	while (line != NULL)
	{
		process_line(line, app);// Обрабатываем каждую строку
		free(line);
		line = get_next_line(fd);// Не забываем освобождать память
	}
	close(fd);// Закрываем файл
}

// Обрабатывает одну строку из .rt файла: парсит и добавляет в сцену
// line — строка из .rt файла (например, "sp 0,0,0 10 255,0,0")
// scene — структура, в которую добавляем объект
void	process_line(char *line, t_app *app)
{
	char	**tokens;

	if (!line || !*line || line[0] == '\n')// Проверка: пустая строка или просто \n
		return ;
	tokens = ft_split(line, ' ');// Разделяем строку по пробелам: tokens[0] — тип (sp, pl, A, C и т.д.)
	if (!tokens)
		return ;
	if (!id_element(tokens, &app->scene))// Распознаём тип элемента и вызываем нужный обработчик (handle_*)
	{
		free_tokens(tokens);
		cleanup_and_exit(app, 1);
		return ;
	}
	free_tokens(tokens);// Освобождаем память после успешного парсинга
}
