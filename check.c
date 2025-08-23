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

#include "includes/parser.h"
#include "mlx/minilibx-linux/mlx.h"
#include "includes/math_utils.h"
#include "includes/scene.h"
#include "includes/miniRT.h"
#include "includes/render.h"
#include <stdio.h>
#include <stdlib.h>

int has_rt_extension(const char *filename)
{
    const char *dot = ft_strrchr(filename, '.');
    if (!dot || ft_strcmp(dot, ".rt") != 0)
        return (0);
    return (1);
}

int check_rt_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return (printf("Error: Cannot open file %s\n", filename), 0);

    char *line;
    int ambient_count = 0;
    int camera_count = 0;
    int light_count = 0;
    int has_object = 0;

    while ((line = get_next_line(fd)))
    {
        char *trim = ft_strtrim(line, " \t\n");
        free(line);
        if (!trim || trim[0] == '\0') { free(trim); continue; } // пустая строка

        if (trim[0] == 'A') ambient_count++;
        else if (trim[0] == 'C') camera_count++;
        else if (trim[0] == 'L') light_count++;
        else if (ft_strncmp(trim, "sp", 2) == 0 || 
                ft_strncmp(trim, "pl", 2) == 0 || 
                ft_strncmp(trim, "cy", 2) == 0 ||
                ft_strncmp(trim, "tr", 2) == 0)
            has_object = 1;

        free(trim); 
    }
    close(fd);

    if (ambient_count > 1)
        return (printf("Error: Too many ambient lights\n"), 0);
    if (camera_count > 1)
        return (printf("Error: Too many cameras\n"), 0);
    if (light_count > 1)
        return (printf("Error: Too many lights\n"), 0);
    if (!has_object)
        return (printf("Error: Scene must contain at least one object\n"), 0);

    return (1);
}


int check_vec3_range(t_vec3 v, double min, double max)
{
    return (v.x >= min && v.x <= max &&
            v.y >= min && v.y <= max &&
            v.z >= min && v.z <= max);
}


int is_file_empty(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return (1);
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return (size == 0);
}

static int is_valid_identifier(const char *id)
{
    return (
        ft_strcmp(id, "A") == 0 ||
        ft_strcmp(id, "C") == 0 ||
        ft_strcmp(id, "L") == 0 ||
        ft_strcmp(id, "sp") == 0 ||
        ft_strcmp(id, "pl") == 0 ||
        ft_strcmp(id, "cy") == 0 ||
        ft_strcmp(id, "tr") == 0
    );
}

int validate_line_tokens(char **tokens)
{
    int count = 0;
    while (tokens[count])
        count++;
    if (!is_valid_identifier(tokens[0]))
    {
       ft_printf("Error: element '%s' has an invalid identifier\n", tokens[0]);
        return (0);
    }
    /*if (ft_strcmp(tokens[0], "A") == 0 && count != 3)
        return (printf("Error: Ambient must have 3 parameters\n"), 0);
    if (ft_strcmp(tokens[0], "C") == 0 && count != 4)
        return (printf("Error: Camera must have 4 parameters\n"), 0);
    if (ft_strcmp(tokens[0], "L") == 0 && count != 4)
        return (printf("Error: Light must have 4 parameters\n"), 0);
    if (ft_strcmp(tokens[0], "sp") == 0 && count != 4)
        return (printf("Error: Sphere must have 4 parameters\n"), 0);
    if (ft_strcmp(tokens[0], "pl") == 0 && count != 4)
        return (printf("Error: Plane must have 4 parameters\n"), 0);
    if (ft_strcmp(tokens[0], "cy") == 0 && count != 6)
        return (printf("Error: Cylinder must have 6 parameters\n"), 0);*/
    return (1);
}
