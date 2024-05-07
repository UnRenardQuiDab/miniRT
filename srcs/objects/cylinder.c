/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:01 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/07 16:41:35 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"
#include "file.h"
#include "engine.h"

uint8_t	init_cylinder(t_engine *engine, char **args)
{
	t_object	obj;

	obj.type = &engine->types[CYLINDER];
	if (ft_atov3(&obj.position, args[1], rangef(FLT_MIN, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atov3(&obj.rotation, args[2], rangef(-1.0f, 1.0f)) == FAILURE)
		return (FAILURE);
	if (str_to_decimal(&obj.specific.cylinder.diameter, args[3],
			FLOAT, rangef(0, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (str_to_decimal(&obj.specific.cylinder.height, args[4],
			FLOAT, rangef(0, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atoc(&obj.color, args[5]) == FAILURE)
		return (FAILURE);
	if (vector_add(&engine->objects, &obj) != 0)
		return (err(obj.type->name));
	return (SUCCESS);
}
