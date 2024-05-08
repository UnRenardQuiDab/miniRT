/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:20:10 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/08 16:01:35 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "file.h"
#include "ft_error.h"

uint8_t	init_light(t_engine *engine, char **args)
{
	t_object	obj;

	obj.type = &engine->types[LIGHT];
	if (ft_atov3(&obj.position, args[1], rangef(FLT_MIN, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (str_to_decimal(&obj.specific.light.brightness, args[2], FLOAT,
			rangef(0.0f, 1.0f)) == FAILURE)
		return (FAILURE);
	if (ft_atoc(&obj.color, args[3]) == FAILURE)
		return (FAILURE);
	if (vector_add(&engine->lights, &obj) != 0)
		return (err(obj.type->name));
	return (SUCCESS);
}
