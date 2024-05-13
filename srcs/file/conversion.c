/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:38:16 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/07 23:50:16 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_error.h"
#include "libft.h"
#include "file.h"
#include "engine.h"

//str_to_decimal(&float, str, DEC_FLOAT);
//str_to_decmial(&int, str, DEC_INT);
static uint8_t	is_str_valid(char *str, t_dectype type)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '.' && type == FLOAT)
	{
		i++;
		while (ft_isdigit(str[i]))
			i++;
	}
	if (str[i] == '\0' || str[i] == '\n')
		return (SUCCESS);
	return (FAILURE);
}

uint8_t	str_to_decimal(void *num, char *str, t_dectype type, t_range range)
{
	if (is_str_valid(str, type) == FAILURE)
	{
		if (type == INT)
			return (custom_error(str, ERR_INVALID_INT));
		else
			return (custom_error(str, ERR_INVALID_FLOAT));
	}
	if (type == FLOAT)
	{
		*((float *) num) = ft_atof(str);
		if (*((float *) num) < range.t_float.min
			|| *((float *) num) > range.t_float.max)
			return (custom_error(str, ERR_RANGE));
	}
	else if (type == INT)
	{
		*((int32_t *) num) = ft_atoi(str);
		if (*((int32_t *) num) > range.t_int.max
			|| *((int32_t *) num) < range.t_int.min)
			return (custom_error(str, ERR_RANGE));
	}
	return (SUCCESS);
}

uint8_t	ft_atov3(t_vec3 *vec, char *arg, t_range range)
{
	char	**split_arg;
	size_t	i;

	split_arg = ft_split(arg, ',');
	if (!split_arg)
		return (err("split"));
	if (ft_arrlen(split_arg, sizeof(char *)) != 3)
	{
		ft_freesplit(split_arg);
		return (custom_error(arg, ERR_VALUE_COUNT));
	}
	i = 0;
	while (i < 3)
	{
		if (str_to_decimal(&vec->arr[i], split_arg[i], FLOAT, range) == FAILURE)
		{
			ft_freesplit(split_arg);
			return (FAILURE);
		}
		i++;
	}
	ft_freesplit(split_arg);
	return (SUCCESS);
}

uint8_t	ft_atoc(t_color *color, char *arg)
{
	char	**split_arg;
	size_t	i;

	split_arg = ft_split(arg, ',');
	if (!split_arg)
		return (err("split"));
	if (ft_arrlen(split_arg, sizeof(char *)) != 3)
	{
		ft_freesplit(split_arg);
		return (custom_error(arg, ERR_VALUE_COUNT));
	}
	i = 0;
	while (i < 3)
	{
		if (str_to_decimal(&color->arr[i], split_arg[2 - i],
				INT, rangei(0, 255)) == FAILURE)
		{
			ft_freesplit(split_arg);
			return (FAILURE);
		}
		i++;
	}
	color->a = 255;
	ft_freesplit(split_arg);
	return (SUCCESS);
}
