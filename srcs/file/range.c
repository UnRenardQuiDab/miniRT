/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   range.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 15:04:20 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/07 15:10:24 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"

t_range	rangef(double min, double max)
{
	t_range	range;

	range.t_double.min = min;
	range.t_double.max = max;
	return (range);
}

t_range	rangei(int32_t min, int32_t max)
{
	t_range	range;

	range.t_int.min = min;
	range.t_int.max = max;
	return (range);
}
