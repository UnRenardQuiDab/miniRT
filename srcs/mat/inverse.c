/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:19:14 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/11 07:59:11 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "float.h"
#include "libft.h"
#include "matrix.h"
#include <stdbool.h>

// static void	swap_pivot(t_mat4 *matrix, t_mat4 *identity, int current_row)
// {
// 	int		row;
// 	int		column;
// 	float	temp;

// 	row = current_row;
// 	while (row < 4 && matrix->matrix[row * 4 + current_row] == 0)
// 		row++;
// 	column = 0;
// 	while (column < 4)
// 	{
// 		temp = matrix->matrix[row * 4 + column];
// 		matrix->matrix[row * 4 + column] = matrix->matrix[current_row * 4 + column];
// 		matrix->matrix[current_row * 4 + column] = temp;
// 		column++;
// 	}
// 	column = 0;
// 	while (column < 4)
// 	{
// 		temp = identity->matrix[row * 4 + column];
// 		identity->matrix[row * 4 + column] = identity->matrix[current_row * 4 + column];
// 		identity->matrix[current_row * 4 + column] = temp;
// 		column++;
// 	}
// }

// static void	multiply_row(t_mat4 *matrix, int row, float factor)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		matrix->matrix[row * 4 + i] *= factor;
// 		i++;
// 	}
// }

// static void	sum_column(t_mat4 *matrix, int x, int y, float factor)
// {
// 	int	i;

// 	i = 0;
// 	while (i < 4)
// 	{
// 		matrix->matrix[y * 4 + i] -= factor * matrix->matrix[x * 4 + i];
// 		i++;
// 	}
// }

// static void	set_column_to_zero(t_mat4 *matrix, t_mat4 *identity_matrix,
// 								int x)
// {
// 	int	y;

// 	y = 0;
// 	while (y < 4)
// 	{
// 		if (x != y)
// 		{
// 			sum_column(identity_matrix, x, y, matrix->matrix[y * 4 + x]);
// 			sum_column(matrix, x, y, matrix->matrix[y * 4 + x]);
// 		}
// 		y++;
// 	}
// }

// t_mat4	mat4_inverse(t_mat4 matrix)
// {
// 	t_mat4		identity;
// 	int			x;
// 	float		pivot;
// 	float		factor;

