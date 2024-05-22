/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/22 19:30:44 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "libft.h"
#include <sys/sysinfo.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void	join_threads(t_framedetails *details)
{
	int	i;

	pthread_mutex_lock(&details->running_mutex);
	details->running = false;
	pthread_mutex_unlock(&details->running_mutex);
	pthread_mutex_unlock(&details->render_mutex);
	pthread_mutex_lock(&details->finished_mutex);
	details->finished = 0;
	pthread_mutex_unlock(&details->finished_mutex);
	i = 0;
	while (i < details->thread_count)
	{
		pthread_join(details->threads[i].thread_id, NULL);
		i++;
	}
	free(details->threads);
	pthread_mutex_destroy(&details->finished_mutex);
	pthread_mutex_destroy(&details->running_mutex);
	pthread_mutex_destroy(&details->render_mutex);
}

int8_t	init_frame_detais(t_engine *engine)
{
	engine->frame_details.pixel_size = 1;
	engine->frame_details.lights = ALL;
	engine->frame_details.bounces = BOUNCES;
	engine->frame_details.finished = 0;
	engine->frame_details.running = true;
	engine->frame_details.should_render = true;
	if (pthread_mutex_init(&engine->frame_details.finished_mutex, NULL) != 0)
		return (FAILURE);
	if (pthread_mutex_init(&engine->frame_details.running_mutex, NULL) != 0)
		return (FAILURE);
	if (pthread_mutex_init(&engine->frame_details.render_mutex, NULL) != 0)
		return (FAILURE);
	pthread_mutex_lock(&engine->frame_details.render_mutex);
	return (SUCCESS);
}

int8_t	create_thread(t_engine *engine, float starty, float endy,
	t_thread *thread)
{
	thread->engine = engine;
	thread->starty = starty;
	thread->endy = endy;
	if (pthread_create(&thread->thread_id, NULL,
			(void *(*)(void *))thread_render, thread) != 0)
		return (FAILURE);
	printf("Created thread #%lu from line %f to %f\n",
		thread->thread_id, starty, endy);
	return (SUCCESS);
}

int8_t	create_threads(t_engine *engine)
{
	int	available_cores;
	int	i;

	available_cores = get_nprocs();
	engine->frame_details.threads = malloc(sizeof(t_thread) * available_cores);
	if (!engine->frame_details.threads)
		return (FAILURE);
	if (init_frame_detais(engine) == FAILURE)
		return (FAILURE);
	if (available_cores < 1)
		return (FAILURE);
	i = 0;
	while (i < available_cores)
	{
		if (create_thread(engine, i * (HEIGHT / available_cores),
				(i + 1) * (HEIGHT / available_cores),
				&(engine->frame_details.threads[i])) == FAILURE)
			return (FAILURE);
		i++;
	}
	engine->frame_details.thread_count = available_cores;
	return (SUCCESS);
}

void	request_frame(t_engine *engine)
{
	struct timeval	start;
	struct timeval	end;

	gettimeofday(&start, NULL);
	engine->frame_details.ready = 0;
	project_camera(&engine->camera);
	calculate_inside_objects(engine);
	pthread_mutex_lock(&engine->frame_details.finished_mutex);
	engine->frame_details.finished = 0;
	pthread_mutex_unlock(&engine->frame_details.finished_mutex);
	pthread_mutex_unlock(&engine->frame_details.render_mutex);
	wait_frame(engine, engine->frame_details.thread_count);
	pthread_mutex_lock(&engine->frame_details.render_mutex);
	pthread_mutex_lock(&engine->frame_details.finished_mutex);
	engine->frame_details.finished = 0;
	pthread_mutex_unlock(&engine->frame_details.finished_mutex);
	gettimeofday(&end, NULL);
	printf("Frame rendered in %ldms\n",
		((end.tv_sec - start.tv_sec) * 1000
			+ (end.tv_usec - start.tv_usec) / 1000));
	wait_ready(engine, engine->frame_details.thread_count);
}
