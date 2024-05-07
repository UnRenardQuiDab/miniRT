/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:20 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/07 16:25:48 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "ft_error.h"
#include "file.h"

uint8_t	init_plane(t_engine *engine, char **args)
{
	t_object	obj;

	obj.type = &engine->types[PLANE];
	if (ft_atov3(&obj.position, args[1], rangef(FLT_MIN, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atov3(&obj.rotation, args[2], rangef(0, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atoc(&obj.color, args[3]) == FAILURE)
		return (FAILURE);
	if (vector_add(&engine->objects, &obj) == -1)
		return (err(obj.type->name));
	return (SUCCESS);
}
