/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   product.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:13:35 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/22 18:58:32 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "vec.h"
#include "matrix.h"

t_vec3	vec3_product(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3	mat3vec3_product(t_vec3 vec, t_mat3 mat)
{
	size_t	i;
	size_t	y;
	t_vec3	product_vec;

	i = 0;
	while (i < 3)
	{
		product_vec.arr[i] = 0;
		y = 0;
		while (y < 3)
		{
			product_vec.arr[i] += vec.arr[y] * mat.matrix[y + i * 3];
			y++;
		}
		i++;
	}
	return (product_vec);
}

t_vec4	mat4vec4_product(t_vec4 vec, t_mat4 mat)
{
	size_t	i;
	size_t	y;
	t_vec4	product_vec;

	i = 0;
	while (i < 4)
	{
		product_vec.arr[i] = 0;
		y = 0;
		while (y < 4)
		{
			product_vec.arr[i] += vec.arr[y] * mat.matrix[y + i * 4];
			y++;
		}
		i++;
	}
	return (product_vec);
}
