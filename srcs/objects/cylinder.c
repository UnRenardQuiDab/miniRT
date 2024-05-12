/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:01 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/12 09:54:23 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_error.h"
#include "file.h"
#include "engine.h"

float	get_hit_distance_disk(t_object *oldobj, t_ray ray, t_vec3 offset)
{
	float		t;
	t_object	obj;
	t_vec3		p;
	t_vec3		v;
	float		d2;

	obj = *oldobj;
	obj.position = vec3_add(obj.position, offset);
	t = get_hit_distance_plane(&obj, ray, NULL);
	if (t < FLT_MAX && t > 0.0f)
	{
		p = vec3_add(ray.origin, vec3_multiply(ray.direction, t));
		v = vec3_substract(p, obj.position);
		d2 = vec3_dot(v, v);
		if (d2 <= obj.specific.cylinder.radius * obj.specific.cylinder.radius)
			return (t);
	}
	return (FLT_MAX);
}

float	get_disk_context(float t[3], t_object *obj, t_hit_payload *payload)
{
	if (t[1] < t[2] && t[1] != FLT_MAX)
	{
		payload->world_normal = obj->rotation;
		return (t[1]);
	}
	else if (t[2] != FLT_MAX)
	{
		payload->world_normal = vec3_multiply(obj->rotation, -1.0f);
		return (t[2]);
	}
	return (FLT_MAX);
}

float	get_hit_distance_cylinder(t_object *obj, t_ray ray,
	t_hit_payload *payload)
{
	float	t[3];
	t_vec3	hit_position;

	t[1] = get_hit_distance_disk(obj, ray,
			vec3_multiply(obj->rotation, obj->specific.cylinder.height / 2));
	t[2] = get_hit_distance_disk(obj, ray,
			vec3_multiply(obj->rotation, -obj->specific.cylinder.height / 2));
	t[0] = get_hit_distance_inf_cylinder(obj, ray, payload);
	if (t[0] == FLT_MAX)
		return (FLT_MAX);
	hit_position = vec3_add(ray.origin, vec3_multiply(ray.direction, t[0]));
	payload->world_normal = get_normal_inf_cylinder(obj, ray, t[0]);
	hit_position = vec3_add(hit_position, vec3_multiply(payload->world_normal,
				-obj->specific.cylinder.radius));
	if (vec3_dist_sqr(obj->position, hit_position)
		< (obj->specific.cylinder.height * 0.25f
			* obj->specific.cylinder.height))
		return (t[0]);
	return (get_disk_context(t, obj, payload));
}

t_vec3	get_normal_cylinder(t_object *obj, t_ray ray, t_hit_payload payload)
{
	(void)ray;
	(void)obj;
	return (payload.world_normal);
}

uint8_t	init_cylinder(t_engine *engine, char **args)
{
	t_object	obj;

	obj.type = &engine->types[CYLINDER];
	obj.get_hit_distance = get_hit_distance_cylinder;
	obj.get_normal = get_normal_cylinder;
	if (ft_atov3(&obj.position, args[1], rangef(FLT_MIN, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atov3(&obj.rotation, args[2], rangef(-1.0f, 1.0f)) == FAILURE)
		return (FAILURE);
	obj.rotation = vec3_normalize(obj.rotation);
	if (str_to_decimal(&obj.specific.cylinder.radius, args[3],
			FLOAT, rangef(0, FLT_MAX)) == FAILURE)
		return (FAILURE);
	obj.specific.cylinder.radius = obj.specific.cylinder.radius / 2.0f;
	if (str_to_decimal(&obj.specific.cylinder.height, args[4],
			FLOAT, rangef(0, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atoc(&obj.color, args[5]) == FAILURE)
		return (FAILURE);
	if (vector_add(&engine->objects, &obj) != 0)
		return (err(obj.type->name));
	return (SUCCESS);
}
