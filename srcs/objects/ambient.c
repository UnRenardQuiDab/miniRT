/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:19:27 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/13 20:54:23 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "engine.h"
#include "ft_error.h"

uint8_t	init_ambient(t_engine *engine, char **args)
{
	if (engine->ambient.lighting >= 0)
		return (custom_error(OBJECT_AMBIENT, ERR_REDEFINITION));
	if (str_to_decimal(&engine->ambient.lighting, args[1],
			FLOAT, rangef(0.0f, 1.0f)) == FAILURE)
		return (FAILURE);
	if (ft_atoc(&engine->ambient.color, args[2]) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
