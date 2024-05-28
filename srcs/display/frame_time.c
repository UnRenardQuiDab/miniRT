/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:51:19 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/28 18:08:13 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include "engine.h"
#include "libft.h"

void	add_frame_time(uint32_t	time, t_framedetails *frame)
{
	printf("Frame rendered in %ums\n", time);
	if (frame->frame_time_len < FRAME_TIME_COUNT - 1)
	{
		ft_memmove(frame->frame_time + 1, frame->frame_time,
			sizeof(uint32_t) * frame->frame_time_len);
		frame->frame_time[0] = time;
		frame->frame_time_len++;
		return ;
	}
	ft_memmove(frame->frame_time + 1, frame->frame_time,
		sizeof(uint32_t) * (FRAME_TIME_COUNT - 1));
	frame->frame_time[0] = time;
}

void	adjust_frame_details(t_framedetails *frame)
{
	uint32_t	i;
	uint32_t	sum;
	uint32_t	avg;

	i = 0;
	sum = 0;
	while (i < frame->frame_time_len)
	{
		sum += frame->frame_time[i];
		i++;
	}
	frame->frame_time_len = i;
	avg = sum / frame->frame_time_len;
	if (avg < FRAME_TIME_GOAL_MIN && frame->pixel_size > 2)
		frame->pixel_size--;
	else if (avg > FRAME_TIME_GOAL_MAX && frame->pixel_size < 254)
		frame->pixel_size++;
}
