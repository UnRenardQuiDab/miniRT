/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:17:07 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/07 15:40:46 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "engine.h"
#include "ft_error.h"
#include <stddef.h>

uint8_t	init_camera(t_engine *engine, char **args)
{
	if (engine->camera.fov > 0)
		return (custom_error(OBJECT_CAMERA, ERR_REDEFINITION));
	if (ft_atov3(&engine->camera.position, args[1],
			rangef(FLT_MIN, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atov3(&engine->camera.rotation, args[2],
			rangef(-1.0f, 1.1f)) == FAILURE)
		return (FAILURE);
	if (str_to_decimal(&engine->camera.fov, args[3],
			INT, rangei(0, 180)) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
