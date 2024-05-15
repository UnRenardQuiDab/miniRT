/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:51:41 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/15 18:45:31 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <stdint.h>
# include <stdbool.h>

# include "object.h"
# include "vector.h"
# include "color.h"
# include "display.h"
# include "vec.h"

# define MOUVEMENT_SPEED 0.1f
# define SENSITIVITY 0.001f

# define BOUNCES 1

# define FAILURE 1
# define SUCCESS 0

# define FLT_MAX __FLT_MAX__
# define FLT_MIN -FLT_MAX

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

typedef struct s_hit_payload
{
	float			hit_distance;
	t_vec3			world_position;
	t_vec3			world_normal;
	t_object		*object;
}		t_hit_payload;

typedef	struct s_input
{
	bool	left;
	bool	right;
	bool	forward;
	bool	backward;
	bool	up;
	bool	down;
	bool	active;
	int		mouse_x;
	int		mouse_y;
}	t_input;

typedef struct s_engine
{
	t_obj_type		types[TYPE_COUNT];
	t_vector		objects;
	t_vector		lights;
	t_camera		camera;
	t_ambient		ambient;
	t_mlx			mlx;
	t_framedetails	frame_details;
	t_input			input;
}				t_engine;

void			mlx_hooks(t_mlx *mlx);
void			put_pixel(t_img *img, int x, int y, int color);
void			mlx_destroy_mlx(t_mlx *mlx);
int				mlx_init_mlx(t_mlx *mlx);

t_hit_payload	trace_ray(t_engine *engine, t_ray ray);
t_vec3			compute_light_colors(t_engine *engine, t_hit_payload *payload);
t_ray			init_ray(t_engine *engine, t_vec2 pos);

int				loop_hook(t_engine *engine);
int				keypress_hook( int key, t_engine *engine);
int				keyrelease_hook(int key, t_engine *engine);
int				buttonpress_hook(int button, int x, int y, t_engine *engine);
int				motion_hook(int x, int y, t_engine *engine);

int				exit_rt(t_engine *engine, int status);
void			camera_move(t_engine *engine);
void			rotate_camera(t_engine *engine, int deltax, int deltay);

#endif