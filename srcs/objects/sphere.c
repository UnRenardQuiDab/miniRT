/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:20:44 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/07 16:26:14 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "ft_error.h"
#include "file.h"

uint8_t	init_sphere(t_engine *engine, char **args)
{
	t_object	obj;

	obj.type = &engine->types[SPHERE];
	if (ft_atov3(&obj.position, args[1], rangef(FLT_MIN, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (str_to_decimal(&obj.specific.sphere.diameter, args[2],
			FLOAT, rangef(0, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atoc(&obj.color, args[3]) == FAILURE)
		return (FAILURE);
	if (vector_add(&engine->objects, &obj) != 0)
		return (err(obj.type->name));
	return (SUCCESS);
}
