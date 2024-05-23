/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/22 19:00:02 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "mlx.h"
#include <stdio.h>

void	prepare_hd(t_engine *engine)
{
	printf("Preparing high quality rendering...\n");
	engine->frame_details.pixel_size = 1;
	engine->frame_details.lights = ALL;
	engine->frame_details.should_render = true;
	engine->input.active = false;
	mlx_mouse_show(engine->mlx.mlx, engine->mlx.win);
}

void	wait_frame(t_engine *engine, uint16_t goal)
{
	pthread_mutex_lock(&engine->frame_details.finished_mutex);
	pthread_mutex_lock(&engine->frame_details.running_mutex);
	while (
		((goal == 0 && engine->frame_details.finished != 0)
			|| (goal != 0 && engine->frame_details.finished < goal))
		&& engine->frame_details.running)
	{
		pthread_mutex_unlock(&engine->frame_details.running_mutex);
		pthread_mutex_unlock(&engine->frame_details.finished_mutex);
		usleep(100);
		pthread_mutex_lock(&engine->frame_details.finished_mutex);
		pthread_mutex_lock(&engine->frame_details.running_mutex);
	}
	pthread_mutex_unlock(&engine->frame_details.running_mutex);
	pthread_mutex_unlock(&engine->frame_details.finished_mutex);
}

void	wait_ready(t_engine *engine, uint16_t goal)
{
	pthread_mutex_lock(&engine->frame_details.ready_mutex);
	pthread_mutex_lock(&engine->frame_details.running_mutex);
	while (
		((goal == 0 && engine->frame_details.ready != 0)
			|| (goal != 0 && engine->frame_details.ready < goal))
		&& engine->frame_details.running)
	{
		pthread_mutex_unlock(&engine->frame_details.running_mutex);
		pthread_mutex_unlock(&engine->frame_details.ready_mutex);
		usleep(100);
		pthread_mutex_lock(&engine->frame_details.ready_mutex);
		pthread_mutex_lock(&engine->frame_details.running_mutex);
	}
	pthread_mutex_unlock(&engine->frame_details.running_mutex);
	pthread_mutex_unlock(&engine->frame_details.ready_mutex);
}
