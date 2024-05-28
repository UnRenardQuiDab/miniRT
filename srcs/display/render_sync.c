/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sync.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:38:06 by lcottet           #+#    #+#             */
/*   Updated: 2024/05/28 18:08:13 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

bool	wait_start(t_thread *thread)
{
	pthread_mutex_lock(&thread->engine->frame_details.running_mutex);
	if (!thread->engine->frame_details.running)
	{
		pthread_mutex_unlock(&thread->engine->frame_details.running_mutex);
		return (false);
	}
	pthread_mutex_unlock(&thread->engine->frame_details.running_mutex);
	pthread_mutex_lock(&thread->engine->frame_details.render_mutex);
	pthread_mutex_unlock(&thread->engine->frame_details.render_mutex);
	return (true);
}

void	end_frame(t_thread *thread)
{
	pthread_mutex_lock(&thread->engine->frame_details.finished_mutex);
	thread->engine->frame_details.finished++;
	pthread_mutex_unlock(&thread->engine->frame_details.finished_mutex);
	wait_frame(thread->engine, 0);
	pthread_mutex_lock(&thread->engine->frame_details.ready_mutex);
	thread->engine->frame_details.ready++;
	pthread_mutex_unlock(&thread->engine->frame_details.ready_mutex);
}
