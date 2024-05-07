/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:55:47 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/07 17:30:20 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "engine.h"
#include "display.h"
#include "ft_error.h"
#define XK_MISCELLANY
#define XK_LATIN1
#include <X11/keysymdef.h>
#include <X11/X.h>
#include <stdlib.h>

static int	mlx_stop_loop( int key, t_mlx *mlx)
{
	if (key == XK_Escape || key == XK_q)
		mlx_loop_end(mlx->mlx);
	return (SUCCESS);
}

void	mlx_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, DestroyNotify, NoEventMask, mlx_loop_end, mlx->mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, mlx_stop_loop, mlx);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	mlx_init_mlx(t_mlx *mlx)
{
	mlx->img.img = NULL;
	mlx->win = NULL;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (FAILURE);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, NAME);
	if (!mlx->win)
		return (FAILURE);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img.img)
		return (FAILURE);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img,
			&(mlx->img.bits_per_pixel), &(mlx->img.line_length),
			&(mlx->img.endian));
	if (!mlx->img.addr)
		return (FAILURE);
	mlx_hooks(mlx);
	mlx_loop(mlx->mlx);
	return (SUCCESS);
}

void	mlx_destroy_mlx(t_mlx *mlx)
{
	if (mlx->img.img)
		mlx_destroy_image(mlx->mlx, mlx->img.img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
}
