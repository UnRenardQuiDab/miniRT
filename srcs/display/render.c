/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/15 23:50:56 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	while (i < engine->frame_details.bounces)
	{
		payload = trace_ray(engine, ray);
		if (payload.hit_distance == -1)
			break ;
		color = vec3_add(color,
				vec3_multiply(compute_light_colors(engine, &payload, ray),
					multiplier));
		ray.direction = vec3_reflect(ray.direction, payload.world_normal);
		ray.origin = vec3_add(payload.world_position,
				vec3_multiply(payload.world_normal, 0.0001f));
		multiplier *= 0.1f;
		i++;
	}
	return (vec3_to_color(color));
}

void	put_pixel_ratio(t_thread *thread, t_vec2 pos, t_color color)
{
	size_t	i;
	size_t	j;
	uint8_t	ratio;

	ratio = thread->engine->frame_details.pixel_size;
	i = 0;
	while (i < ratio)
	{
		j = 0;
		while (j < ratio)
		{
			if (pos.x + j < WIDTH && pos.y + i < thread->endy)
				put_pixel(&thread->engine->mlx.img,
					pos.x + j, pos.y + i, color.color);
			j++;
		}
		i++;
	}
}

void	thread_render_frame(t_thread *thread)
{
	t_vec2	pos;

	pthread_mutex_lock(&thread->engine->frame_details.render_mutex);
	pthread_mutex_unlock(&thread->engine->frame_details.render_mutex);
	pos.y = thread->starty;
	while (pos.y < thread->endy)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			put_pixel_ratio(thread, pos,
				get_pixel_color(thread->engine, (t_vec2){{pos.x
					+ thread->engine->frame_details.pixel_size * 0.5f, pos.y
					+ thread->engine->frame_details.pixel_size * 0.5f}}));
			pos.x += thread->engine->frame_details.pixel_size;
		}
		pos.y += thread->engine->frame_details.pixel_size;
	}
	pthread_mutex_lock(&thread->engine->frame_details.finished_mutex);
	thread->engine->frame_details.finished++;
	pthread_mutex_unlock(&thread->engine->frame_details.finished_mutex);
	wait_frame(thread->engine, 0);
	pthread_mutex_lock(&thread->engine->frame_details.ready_mutex);
	thread->engine->frame_details.ready++;
	pthread_mutex_unlock(&thread->engine->frame_details.ready_mutex);
}

void	*thread_render(t_thread *ptrthread)
{
	t_thread	thread;

	thread = *ptrthread;
	pthread_mutex_lock(&thread.engine->frame_details.running_mutex);
	while (thread.engine->frame_details.running)
	{
		pthread_mutex_unlock(&thread.engine->frame_details.running_mutex);
		thread_render_frame(&thread);
		pthread_mutex_lock(&thread.engine->frame_details.running_mutex);
	}
	pthread_mutex_unlock(&thread.engine->frame_details.running_mutex);
	return (NULL);
}

void	calculate_inside_objects(t_engine *engine)
{
	size_t		i;
	t_object	*obj;

	i = 0;
	while (i < engine->objects.len)
	{
		obj = (t_object *)engine->objects.tab + i;
		if (obj->is_inside_func)
			obj->is_inside = obj->is_inside_func(obj, engine->camera.position);
		else
			obj->is_inside = false;
		i++;
	}
}
