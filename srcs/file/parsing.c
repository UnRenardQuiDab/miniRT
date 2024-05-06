/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:39:10 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/06 18:57:48 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#include "engine.h"
#include "error.h"
#include "vector.h"
#include "libft.h"
#include "get_next_line.h"

uint8_t check_line_type(t_engine *engine, char **split_line)
{
	size_t	i;

	i = 0;
	while (i < TYPE_COUNT)
	{
		if (ft_strcmp(engine->types[i].name, split_line[0]) == 0)
		{
			if (engine->types[i].args_count != ft_arrlen(split_line, sizeof(char *)))
				return (custom_error("Invalid arg count for type ", engine->types[i].name));
			if (engine->types[i].init(engine, split_line) != 0)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

uint8_t	split_line(t_engine *engine, char *line)
{
	char	**split_line;
	uint8_t	res;

	split_line = ft_split(line, ' ');
	if (!split_line)
	{
		err("split");
		return (FAILURE);
	}
	if (!split_line[0])
	{
		ft_freesplit(split_line);
		return (SUCCESS);
	}
	res = check_line_type(engine, split_line);
	ft_freesplit(split_line);
	return (res);
}

uint8_t	parsing(t_engine *engine, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		err(file_name);
		return (FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (split_line(engine, line) != 0)
		{
			free(line);
			return (FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (SUCCESS);
}
