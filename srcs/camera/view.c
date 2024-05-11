/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:57:01 by lcottet           #+#    #+#             */
/*   Updated: 2024/05/11 05:32:20 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"
#include "matrix.h"
#include "vec.h"
#include "camera.h"

void	mat4_view(t_camera *camera)
{
	t_mat4	view;
	t_vec3	look_at;
	t_vec3	new_axe;
	t_vec3	norm;

	look_at = vec3_normalize(vec3_add(camera->position, camera->rotation));
	norm = vec3_normalize(vec3_product(look_at, camera->up));
	new_axe = vec3_normalize(vec3_product(norm, look_at));
	view = mat4_identity();
	view.matrix[0] = norm.x;
	view.matrix[1] = norm.y;
	view.matrix[2] = norm.z;
	view.matrix[4] = new_axe.x;
	view.matrix[5] = new_axe.y;
	view.matrix[6] = new_axe.z;
	view.matrix[8] = -look_at.x;
	view.matrix[9] = -look_at.y;
	view.matrix[10] = -look_at.z;
	view.matrix[12] = -vec3_dot(norm, camera->position);
	view.matrix[13] = -vec3_dot(new_axe, camera->position);
	view.matrix[14] = vec3_dot(look_at, camera->position);
	view.matrix[15] = 1.0;
	camera->view = view;
}
