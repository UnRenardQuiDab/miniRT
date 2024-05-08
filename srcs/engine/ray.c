/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:10:01 by lcottet           #+#    #+#             */
/*   Updated: 2024/05/08 22:32:20 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static t_hit_payload	hit(t_hit_payload payload, t_ray ray)
{
	t_vec3	origin;

	origin = vec3_substract(ray.origin, payload.object->position);
	payload.world_position = vec3_add(origin,
			vec3_multiply(ray.direction, payload.hit_distance));
	payload.world_normal = payload.object->get_normal(payload.object,
			payload.world_position);

	payload.world_position = vec3_add(payload.world_position, payload.object->position);
	return (payload);
}

static t_hit_payload	miss(t_hit_payload payload)
{
	payload.hit_distance = -1;
	return (payload);
}

t_hit_payload	trace_ray(t_engine *engine, t_ray ray)
{
	t_hit_payload	payload;
	size_t			i;
	float			current_dist;

	payload.hit_distance = FLT_MAX;
	payload.object = NULL;
	i = 0;
	while (i < engine->objects.len)
	{
		t_object	*obj = ((t_object *)engine->objects.tab) + i;
		current_dist = obj->get_hit_distance(obj, ray);
		if (current_dist < payload.hit_distance && current_dist > 0.0f)
		{
			payload.object = obj;
			payload.hit_distance = current_dist;
		}
		i++;
	}
	if (payload.object == NULL)
		return (miss(payload));
	return (hit(payload, ray));
}
