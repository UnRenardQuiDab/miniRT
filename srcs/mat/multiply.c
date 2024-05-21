/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:28:06 by lcottet           #+#    #+#             */
/*   Updated: 2024/05/21 17:37:34 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "matrix.h"

t_mat3	mat3_multiply(t_mat3 a, t_mat3 b)
{
	t_mat3		res;
	size_t		i;

	i = 0;
	while (i < 3)
	{
		res.matrix[i] = a.matrix[i] * b.matrix[0] + a.matrix[i + 3]
			* b.matrix[1] + a.matrix[i + 6] * b.matrix[2];
		res.matrix[i + 3] = a.matrix[i] * b.matrix[3] + a.matrix[i + 3]
			* b.matrix[4] + a.matrix[i + 6] * b.matrix[5];
		res.matrix[i + 6] = a.matrix[i] * b.matrix[6] + a.matrix[i + 3]
			* b.matrix[7] + a.matrix[i + 6] * b.matrix[8];
		i++;
	}
	return (res);
}

t_mat4	mat4_multiply(t_mat4 a, t_mat4 b)
{
	t_mat4		res;
	size_t		i;

	i = 0;
	while (i < 4)
	{
		res.matrix[i] = a.matrix[i] * b.matrix[0] + a.matrix[i + 4]
			* b.matrix[1] + a.matrix[i + 8] * b.matrix[2] + a.matrix[i + 12]
			* b.matrix[3];
		res.matrix[i + 4] = a.matrix[i] * b.matrix[4] + a.matrix[i + 4]
			* b.matrix[5] + a.matrix[i + 8] * b.matrix[6] + a.matrix[i + 12]
			* b.matrix[7];
		res.matrix[i + 8] = a.matrix[i] * b.matrix[8] + a.matrix[i + 4]
			* b.matrix[9] + a.matrix[i + 8] * b.matrix[10] + a.matrix[i + 12]
			* b.matrix[11];
		res.matrix[i + 12] = a.matrix[i] * b.matrix[12] + a.matrix[i + 4]
			* b.matrix[13] + a.matrix[i + 8] * b.matrix[14] + a.matrix[i + 12]
			* b.matrix[15];
		i++;
	}
	return (res);
}
