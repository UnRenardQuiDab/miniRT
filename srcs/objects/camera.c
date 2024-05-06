/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:17:07 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/06 18:56:35 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "engine.h"

uint8_t init_camera(t_engine *engine, char **args)
{
	engine->camera.fov = ft_atoi(args[1]);
	if (ft_atov3(&engine->camera.orientation, args[2]) == FAILURE)
		return (FAILURE);
	if (ft_atov3(&engine->camera.position, args[3]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
