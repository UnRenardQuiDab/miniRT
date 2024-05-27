/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:55:47 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/27 14:39:52 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "mlx.h"
#include "libft.h"
#include <unistd.h>
#define XK_MISCELLANY
#define XK_LATIN1
#include <X11/keysymdef.h>
#include <X11/X.h>
#include <stdio.h>

int	motion_hook(int x, int y, t_engine *engine)
{
	int	deltax;
	int	deltay;

	deltax = x - engine->input.mouse_x;
	deltay = engine->input.mouse_y - y;
	engine->input.mouse_x = x;
	engine->input.mouse_y = y;
	if (!engine->input.active || (x == WIDTH / 2 && y == HEIGHT / 2))
		return (SUCCESS);
	rotate_camera(engine, deltax, deltay);
	mlx_mouse_move(engine->mlx.mlx, engine->mlx.win, WIDTH / 2, HEIGHT / 2);
	return (SUCCESS);
}

int	buttonpress_hook(int button, int x, int y, t_engine *engine)
{
	(void)x;
	(void)y;
	if (button == 1 && !engine->input.active)
	{
		mlx_mouse_hide(engine->mlx.mlx, engine->mlx.win);
		engine->frame_details.lights = NO_SHADOW;
		engine->frame_details.pixel_size = 6;
		engine->input.active = true;
		engine->frame_details.bounces = 1;
	}
	return (SUCCESS);
}

int	keypress_hook(int key, t_engine *engine)
{
	if (key == XK_Escape || key == XK_q)
		mlx_loop_end(engine->mlx.mlx);
	if (!engine->input.active)
		return (SUCCESS);
	if (key == XK_a || key == XK_A)
		engine->input.left = true;
	else if (key == XK_d || key == XK_D)
		engine->input.right = true;
	else if (key == XK_w || key == XK_W)
		engine->input.forward = true;
	else if (key == XK_s || key == XK_S)
		engine->input.backward = true;
	else if (key == XK_space)
		engine->input.up = true;
	else if (key == XK_Shift_L)
		engine->input.down = true;
	else if (key == XK_Return)
		prepare_hd(engine);
	return (SUCCESS);
}

int	keyrelease_hook(int key, t_engine *engine)
{
	if (key == XK_a || key == XK_A)
		engine->input.left = false;
	else if (key == XK_d || key == XK_D)
		engine->input.right = false;
	else if (key == XK_w || key == XK_W)
		engine->input.forward = false;
	else if (key == XK_s || key == XK_S)
		engine->input.backward = false;
	else if (key == XK_space)
		engine->input.up = false;
	else if (key == XK_Shift_L)
		engine->input.down = false;
	return (SUCCESS);
}

int	loop_hook(t_engine *engine)
{
	if (engine->input.active)
		camera_move(engine);
	if (engine->frame_details.should_render)
	{
		engine->frame_details.should_render = false;
		request_frame(engine);
		mlx_put_image_to_window(engine->mlx.mlx, engine->mlx.win,
			engine->mlx.img.img, 0, 0);
	}
	return (0);
}
