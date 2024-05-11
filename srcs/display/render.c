/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/11 07:05:20 by bwisniew         ###   ########.fr       */
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
	size_t			j;

	pos.x = (1.0f - pos.x / WIDTH) * 2.0f -1.0f;
	pos.y = (1.0f - pos.y / HEIGHT) * 2.0f -1.0f;
	t_vec4 target = mat4vec4_product((t_vec4){{
		pos.x, pos.y, 1, 1
	}}, mat4_inverse(engine->camera.projection));
	t_vec3 ray_dir_norm = vec3_normalize(vec3_multiply((t_vec3){{target.x, target.y, target.z}}, 1 / target.w));
	t_vec4 ray_dir_tmp = mat4vec4_product((t_vec4){{
		ray_dir_norm.x,
		ray_dir_norm.y,
		ray_dir_norm.z,
		0.0f
	}},mat4_inverse(engine->camera.view));
	ray.direction = (t_vec3)
	{{
		ray_dir_tmp.x,
		ray_dir_tmp.y,
		ray_dir_tmp.z
	}};
	ray.origin = engine->camera.position;
	/*ray.direction = (t_vec3){{
		pos.x,
		pos.y,
		-1.0f
	}};*/
	ray.direction = vec3_normalize(ray.direction);
	color = (t_vec3){{0, 0, 0}};
	multiplier = 1.0f;
	i = 0;
	while (i < BOUNCES)
	{
		payload = trace_ray(engine, ray);
		if (payload.hit_distance == -1)
			break;
		t_vec3	light_color = vec3_multiply(color_to_vec3(engine->ambient.color), engine->ambient.lighting);
		j = 0;
		while (j < engine->lights.len)
		{
			t_vec3 rel_pos = vec3_substract(payload.world_position, ((t_object *)engine->lights.tab)[j].position);
			t_vec3 light_dir = vec3_normalize(rel_pos);
			t_hit_payload light_payload = trace_ray(engine, (t_ray){
				vec3_add(payload.world_position, vec3_multiply(payload.world_normal, 0.0001f)),
				vec3_multiply(light_dir, -1.0f)
			});
			if (light_payload.hit_distance != -1 && vec3_dist_sqr(payload.world_position, ((t_object *)engine->lights.tab)[j].position) > light_payload.hit_distance * light_payload.hit_distance)
			{
				//color = color_to_vec3(light_payload.object->color);
				j++;
				continue;
			}
			float light = vec3_dot(payload.world_normal, vec3_multiply(light_dir, -1.0f * ((t_object *)engine->lights.tab)[j].specific.light.brightness) );
			if (light < 0)
				light = 0;
			light_color = vec3_add(light_color, vec3_multiply(color_to_vec3(((t_object *)engine->lights.tab)[j].color), light));
			j++;
		}
		light_color.x *= color_to_vec3(payload.object->color).x;
		light_color.y *= color_to_vec3(payload.object->color).y;
		light_color.z *= color_to_vec3(payload.object->color).z;
		color = vec3_add(color, vec3_multiply(light_color, multiplier));
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