// 	identity = mat4_identity();
// 	x = 0;
// 	while (x < 4)
// 	{
// 		pivot = matrix.matrix[x + 4 * x];
// 		if (ft_istolerated(pivot, 0.0f, FLT_EPSILON))
// 		{
// 			matrix.matrix[x + 4 * x] = 0;
// 			swap_pivot(&matrix, &identity, x);
// 		}
// 		factor = 1 / matrix.matrix[x + 4 * x];
// 		multiply_row(&identity, x, factor);
// 		multiply_row(&matrix, x, factor);
// 		set_column_to_zero(&matrix, &identity, x);
// 		x++;
// 	}
// 	return (identity);
// }

	// t_mat4	mat4_devide(t_mat4 a, float b)
	// {
	// 	t_mat4		res;
	// 	size_t		i;

	// 	i = 0;
	// 	while (i < 4)
	// 	{
	// 		res.matrix[i * 4 + 0] = a.matrix[i * 4 + 0] / b;
	// 		res.matrix[i * 4 + 1] = a.matrix[i * 4 + 1] / b;
	// 		res.matrix[i * 4 + 2] = a.matrix[i * 4 + 2] / b;
	// 		res.matrix[i * 4 + 3] = a.matrix[i * 4 + 3] / b;
	// 		i++;
	// 	}
	// 	return (res);
	// }

	// t_mat4	mat4_inverse(t_mat4 m){
	// 		float SubFactor00 = m.matrix[2 * 4 + 2] * m.matrix[3 * 4 + 3] - m.matrix[3 * 4 + 2] * m.matrix[2 * 4 + 3];
	// 		float SubFactor01 = m.matrix[2 * 4 + 1] * m.matrix[3 * 4 + 3] - m.matrix[3 * 4 + 1] * m.matrix[2 * 4 + 3];
	// 		float SubFactor02 = m.matrix[2 * 4 + 1] * m.matrix[3 * 4 + 2] - m.matrix[3 * 4 + 1] * m.matrix[2 * 4 + 2];
	// 		float SubFactor03 = m.matrix[2 * 4 + 0] * m.matrix[3 * 4 + 3] - m.matrix[3 * 4 + 0] * m.matrix[2 * 4 + 3];
	// 		float SubFactor04 = m.matrix[2 * 4 + 0] * m.matrix[3 * 4 + 2] - m.matrix[3 * 4 + 0] * m.matrix[2 * 4 + 2];
	// 		float SubFactor05 = m.matrix[2 * 4 + 0] * m.matrix[3 * 4 + 1] - m.matrix[3 * 4 + 0] * m.matrix[2 * 4 + 1];
	// 		float SubFactor06 = m.matrix[1 * 4 + 2] * m.matrix[3 * 4 + 3] - m.matrix[3 * 4 + 2] * m.matrix[1 * 4 + 3];
	// 		float SubFactor07 = m.matrix[1 * 4 + 1] * m.matrix[3 * 4 + 3] - m.matrix[3 * 4 + 1] * m.matrix[1 * 4 + 3];
	// 		float SubFactor08 = m.matrix[1 * 4 + 1] * m.matrix[3 * 4 + 2] - m.matrix[3 * 4 + 1] * m.matrix[1 * 4 + 2];
	// 		float SubFactor09 = m.matrix[1 * 4 + 0] * m.matrix[3 * 4 + 3] - m.matrix[3 * 4 + 0] * m.matrix[1 * 4 + 3];
	// 		float SubFactor10 = m.matrix[1 * 4 + 0] * m.matrix[3 * 4 + 2] - m.matrix[3 * 4 + 0] * m.matrix[1 * 4 + 2];
	// 		float SubFactor11 = m.matrix[1 * 4 + 0] * m.matrix[3 * 4 + 1] - m.matrix[3 * 4 + 0] * m.matrix[1 * 4 + 1];
	// 		float SubFactor12 = m.matrix[1 * 4 + 2] * m.matrix[2 * 4 + 3] - m.matrix[2 * 4 + 2] * m.matrix[1 * 4 + 3];
	// 		float SubFactor13 = m.matrix[1 * 4 + 1] * m.matrix[2 * 4 + 3] - m.matrix[2 * 4 + 1] * m.matrix[1 * 4 + 3];
	// 		float SubFactor14 = m.matrix[1 * 4 + 1] * m.matrix[2 * 4 + 2] - m.matrix[2 * 4 + 1] * m.matrix[1 * 4 + 2];
	// 		float SubFactor15 = m.matrix[1 * 4 + 0] * m.matrix[2 * 4 + 3] - m.matrix[2 * 4 + 0] * m.matrix[1 * 4 + 3];
	// 		float SubFactor16 = m.matrix[1 * 4 + 0] * m.matrix[2 * 4 + 2] - m.matrix[2 * 4 + 0] * m.matrix[1 * 4 + 2];
	// 		float SubFactor17 = m.matrix[1 * 4 + 0] * m.matrix[2 * 4 + 1] - m.matrix[2 * 4 + 0] * m.matrix[1 * 4 + 1];

	// 		t_mat4 Inverse;
	// 		Inverse.matrix[0 * 4 + 0] = + (m.matrix[1 * 4 + 1] * SubFactor00 - m.matrix[1 * 4 + 2] * SubFactor01 + m.matrix[1 * 4 + 3] * SubFactor02);
	// 		Inverse.matrix[0 * 4 + 1] = - (m.matrix[1 * 4 + 0] * SubFactor00 - m.matrix[1 * 4 + 2] * SubFactor03 + m.matrix[1 * 4 + 3] * SubFactor04);
	// 		Inverse.matrix[0 * 4 + 2] = + (m.matrix[1 * 4 + 0] * SubFactor01 - m.matrix[1 * 4 + 1] * SubFactor03 + m.matrix[1 * 4 + 3] * SubFactor05);
	// 		Inverse.matrix[0 * 4 + 3] = - (m.matrix[1 * 4 + 0] * SubFactor02 - m.matrix[1 * 4 + 1] * SubFactor04 + m.matrix[1 * 4 + 2] * SubFactor05);

	// 		Inverse.matrix[1 * 4 + 0] = - (m.matrix[0 * 4 + 1] * SubFactor00 - m.matrix[0 * 4 + 2] * SubFactor01 + m.matrix[0 * 4 + 3] * SubFactor02);
	// 		Inverse.matrix[1 * 4 + 1] = + (m.matrix[0 * 4 + 0] * SubFactor00 - m.matrix[0 * 4 + 2] * SubFactor03 + m.matrix[0 * 4 + 3] * SubFactor04);
	// 		Inverse.matrix[1 * 4 + 2] = - (m.matrix[0 * 4 + 0] * SubFactor01 - m.matrix[0 * 4 + 1] * SubFactor03 + m.matrix[0 * 4 + 3] * SubFactor05);
	// 		Inverse.matrix[1 * 4 + 3] = + (m.matrix[0 * 4 + 0] * SubFactor02 - m.matrix[0 * 4 + 1] * SubFactor04 + m.matrix[0 * 4 + 2] * SubFactor05);

	// 		Inverse.matrix[2 * 4 + 0] = + (m.matrix[0 * 4 + 1] * SubFactor06 - m.matrix[0 * 4 + 2] * SubFactor07 + m.matrix[0 * 4 + 3] * SubFactor08);
	// 		Inverse.matrix[2 * 4 + 1] = - (m.matrix[0 * 4 + 0] * SubFactor06 - m.matrix[0 * 4 + 2] * SubFactor09 + m.matrix[0 * 4 + 3] * SubFactor10);
	// 		Inverse.matrix[2 * 4 + 2] = + (m.matrix[0 * 4 + 0] * SubFactor07 - m.matrix[0 * 4 + 1] * SubFactor09 + m.matrix[0 * 4 + 3] * SubFactor11);
	// 		Inverse.matrix[2 * 4 + 3] = - (m.matrix[0 * 4 + 0] * SubFactor08 - m.matrix[0 * 4 + 1] * SubFactor10 + m.matrix[0 * 4 + 2] * SubFactor11);

	// 		Inverse.matrix[3 * 4 + 0] = - (m.matrix[0 * 4 + 1] * SubFactor12 - m.matrix[0 * 4 + 2] * SubFactor13 + m.matrix[0 * 4 + 3] * SubFactor14);
	// 		Inverse.matrix[3 * 4 + 1] = + (m.matrix[0 * 4 + 0] * SubFactor12 - m.matrix[0 * 4 + 2] * SubFactor15 + m.matrix[0 * 4 + 3] * SubFactor16);
	// 		Inverse.matrix[3 * 4 + 2] = - (m.matrix[0 * 4 + 0] * SubFactor13 - m.matrix[0 * 4 + 1] * SubFactor15 + m.matrix[0 * 4 + 3] * SubFactor17);
	// 		Inverse.matrix[3 * 4 + 3] = + (m.matrix[0 * 4 + 0] * SubFactor14 - m.matrix[0 * 4 + 1] * SubFactor16 + m.matrix[0 * 4 + 2] * SubFactor17);

	// 		float Determinant =
	// 			+ m.matrix[0 * 4 + 0] * Inverse.matrix[0 * 4 + 0]
	// 			+ m.matrix[0 * 4 + 1] * Inverse.matrix[0 * 4 + 1]
	// 			+ m.matrix[0 * 4 + 2] * Inverse.matrix[0 * 4 + 2]
	// 			+ m.matrix[0 * 4 + 3] * Inverse.matrix[0 * 4 + 3];

	// 		Inverse = mat4_devide(Inverse, Determinant);
	// 		return Inverse;
	// 	}

		
