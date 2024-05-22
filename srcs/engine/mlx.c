/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:55:47 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/22 18:58:46 by bwisniew         ###   ########.fr       */
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
#include <stdio.h>

void	mlx_hooks(t_mlx *mlx)
{
	mlx_loop_hook(mlx->mlx, loop_hook, mlx->engine);
	mlx_hook(mlx->win, DestroyNotify, NoEventMask, mlx_loop_end, mlx);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, keypress_hook, mlx->engine);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask,
		keyrelease_hook, mlx->engine);
	mlx_mouse_hook(mlx->win, buttonpress_hook, mlx->engine);
	mlx_hook(mlx->win, MotionNotify, PointerMotionMask,
		motion_hook, mlx->engine);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x <= WIDTH && y <= HEIGHT)
	{
		dst = img->addr
			+ (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
	else
		printf("Acces x: %d y: %d out of image", x, y);
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
