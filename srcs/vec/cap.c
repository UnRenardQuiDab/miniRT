/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:10:34 by lcottet           #+#    #+#             */
/*   Updated: 2024/11/21 16:13:58 by lcottet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec3	vec3_cap(t_vec3 vec, double min, double max)
{
	uint8_t	i;

	i = 0;
	while (i < 3)
	{
		if (vec.arr[i] < min)
			vec.arr[i] = min;
		if (vec.arr[i] > max)
			vec.arr[i] = max;
		++i;
	}
	return (vec);
}
