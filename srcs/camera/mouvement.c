/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:52:02 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/15 19:13:42 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define XK_MISCELLANY
#define XK_LATIN1
#include <X11/keysymdef.h>
#include <X11/X.h>
#include "engine.h"


t_vec3	camera_move_x(t_engine *engine)
{
	if (engine->input.right)
		return (vec3_add(engine->camera.position, vec3_multiply((t_vec3){{
				engine->camera.rotation.z,
				engine->camera.rotation.y,
				engine->camera.rotation.x
			}}, MOUVEMENT_SPEED)));
	if (engine->input.left)
		return (vec3_add(engine->camera.position, vec3_multiply((t_vec3){{
				engine->camera.rotation.z,
				engine->camera.rotation.y,
				engine->camera.rotation.x
			}}, -MOUVEMENT_SPEED)));
	return (engine->camera.position);
}

t_vec3	camera_move_z(t_engine *engine)
{
	if (engine->input.forward)
		return (vec3_add(engine->camera.position, vec3_multiply(engine->camera.rotation, MOUVEMENT_SPEED)));
	if (engine->input.backward)
		return (vec3_add(engine->camera.position, vec3_multiply(engine->camera.rotation, -MOUVEMENT_SPEED)));
	return (engine->camera.position);
}

t_vec3	camera_move_y(t_engine *engine)
{
	if (engine->input.up)
		return (vec3_add(engine->camera.position, vec3_multiply(engine->camera.up, MOUVEMENT_SPEED)));
	if (engine->input.down)
		return (vec3_add(engine->camera.position, vec3_multiply(engine->camera.up, -MOUVEMENT_SPEED)));
	return (engine->camera.position);
}

void	camera_move(t_engine *engine)
{
	if (engine->input.left || engine->input.right)
		engine->camera.position = camera_move_x(engine);
	if (engine->input.forward || engine->input.backward)
		engine->camera.position = camera_move_z(engine);
	if (engine->input.up || engine->input.down)
		engine->camera.position = camera_move_y(engine);
	if (engine->input.left || engine->input.right || engine->input.forward || engine->input.backward || engine->input.up || engine->input.down)
	{
		engine->frame_details.lights = NO_SHADOW;
		engine->frame_details.pixel_size = 4;
		engine->frame_details.should_render = true;
	}
}
