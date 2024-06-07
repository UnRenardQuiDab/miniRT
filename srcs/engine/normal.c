/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:20:38 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/24 20:54:40 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "matrix.h"

static t_vec3	vec3_mat3_dot_vec3(t_vec3 vec, t_mat3 mat)
{
	return (vec3_normalize((t_vec3){{
				mat.matrix[0] * vec.x + mat.matrix[3]
				* vec.y + mat.matrix[6] * vec.z,
				mat.matrix[1] * vec.x + mat.matrix[4]
				* vec.y + mat.matrix[7] * vec.z,
				mat.matrix[2] * vec.x + mat.matrix[5]
				* vec.y + mat.matrix[8] * vec.z
			}}));
}

t_vec3	disturb_world_normal(t_vec3 world_normal, t_vec3 bump_normal)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_mat3	tbn;

	bump_normal = vec3_add(vec3_multiply(bump_normal, 2.0f),
			(t_vec3){{-1.0f, -1.0f, -1.0f}});
	tangent = vec3_product(world_normal, (t_vec3){{0.0f, 1.0f, 0.0f}});
	tangent = vec3_normalize(tangent);
	bitangent = vec3_normalize(vec3_product(world_normal, tangent));
	tbn.matrix[0] = tangent.x;
	tbn.matrix[1] = tangent.y;
	tbn.matrix[2] = tangent.z;
	tbn.matrix[3] = bitangent.x;
	tbn.matrix[4] = bitangent.y;
	tbn.matrix[5] = bitangent.z;
	tbn.matrix[6] = world_normal.x;
	tbn.matrix[7] = world_normal.y;
	tbn.matrix[8] = world_normal.z;
	return (vec3_mat3_dot_vec3(bump_normal, tbn));
}
