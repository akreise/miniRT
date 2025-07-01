/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshcherb <pshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:32:48 by pshcherb          #+#    #+#             */
/*   Updated: 2025/05/12 11:18:49 by pshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static const char	*skip_whitespace_and_sign(const char *str, int *sign)
{
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (str);
}

static double	parse_integer_part(const char **str)
{
	double	result;

	result = 0.0;
	while (ft_isdigit(**str))
	{
		result = (result * 10.0) + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	parse_fractional_part(const char **str)
{
	double	fraction;
	double	result;

	result = 0.0;
	fraction = 1.0;
	if (**str == '.')
	{
		(*str)++;
		while (ft_isdigit(**str))
		{
			fraction /= 10.0;
			result += (**str - '0') * fraction;
			(*str)++;
		}
	}
	return (result);
}

static int	check_trailing_characters(const char *str)
{
	if (*str != '\0' && !ft_isspace(*str))
	{
		ft_printf("Error: Invalid characters after number: %s\n", str);
		return (0);
	}
	return (1);
}

double	ft_atof(const char *str)
{
	double	result;
	double	decimal_part;
	int		sign;

	sign = 1;
	str = skip_whitespace_and_sign(str, &sign);
	result = parse_integer_part(&str);
	decimal_part = parse_fractional_part(&str);
	if (!check_trailing_characters(str))
		return (0.0);
	return ((result + decimal_part) * sign);
}
