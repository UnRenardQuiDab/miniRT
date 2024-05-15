/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/15 14:49:23 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include <stdio.h>

void	wait_frame(t_engine *engine, uint16_t goal)
{
	pthread_mutex_lock(&engine->frame_details.finished_mutex);
	pthread_mutex_unlock(&engine->frame_details.running_mutex);
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
