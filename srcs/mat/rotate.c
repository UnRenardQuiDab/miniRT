/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:07:59 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/11 05:35:02 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "matrix.h"
#include "vec.h"

t_mat4	mat4_rotate(t_mat4 mat, float angle, t_vec3 vec)
{
	float	cosine;
	float	sine;
	t_mat4	rotation;

	cosine = cos(angle);
	sine = sin(angle);
	rotation.matrix[0] = vec.x * vec.x + (1 - vec.x * vec.x) * cosine;
	rotation.matrix[4] = vec.x * vec.y * (1 - cosine) + vec.z * sine;
	rotation.matrix[8] = vec.x * vec.z * (1 - cosine) - vec.y * sine;
	rotation.matrix[1] = vec.x * vec.y
		* (1 - cosine) - vec.z * sine;
	rotation.matrix[5] = vec.y * vec.y + (1 - vec.y * vec.y) * cosine;
	rotation.matrix[9] = vec.y * vec.z
		* (1 - cosine) + vec.x * sine;
	rotation.matrix[2] = vec.x * vec. z
		* (1 - cosine) + vec.y * sine;
	rotation.matrix[6] = vec.y * vec.z
		* (1 - cosine) - vec.x * sine;
	rotation.matrix[10] = vec.z * vec.z + (1 - vec.z * vec.z) * cosine;
	rotation.matrix[15] = 1.0;
	return (mat4_multiply(mat, rotation));
}
