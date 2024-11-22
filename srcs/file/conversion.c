/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 18:38:16 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/28 16:46:34 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_error.h"
#include "libft.h"
#include "file.h"
#include "engine.h"

//str_to_decimal(&double, str, DEC_FLOAT);
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
		*((double *) num) = ft_atof(str);
		if (*((double *) num) < range.t_double.min
			|| *((double *) num) > range.t_double.max)
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

uint8_t	ft_atom(t_engine *engine, t_material *material, char *arg)
{
	size_t		comma_count;
	size_t		i;
	t_material	*mat;

	ft_memset(material, 0, sizeof(t_material));
	material->opacity = 1.0f;
	i = 0;
	comma_count = 0;
	while (arg[i])
	{
		if (arg[i] == ',')
			comma_count++;
		i++;
	}
	if (comma_count == 2)
		return (ft_atoc(&material->color, arg));
	else if (comma_count != 0)
		return (custom_error(arg, ERR_VALUE_COUNT));
	if (str_to_decimal(&i, arg, INT, rangei(INT32_MIN, INT32_MAX)) == FAILURE)
		return (FAILURE);
	mat = get_material(engine, i);
	if (!mat)
		return (custom_error(arg, ERR_MATERIAL_NOT_FOUND));
	*material = *mat;
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
