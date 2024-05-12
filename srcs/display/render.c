/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/12 08:07:12 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "engine.h"
#include "mlx.h"
#include "camera.h"
#include <stddef.h>
#include <math.h>

#include <stdio.h>

t_color	get_pixel_color(t_engine *engine, t_vec2 pos)
{
	t_vec3			color;
	t_ray			ray;
	t_hit_payload	payload;
	float			multiplier;
	size_t			i;

	ray = init_ray(engine, pos);
	color = (t_vec3){{0, 0, 0}};
	multiplier = 1.0f;
	i = 0;
	while (i < BOUNCES)
	{
		payload = trace_ray(engine, ray);
		if (payload.hit_distance == -1)
			break ;
		color = vec3_add(color,
				vec3_multiply(compute_light_colors(engine, &payload),
					multiplier));
		ray.direction = vec3_reflect(ray.direction, payload.world_normal);
		ray.origin = vec3_add(payload.world_position,
				vec3_multiply(payload.world_normal, 0.0001f));
		multiplier *= 0.7f;
		i++;
	}
	return (vec3_to_color(color));
}

void	render(t_engine *engine)
{
	t_vec2	pos;

	pos.y = 0;
	project_camera(&engine->camera);
	while (pos.y < HEIGHT)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			put_pixel(&engine->mlx.img, pos.x, pos.y,
				get_pixel_color(engine, pos).color);
			pos.x++;
		}
		pos.y++;
	}
	mlx_put_image_to_window(engine->mlx.mlx, engine->mlx.win,
		engine->mlx.img.img, 0, 0);
}
