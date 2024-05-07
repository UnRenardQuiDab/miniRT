/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:55:47 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/07 20:05:26 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "ft_error.h"
#include <X11/X.h>
#include <stdlib.h>

void	mlx_hooks(t_mlx *data)
{
	mlx_loop_hook(data->mlx, fill_full_window, data);
	mlx_hook(data->win, ButtonPress, ButtonPressMask, button_hook, data);
	mlx_hook(data->win, ButtonRelease, ButtonReleaseMask, release_hook, data);
	mlx_hook(data->win, DestroyNotify, NoEventMask, mlx_loop_end, data->mlx);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, keyrelease_hook, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, keypress_hook, data);
	mlx_hook(data->win, MotionNotify, PointerMotionMask, mouse_hook, data);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	mlx_init_mlx(t_mlx *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (FAILURE);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, NAME);
	if (!data->win)
		return (-1);
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.img)
		return (-1);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&(data->img.bits_per_pixel), &(data->img.line_length),
			&(data->img.endian));
	if (!data->img.addr)
		return (-1);
	return (0);
}

int	mlx_destroy_mlx(t_mlx *data)
{
	if (data->img.img)
		mlx_destroy_image(data->mlx, data->img.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	return (0);
}
