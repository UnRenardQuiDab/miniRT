/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:53:16 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/30 17:48:41 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# define WIDTH 1920 //3840
# define HEIGHT 1080 //2160
# define NAME "miniRT (lcottet & bwisniew)"

# define Z_NEAR 0.1f
# define Z_FAR 	100.0f

# define FRAME_TIME_COUNT 30
# define FRAME_TIME_GOAL_MIN 10
# define FRAME_TIME_GOAL_MAX 80

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct s_engine	t_engine;

typedef enum e_light_lod
{
	ALL,
	NO_SHADOW,
	AMBIENT_ONLY
}	t_light_lod;

typedef struct s_thread
{
	t_engine		*engine;
	float			starty;
	float			endy;
	pthread_t		thread_id;
}	t_thread;

typedef struct s_framedetails
{
	uint8_t			pixel_size;
	t_light_lod		lights;
	uint16_t		bounces;
	uint16_t		finished;
	int				thread_count;
	t_thread		*threads;
	bool			running;
	pthread_mutex_t	finished_mutex;
	pthread_mutex_t	running_mutex;
	pthread_mutex_t	render_mutex;
	bool			should_render;
	pthread_mutex_t	ready_mutex;
	uint16_t		ready;
	uint32_t		frame_time[FRAME_TIME_COUNT];
	uint8_t			frame_time_len;
}	t_framedetails;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_engine	*engine;
}	t_mlx;

void	render(t_engine *engine);
void	*thread_render(t_thread *thread);
void	request_frame(t_engine *engine);
int8_t	create_threads(t_engine *engine);
void	join_threads(t_framedetails *details);
void	calculate_inside_objects(t_engine *engine);
void	wait_frame(t_engine *engine, uint16_t goal);
void	wait_ready(t_engine *engine, uint16_t goal);
bool	wait_start(t_thread *thread);
void	end_frame(t_thread *thread);
void	prepare_hd(t_engine *engine);
void	adjust_frame_details(t_framedetails *frame);
void	add_frame_time(uint32_t	time, t_framedetails *frame);

#endif