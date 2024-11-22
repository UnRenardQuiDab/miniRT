/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:12:28 by lcottet           #+#    #+#             */
/*   Updated: 2024/06/07 19:37:47 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

double	get_hit_distance_disk(t_object *oldobj, t_ray ray, t_vec3 offset,
	double radius)
{
	double		t;
	t_object	obj;
	t_vec3		p;
	t_vec3		v;
	double		d2;

	obj = *oldobj;
	obj.position = vec3_add(obj.position, offset);
	t = get_hit_distance_plane(&obj, ray, NULL);
	if (t < FLT_MAX && t > 0.0f)
	{
		p = vec3_add(ray.origin, vec3_multiply(ray.direction, t));
		v = vec3_substract(p, obj.position);
		d2 = vec3_dot(v, v);
		if (d2 <= radius * radius)
			return (t);
	}
	return (FLT_MAX);
}

double	get_disk_context(double t[3], t_object *obj, t_hit_payload *payload)
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
