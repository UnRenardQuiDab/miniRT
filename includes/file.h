/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:55:45 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/23 15:53:18 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "engine.h"

typedef union u_range
{
	struct s_int
	{
		int32_t	min;
		int32_t	max;
	}	t_int;
	struct s_double
	{
		double	min;
		double	max;
	}	t_double;
}	t_range;

typedef enum u_dectype
{
	FLOAT,
	INT
}	t_dectype;

uint8_t	str_to_decimal(void *num, char *str, t_dectype type, t_range range);
uint8_t	ft_atov3(t_vec3 *vec, char *arg, t_range range);
uint8_t	ft_atoc(t_color *color, char *arg);
uint8_t	ft_atom(t_engine *engine, t_material *material, char *arg);
t_range	rangef(double min, double max);
t_range	rangei(int32_t min, int32_t max);

void	init_engine(t_engine *engine);

uint8_t	parsing(t_engine *engine, char *file_name);

#endif