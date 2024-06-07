/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:16:26 by bwisniew          #+#    #+#             */
/*   Updated: 2024/06/07 15:42:37 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "object.h"
#include "libft.h"

static void	init_type(t_engine *engine)
{
	ft_memcpy(engine->types, (t_obj_type []){
	{CAMERA, OBJECT_CAMERA, 4, init_camera},
	{AMBIENT, OBJECT_AMBIENT, 3, init_ambient},
	{LIGHT, OBJECT_LIGHT, 4, init_light},
	{SPHERE, OBJECT_SPHERE, 4, init_sphere},
	{PLANE, OBJECT_PLANE, 4, init_plane},
	{CYLINDER, OBJECT_CYLINDER, 6, init_cylinder},
	{MATERIAL, OBJECT_MATERIAL, 8, init_material},
	{CONE, OBJECT_CONE, 6, init_cone}
	}, sizeof(t_obj_type) * TYPE_COUNT);
}

void	init_engine(t_engine *engine)
{
	init_type(engine);
	engine->camera.fov = -1;
	engine->ambient.lighting = -1.0f;
	vector_init(&engine->objects, sizeof(t_object));
	vector_init(&engine->lights, sizeof(t_object));
	vector_init(&engine->materials, sizeof(t_material));
}
