/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/06/03 16:45:58 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "mlx.h"
#include "camera.h"
#include <stddef.h>
#include <math.h>

#include <stdio.h>

t_vec3	get_pixel_color(t_engine *engine, t_ray ray, uint32_t reflections)
{
	t_hit_payload	payload;
	t_vec3			color;
	t_ray			refracted_ray;

	payload = trace_ray(engine, ray);
	if (payload.hit_distance == -1)
		return ((t_vec3){{0, 0.5, 1}});
	color = compute_lights_colors(engine, &payload, ray);
	if (payload.object->material.opacity != 1.0f && reflections > 0)
	{
		refracted_ray = get_refracted_ray(ray, payload);
		color = vec3_add(vec3_multiply(
					get_pixel_color(engine, refracted_ray, --reflections),
					1.0f - payload.object->material.opacity),
				vec3_multiply(color, payload.object->material.opacity));
	}
	if (payload.object->material.reflection > 0.0f && reflections > 0)
	{
		ray = get_reflected_ray(ray, payload);
		color = vec3_add(color,
				vec3_multiply(get_pixel_color(engine, ray, --reflections),
					payload.object->material.reflection));
	}
	return (color);
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

	if (!wait_start(thread))
		return ;
	pthread_mutex_unlock(&thread->engine->frame_details.running_mutex);
	pos.y = thread->starty;
	while (pos.y < thread->endy)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{
			put_pixel_ratio(thread, pos,
				vec3_to_color(get_pixel_color(thread->engine,
						init_ray(thread->engine, (t_vec2){{pos.x
							+ thread->engine->frame_details.pixel_size * 0.5f,
							pos.y
							+ thread->engine->frame_details.pixel_size
							* 0.5f}}),
						thread->engine->frame_details.bounces)));
			pos.x += thread->engine->frame_details.pixel_size;
		}
		pos.y += thread->engine->frame_details.pixel_size;
	}
	end_frame(thread);
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
