/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:16:26 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/06 18:41:36 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "object.h"

#include "libft.h"

void init_type(t_engine *engine)
{
	ft_memcpy(engine->types, (t_obj_type []){
		{0, OBJECT_CAMERA, 4, init_camera},
		{1, OBJECT_AMBIENT, 3, init_ambient},
		{2, OBJECT_LIGHT, 4, init_light},
		{3, OBJECT_CYLINDER, 6, init_cylinder},
		{4, OBJECT_PLANE, 4, init_plane},
		{5, OBJECT_SPHERE, 4, init_sphere}
	}, sizeof(t_obj_type) * TYPE_COUNT);
}