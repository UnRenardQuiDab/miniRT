/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:19:14 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/12 09:54:23 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

static void	mat4_inverse_col1(t_mat4 m, t_mat4 *inv)
{
	inv->matrix[0] = m.matrix[5] * m.matrix[10] * m.matrix[15]
		- m.matrix[5] * m.matrix[11] * m.matrix[14]
		- m.matrix[9] * m.matrix[6] * m.matrix[15]
		+ m.matrix[9] * m.matrix[7] * m.matrix[14]
		+ m.matrix[13] * m.matrix[6] * m.matrix[11]
		- m.matrix[13] * m.matrix[7] * m.matrix[10];
	inv->matrix[4] = -m.matrix[4] * m.matrix[10] * m.matrix[15]
		+ m.matrix[4] * m.matrix[11] * m.matrix[14]
		+ m.matrix[8] * m.matrix[6] * m.matrix[15]
		- m.matrix[8] * m.matrix[7] * m.matrix[14]
		- m.matrix[12] * m.matrix[6] * m.matrix[11]
		+ m.matrix[12] * m.matrix[7] * m.matrix[10];
	inv->matrix[8] = m.matrix[4] * m.matrix[9] * m.matrix[15]
		- m.matrix[4] * m.matrix[11] * m.matrix[13]
		- m.matrix[8] * m.matrix[5] * m.matrix[15]
		+ m.matrix[8] * m.matrix[7] * m.matrix[13]
		+ m.matrix[12] * m.matrix[5] * m.matrix[11]
		- m.matrix[12] * m.matrix[7] * m.matrix[9];
	inv->matrix[12] = -m.matrix[4] * m.matrix[9] * m.matrix[14]
		+ m.matrix[4] * m.matrix[10] * m.matrix[13]
		+ m.matrix[8] * m.matrix[5] * m.matrix[14]
		- m.matrix[8] * m.matrix[6] * m.matrix[13]
		- m.matrix[12] * m.matrix[5] * m.matrix[10]
		+ m.matrix[12] * m.matrix[6] * m.matrix[9];
}

static void	mat4_inverse_col2(t_mat4 m, t_mat4 *inv)
{
	inv->matrix[1] = -m.matrix[1] * m.matrix[10] * m.matrix[15]
		+ m.matrix[1] * m.matrix[11] * m.matrix[14]
		+ m.matrix[9] * m.matrix[2] * m.matrix[15]
		- m.matrix[9] * m.matrix[3] * m.matrix[14]
		- m.matrix[13] * m.matrix[2] * m.matrix[11]
		+ m.matrix[13] * m.matrix[3] * m.matrix[10];
	inv->matrix[5] = m.matrix[0] * m.matrix[10] * m.matrix[15]
		- m.matrix[0] * m.matrix[11] * m.matrix[14]
		- m.matrix[8] * m.matrix[2] * m.matrix[15]
		+ m.matrix[8] * m.matrix[3] * m.matrix[14]
		+ m.matrix[12] * m.matrix[2] * m.matrix[11]
		- m.matrix[12] * m.matrix[3] * m.matrix[10];
	inv->matrix[9] = -m.matrix[0] * m.matrix[9] * m.matrix[15]
		+ m.matrix[0] * m.matrix[11] * m.matrix[13]
		+ m.matrix[8] * m.matrix[1] * m.matrix[15]
		- m.matrix[8] * m.matrix[3] * m.matrix[13]
		- m.matrix[12] * m.matrix[1] * m.matrix[11]
		+ m.matrix[12] * m.matrix[3] * m.matrix[9];
	inv->matrix[13] = m.matrix[0] * m.matrix[9] * m.matrix[14]
		- m.matrix[0] * m.matrix[10] * m.matrix[13]
		- m.matrix[8] * m.matrix[1] * m.matrix[14]
		+ m.matrix[8] * m.matrix[2] * m.matrix[13]
		+ m.matrix[12] * m.matrix[1] * m.matrix[10]
		- m.matrix[12] * m.matrix[2] * m.matrix[9];
}

