/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 19:20:38 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/23 22:46:56 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "matrix.h"

t_vec3	disturb_world_normal(t_vec3 world_normal, t_vec3 bump_normal)
{
	t_vec3	new;

	new.x = (1.0f - bump_normal.x)
	
	// t_vec3	tangent;
	// t_vec3	bitangent;
	// t_mat3	tbn;
	
	// tangent = vec3_product(world_normal, (t_vec3){{0, 1, 0}});
	// tangent = vec3_normalize(tangent);
	// bitangent = vec3_normalize(vec3_product(world_normal, tangent));
	// tbn.matrix[0] = tangent.x;
	// tbn.matrix[1] = tangent.y;
	// tbn.matrix[2] = tangent.z;
	// tbn.matrix[3] = bitangent.x;
	// tbn.matrix[4] = bitangent.y;
	// tbn.matrix[5] = bitangent.z;
	// tbn.matrix[6] = world_normal.x;
	// tbn.matrix[7] = world_normal.y;
	// tbn.matrix[8] = world_normal.z;
	// (void) bump_normal;
	// return (vec3_normalize((t_vec3){{
	// 	tbn.matrix[0] + tbn.matrix[3] + tbn.matrix[6],
	// 	tbn.matrix[1] + tbn.matrix[4] + tbn.matrix[7],
	// 	tbn.matrix[2] + tbn.matrix[5] + tbn.matrix[8]
	// }}));
}
