/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:01:05 by lcottet           #+#    #+#             */
/*   Updated: 2024/05/11 23:17:23 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "object.h"
#include "libft.h"
#include "camera.h"
#include "matrix.h"

#include <math.h>

void	project_camera(t_camera *camera)
{
	camera->rad_fov = tanf((camera->fov * M_PI / 180.0f) / 2.0f);
	camera->up = (t_vec3){{0, 1, 0}};
	camera->aspect_ratio = (double)WIDTH / (double)HEIGHT;
	camera->far = Z_FAR;
	camera->near = Z_NEAR;
	camera->view = mat4_init(0.0f);
	camera->projection = mat4_init(0.0f);
	mat4_view(camera);
	mat4_perspective(camera);
}
