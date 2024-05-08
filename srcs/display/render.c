/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/08 22:53:20 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "engine.h"
#include "mlx.h"
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
	size_t			j;
	float			biggest_light;

	ray.origin = engine->camera.position;
	ray.direction = (t_vec3){{
		pos.x,
		pos.y,
		-1.0f
	}};
	ray.direction = vec3_normalize(ray.direction);
	color = (t_vec3){{0, 0, 0}};
	multiplier = 1.0f;
	i = 0;
	while (i < BOUNCES)
	{
		payload = trace_ray(engine, ray);
		if (payload.hit_distance == -1)
			break;
		biggest_light = 0;
		j = 0;
		while (j < engine->lights.len)
		{
			t_vec3 light_dir = vec3_substract(payload.world_position, ((t_object *)engine->lights.tab)[j].position);
			light_dir = vec3_normalize(light_dir);
			float light = vec3_dot(payload.world_normal, vec3_multiply(light_dir, -1.0)) * ((t_object *)engine->lights.tab)[j].specific.light.brightness;
			if (light > biggest_light)
				biggest_light = light;
			j++;
		}
		t_vec3	obj_color;
		obj_color = vec3_multiply(color_to_vec3(payload.object->color), biggest_light);
		color = vec3_add(color, vec3_multiply(obj_color, multiplier));
		ray.direction = vec3_reflect(ray.direction, payload.world_normal);
		ray.origin = vec3_add(payload.world_position, vec3_multiply(payload.world_normal, 0.0001f));
		multiplier *= 0.7f;
		i++;
	}
	return (vec3_to_color(color));
}

void	render(t_engine *engine)
{
	t_vec2	pos;
	float	aspect_ratio;

	aspect_ratio = WIDTH / (float) HEIGHT;
	pos.y = 0;
	float	theta = engine->camera.fov * M_PI / 180;
	float	h = tan(theta / 2);
	
	while (pos.y < HEIGHT)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{	
			put_pixel(&engine->mlx.img, pos.x, pos.y,
				get_pixel_color(engine, (t_vec2){{
					((pos.x / WIDTH) * 2.0f - 1.0f) * aspect_ratio * h,
					(1.0f - 2.0f * pos.y / HEIGHT) * h}}
					).color);
			pos.x++;
		}
		pos.y++;
	}
	mlx_put_image_to_window(engine->mlx.mlx, engine->mlx.win,
		engine->mlx.img.img, 0, 0);
}