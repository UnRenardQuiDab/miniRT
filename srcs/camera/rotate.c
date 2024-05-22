/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:59:36 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/22 19:02:03 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include <stdio.h>

t_vec3	rotate_camera_x(t_engine *engine, int delta)
{
	return (vec3_normalize(mat3vec3_product(engine->camera.rotation,
				mat3_rotate(SENSITIVITY * delta, (t_vec3){{0, 1, 0}}))));
}

t_vec3	rotate_camera_y(t_engine *engine, int delta)
{
	t_vec3	rotation;

	rotation = vec3_normalize(mat3vec3_product(engine->camera.rotation,
				mat3_rotate(SENSITIVITY * delta,
					vec3_normalize(vec3_product(engine->camera.rotation,
							(t_vec3){{0, 1, 0}})))));
	if (rotation.y < 0.95 && rotation.y > -0.95)
		return (rotation);
	return (engine->camera.rotation);
}

void	rotate_camera(t_engine *engine, int deltax, int deltay)
{
	engine->camera.rotation = vec3_normalize(rotate_camera_x(engine, deltax));
	engine->camera.rotation = vec3_normalize(rotate_camera_y(engine, deltay));
	engine->frame_details.should_render = true;
}
