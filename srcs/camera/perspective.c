/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perspective.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:09:15 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/11 23:54:50 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "object.h"

void	mat4_perspective(t_camera *camera)
{
	t_mat4	projection;

	projection = mat4_init(0.0f);
	projection.matrix[0] = -1.0f / (camera->rad_fov * camera->aspect_ratio);
	projection.matrix[5] = -1.0f / camera->rad_fov;
	projection.matrix[10] = (camera->near + camera->far)
		/ (camera->near - camera->far);
	projection.matrix[11] = -(2.0f * camera->near * camera->far)
		/ (camera->far - camera->near);
	projection.matrix[14] = -1.0f;
	camera->projection = projection;
}
