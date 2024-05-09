/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:51:41 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/09 19:41:08 by lcottet          ###   ########.fr       */
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

# define BOUNCES 2

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
	float		hit_distance;
	t_vec3		world_position;
	t_vec3		world_normal;
	t_object	*object;
}		t_hit_payload;

typedef struct s_engine
{
	t_obj_type		types[TYPE_COUNT];
	t_vector		objects;
	t_vector		lights;
	t_camera		camera;
	t_ambient		ambient;
	t_mlx			mlx;
}				t_engine;

void	mlx_hooks(t_mlx *mlx);
void	put_pixel(t_img *img, int x, int y, int color);
void	mlx_destroy_mlx(t_mlx *mlx);
int		mlx_init_mlx(t_mlx *mlx);

t_hit_payload	trace_ray(t_engine *engine, t_ray ray);

#endif