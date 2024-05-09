/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:20 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/09 19:13:24 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "engine.h"
#include "ft_error.h"
#include "file.h"

float	get_hit_distance_plane(t_object *obj, t_ray ray)
{
	t_vec3		ray_origin;
	float		t;
	float		discriment;

	ray_origin = vec3_substract(obj->position, ray.origin);
	discriment = vec3_dot(ray.direction, obj->rotation);
	if (discriment == 0)
		return (FLT_MAX);
	t = vec3_dot(obj->rotation, ray_origin) / discriment;
	return (t);
}

t_vec3	get_normal_plane(t_object *obj, t_ray ray, t_hit_payload payload)
{
	(void)payload;
	if (vec3_dot(ray.direction, obj->rotation) > 0)
		return (vec3_multiply(obj->rotation, -1.0f));
	return (obj->rotation);
}

uint8_t	init_plane(t_engine *engine, char **args)
{
	t_object	obj;

	obj.type = &engine->types[PLANE];
	obj.get_hit_distance = get_hit_distance_plane;
	obj.get_normal = get_normal_plane;
	if (ft_atov3(&obj.position, args[1], rangef(FLT_MIN, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atov3(&obj.rotation, args[2], rangef(-1.0f, 1.0f)) == FAILURE)
		return (FAILURE);
	obj.rotation = vec3_normalize(obj.rotation);
	if (ft_atoc(&obj.color, args[3]) == FAILURE)
		return (FAILURE);
	if (vector_add(&engine->objects, &obj) == -1)
		return (err(obj.type->name));
	return (SUCCESS);
}
