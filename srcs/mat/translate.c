/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 22:12:47 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/11 05:32:43 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "vec.h"

t_mat4	mat4_translate(t_mat4 mat, t_vec3 vec)
{
	t_mat4	translation;

	translation = mat4_identity();
	translation.matrix[3] = vec.x;
	translation.matrix[7] = vec.y;
	translation.matrix[11] = vec.z;
	return (mat4_multiply(mat, translation));
}
