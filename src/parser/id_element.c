/* **************************************int	parse_objects(char **tokens, t_scene *scene)
{
	if (ft_strcmp(tokens[0], "sp") == 0)
		return (handle_sphere(tokens, scene));
	if (ft_strcmp(tokens[0], "pl") == 0)
		return (handle_plane(tokens, scene));
	if (ft_strcmp(tokens[0], "cy") == 0)
		return (handle_cylinder(tokens, scene));
	return (0);
}************************ */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_element.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akreise <akreise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:17:32 by pshcherb          #+#    #+#             */
/*   Updated: 2025/08/11 18:11:39 by akreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../includes/scene.h"


//Главная точка входа для определения, что именно содержится в строке .rt файла
int	id_element(char **tokens, t_scene *scene)
{
	if (!tokens || !tokens[0])// Проверка на пустые строки или строки без токенов
		return (0);
	if (parse_ambient(tokens, scene))// Пробуем как глобальные элементы сцены (Ambient, Camera, Light)
		return (1);
	if (parse_objects(tokens, scene))// Пробуем как геометрические объекты (Sphere, Plane, Cylinder)
		return (1);
	return (0);/// Неизвестный элемент, не удалось распознать
}

//Обрабатывает глобальные элементы сцены (ambient light, camera, light)
int	parse_ambient(char **tokens, t_scene *scene)
{
	if (ft_strcmp(tokens[0], "A") == 0)// Ambient light (освещение сцены)
		return (handle_ambient(tokens, scene));
	if (ft_strcmp(tokens[0], "C") == 0)// Camera (камера)
		return (handle_camera(tokens, scene));
	if (ft_strcmp(tokens[0], "L") == 0)// Light (источник света)
		return (handle_light(tokens, scene));
	return (0);// Неизвестный элемент
}

//Определяет геомет объект по токену и вызывает handle_*
int	parse_objects(char **tokens, t_scene *scene)
{
	if (ft_strcmp(tokens[0], "sp") == 0)//сфера
		return (handle_sphere(tokens, scene));
	if (ft_strcmp(tokens[0], "pl") == 0)//плоскость
		return (handle_plane(tokens, scene));
	if (ft_strcmp(tokens[0], "cy") == 0)//цилиндр
		return (handle_cylinder(tokens, scene));
	return (0);//неизвестный обьяект
}
