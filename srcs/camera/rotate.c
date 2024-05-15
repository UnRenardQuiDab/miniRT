/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:59:36 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/15 19:14:39 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include <stdio.h>

t_vec3	rotate_camera_x(t_engine *engine, int delta)
{
	(void) delta;
	return ((t_vec3){{
		engine->camera.rotation.x,
		engine->camera.rotation.y,
		engine->camera.rotation.z
	}});
}

t_vec3	rotate_camera_y(t_engine *engine, int delta)
{
	(void) delta;
	return ((t_vec3){{
		engine->camera.rotation.x,
		engine->camera.rotation.y,
		engine->camera.rotation.z
	}});
}

void	rotate_camera(t_engine *engine, int deltax, int deltay)
{
	engine->camera.rotation = rotate_camera_x(engine, deltax);
	engine->camera.rotation = rotate_camera_y(engine, deltay);
	engine->camera.rotation = vec3_normalize(engine->camera.rotation);
	//printf("x = %f, y = %f, z = %f\n", engine->camera.rotation.x, engine->camera.rotation.y, engine->camera.rotation.z);
	engine->frame_details.should_render = true;
}

