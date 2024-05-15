/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:55:47 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/15 14:47:31 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "mlx.h"
#include <unistd.h>

int	loop_hook(t_engine *engine)
{
	request_frame(engine);
	mlx_put_image_to_window(engine->mlx.mlx, engine->mlx.win,
		engine->mlx.img.img, 0, 0);
	return (0);
}