static void	mat4_inverse_col3(t_mat4 m, t_mat4 *inv)
{
	inv->matrix[2] = m.matrix[1] * m.matrix[6] * m.matrix[15]
		- m.matrix[1] * m.matrix[7] * m.matrix[14]
		- m.matrix[5] * m.matrix[2] * m.matrix[15]
		+ m.matrix[5] * m.matrix[3] * m.matrix[14]
		+ m.matrix[13] * m.matrix[2] * m.matrix[7]
		-m.matrix[13] * m.matrix[3] * m.matrix[6];
	inv->matrix[6] = -m.matrix[0] * m.matrix[6] * m.matrix[15]
		+ m.matrix[0] * m.matrix[7] * m.matrix[14]
		+ m.matrix[4] * m.matrix[2] * m.matrix[15]
		- m.matrix[4] * m.matrix[3] * m.matrix[14]
		- m.matrix[12] * m.matrix[2] * m.matrix[7]
		+ m.matrix[12] * m.matrix[3] * m.matrix[6];
	inv->matrix[10] = m.matrix[0] * m.matrix[5] * m.matrix[15]
		- m.matrix[0] * m.matrix[7] * m.matrix[13]
		- m.matrix[4] * m.matrix[1] * m.matrix[15]
		+ m.matrix[4] * m.matrix[3] * m.matrix[13]
		+ m.matrix[12] * m.matrix[1] * m.matrix[7]
		- m.matrix[12] * m.matrix[3] * m.matrix[5];
	inv->matrix[14] = -m.matrix[0] * m.matrix[5] * m.matrix[14]
		+ m.matrix[0] * m.matrix[6] * m.matrix[13]
		+ m.matrix[4] * m.matrix[1] * m.matrix[14]
		- m.matrix[4] * m.matrix[2] * m.matrix[13]
		- m.matrix[12] * m.matrix[1] * m.matrix[6]
		+ m.matrix[12] * m.matrix[2] * m.matrix[5];
}

static void	mat4_inverse_col4(t_mat4 m, t_mat4 *inv)
{
	inv->matrix[3] = -m.matrix[1] * m.matrix[6] * m.matrix[11]
		+ m.matrix[1] * m.matrix[7] * m.matrix[10]
		+ m.matrix[5] * m.matrix[2] * m.matrix[11]
		- m.matrix[5] * m.matrix[3] * m.matrix[10]
		- m.matrix[9] * m.matrix[2] * m.matrix[7]
		+ m.matrix[9] * m.matrix[3] * m.matrix[6];
	inv->matrix[7] = m.matrix[0] * m.matrix[6] * m.matrix[11]
		- m.matrix[0] * m.matrix[7] * m.matrix[10]
		- m.matrix[4] * m.matrix[2] * m.matrix[11]
		+ m.matrix[4] * m.matrix[3] * m.matrix[10]
		+ m.matrix[8] * m.matrix[2] * m.matrix[7]
		- m.matrix[8] * m.matrix[3] * m.matrix[6];
	inv->matrix[11] = -m.matrix[0] * m.matrix[5] * m.matrix[11]
		+ m.matrix[0] * m.matrix[7] * m.matrix[9]
		+ m.matrix[4] * m.matrix[1] * m.matrix[11]
		- m.matrix[4] * m.matrix[3] * m.matrix[9]
		- m.matrix[8] * m.matrix[1] * m.matrix[7]
		+ m.matrix[8] * m.matrix[3] * m.matrix[5];
	inv->matrix[15] = m.matrix[0] * m.matrix[5] * m.matrix[10]
		- m.matrix[0] * m.matrix[6] * m.matrix[9]
		- m.matrix[4] * m.matrix[1] * m.matrix[10]
		+ m.matrix[4] * m.matrix[2] * m.matrix[9]
		+ m.matrix[8] * m.matrix[1] * m.matrix[6]
		- m.matrix[8] * m.matrix[2] * m.matrix[5];
}

t_mat4	mat4_inverse(t_mat4 m)
{
	t_mat4	inv;
	t_mat4	inv_out;
	double	det;
	int		i;

	mat4_inverse_col1(m, &inv);
	mat4_inverse_col2(m, &inv);
	mat4_inverse_col3(m, &inv);
	mat4_inverse_col4(m, &inv);
	det = m.matrix[0] * inv.matrix[0] + m.matrix[1] * inv.matrix[4]
		+ m.matrix[2] * inv.matrix[8] + m.matrix[3] * inv.matrix[12];
	det = 1.0 / det;
	i = 0;
	while (i < 16)
	{
		inv_out.matrix[i] = inv.matrix[i] * det;
		i++;
	}
	return (inv_out);
}
