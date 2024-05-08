/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:55:45 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/08 15:50:30 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "engine.h"

# define FLT_MAX __FLT_MAX__
# define FLT_MIN -FLT_MAX

typedef union u_range
{
	struct s_int
	{
		int32_t	min;
		int32_t	max;
	}	t_int;
	struct s_float
	{
		float	min;
		float	max;
	}	t_float;
}	t_range;

typedef enum u_dectype
{
	FLOAT,
	INT
}	t_dectype;

uint8_t	str_to_decimal(void *num, char *str, t_dectype type, t_range range);
uint8_t	ft_atov3(t_vec3 *vec, char *arg, t_range range);
uint8_t	ft_atoc(t_color *color, char *arg);
t_range	rangef(float min, float max);
t_range	rangei(int32_t min, int32_t max);

void	init_engine(t_engine *engine);

uint8_t	parsing(t_engine *engine, char *file_name);

#endif