t_mat4 mat4_inverse(t_mat4 m)
{
    t_mat4 inv;
	float det;
    t_mat4 invOut;
	int i;

    inv.matrix[0] = m.matrix[5]  * m.matrix[10] * m.matrix[15] - 
             m.matrix[5]  * m.matrix[11] * m.matrix[14] - 
             m.matrix[9]  * m.matrix[6]  * m.matrix[15] + 
             m.matrix[9]  * m.matrix[7]  * m.matrix[14] +
             m.matrix[13] * m.matrix[6]  * m.matrix[11] - 
             m.matrix[13] * m.matrix[7]  * m.matrix[10];

    inv.matrix[4] = -m.matrix[4]  * m.matrix[10] * m.matrix[15] + 
              m.matrix[4]  * m.matrix[11] * m.matrix[14] + 
              m.matrix[8]  * m.matrix[6]  * m.matrix[15] - 
              m.matrix[8]  * m.matrix[7]  * m.matrix[14] - 
              m.matrix[12] * m.matrix[6]  * m.matrix[11] + 
              m.matrix[12] * m.matrix[7]  * m.matrix[10];

    inv.matrix[8] = m.matrix[4]  * m.matrix[9] * m.matrix[15] - 
             m.matrix[4]  * m.matrix[11] * m.matrix[13] - 
             m.matrix[8]  * m.matrix[5] * m.matrix[15] + 
             m.matrix[8]  * m.matrix[7] * m.matrix[13] + 
             m.matrix[12] * m.matrix[5] * m.matrix[11] - 
             m.matrix[12] * m.matrix[7] * m.matrix[9];

    inv.matrix[12] = -m.matrix[4]  * m.matrix[9] * m.matrix[14] + 
               m.matrix[4]  * m.matrix[10] * m.matrix[13] +
               m.matrix[8]  * m.matrix[5] * m.matrix[14] - 
               m.matrix[8]  * m.matrix[6] * m.matrix[13] - 
               m.matrix[12] * m.matrix[5] * m.matrix[10] + 
               m.matrix[12] * m.matrix[6] * m.matrix[9];

    inv.matrix[1] = -m.matrix[1]  * m.matrix[10] * m.matrix[15] + 
              m.matrix[1]  * m.matrix[11] * m.matrix[14] + 
              m.matrix[9]  * m.matrix[2] * m.matrix[15] - 
              m.matrix[9]  * m.matrix[3] * m.matrix[14] - 
              m.matrix[13] * m.matrix[2] * m.matrix[11] + 
              m.matrix[13] * m.matrix[3] * m.matrix[10];

    inv.matrix[5] = m.matrix[0]  * m.matrix[10] * m.matrix[15] - 
             m.matrix[0]  * m.matrix[11] * m.matrix[14] - 
             m.matrix[8]  * m.matrix[2] * m.matrix[15] + 
             m.matrix[8]  * m.matrix[3] * m.matrix[14] + 
             m.matrix[12] * m.matrix[2] * m.matrix[11] - 
             m.matrix[12] * m.matrix[3] * m.matrix[10];

    inv.matrix[9] = -m.matrix[0]  * m.matrix[9] * m.matrix[15] + 
              m.matrix[0]  * m.matrix[11] * m.matrix[13] + 
              m.matrix[8]  * m.matrix[1] * m.matrix[15] - 
              m.matrix[8]  * m.matrix[3] * m.matrix[13] - 
              m.matrix[12] * m.matrix[1] * m.matrix[11] + 
              m.matrix[12] * m.matrix[3] * m.matrix[9];

    inv.matrix[13] = m.matrix[0]  * m.matrix[9] * m.matrix[14] - 
              m.matrix[0]  * m.matrix[10] * m.matrix[13] - 
              m.matrix[8]  * m.matrix[1] * m.matrix[14] + 
              m.matrix[8]  * m.matrix[2] * m.matrix[13] + 
              m.matrix[12] * m.matrix[1] * m.matrix[10] - 
              m.matrix[12] * m.matrix[2] * m.matrix[9];

    inv.matrix[2] = m.matrix[1]  * m.matrix[6] * m.matrix[15] - 
             m.matrix[1]  * m.matrix[7] * m.matrix[14] - 
             m.matrix[5]  * m.matrix[2] * m.matrix[15] + 
             m.matrix[5]  * m.matrix[3] * m.matrix[14] + 
             m.matrix[13] * m.matrix[2] * m.matrix[7] - 
             m.matrix[13] * m.matrix[3] * m.matrix[6];

    inv.matrix[6] = -m.matrix[0]  * m.matrix[6] * m.matrix[15] + 
              m.matrix[0]  * m.matrix[7] * m.matrix[14] + 
              m.matrix[4]  * m.matrix[2] * m.matrix[15] - 
              m.matrix[4]  * m.matrix[3] * m.matrix[14] - 
              m.matrix[12] * m.matrix[2] * m.matrix[7] + 
              m.matrix[12] * m.matrix[3] * m.matrix[6];

    inv.matrix[10] = m.matrix[0]  * m.matrix[5] * m.matrix[15] - 
              m.matrix[0]  * m.matrix[7] * m.matrix[13] - 
              m.matrix[4]  * m.matrix[1] * m.matrix[15] + 
              m.matrix[4]  * m.matrix[3] * m.matrix[13] + 
              m.matrix[12] * m.matrix[1] * m.matrix[7] - 
              m.matrix[12] * m.matrix[3] * m.matrix[5];

    inv.matrix[14] = -m.matrix[0]  * m.matrix[5] * m.matrix[14] + 
               m.matrix[0]  * m.matrix[6] * m.matrix[13] + 
               m.matrix[4]  * m.matrix[1] * m.matrix[14] - 
               m.matrix[4]  * m.matrix[2] * m.matrix[13] - 
               m.matrix[12] * m.matrix[1] * m.matrix[6] + 
               m.matrix[12] * m.matrix[2] * m.matrix[5];

    inv.matrix[3] = -m.matrix[1] * m.matrix[6] * m.matrix[11] + 
              m.matrix[1] * m.matrix[7] * m.matrix[10] + 
              m.matrix[5] * m.matrix[2] * m.matrix[11] - 
              m.matrix[5] * m.matrix[3] * m.matrix[10] - 
              m.matrix[9] * m.matrix[2] * m.matrix[7] + 
              m.matrix[9] * m.matrix[3] * m.matrix[6];

    inv.matrix[7] = m.matrix[0] * m.matrix[6] * m.matrix[11] - 
             m.matrix[0] * m.matrix[7] * m.matrix[10] - 
             m.matrix[4] * m.matrix[2] * m.matrix[11] + 
             m.matrix[4] * m.matrix[3] * m.matrix[10] + 
             m.matrix[8] * m.matrix[2] * m.matrix[7] - 
             m.matrix[8] * m.matrix[3] * m.matrix[6];

    inv.matrix[11] = -m.matrix[0] * m.matrix[5] * m.matrix[11] + 
               m.matrix[0] * m.matrix[7] * m.matrix[9] + 
               m.matrix[4] * m.matrix[1] * m.matrix[11] - 
               m.matrix[4] * m.matrix[3] * m.matrix[9] - 
               m.matrix[8] * m.matrix[1] * m.matrix[7] + 
               m.matrix[8] * m.matrix[3] * m.matrix[5];

    inv.matrix[15] = m.matrix[0] * m.matrix[5] * m.matrix[10] - 
              m.matrix[0] * m.matrix[6] * m.matrix[9] - 
              m.matrix[4] * m.matrix[1] * m.matrix[10] + 
              m.matrix[4] * m.matrix[2] * m.matrix[9] + 
              m.matrix[8] * m.matrix[1] * m.matrix[6] - 
              m.matrix[8] * m.matrix[2] * m.matrix[5];

    det = m.matrix[0] * inv.matrix[0] + m.matrix[1] * inv.matrix[4] + m.matrix[2] * inv.matrix[8] + m.matrix[3] * inv.matrix[12];

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        invOut.matrix[i] = inv.matrix[i] * det;

    return invOut;
}