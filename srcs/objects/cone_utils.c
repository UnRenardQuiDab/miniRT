/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 19:28:12 by bwisniew          #+#    #+#             */
/*   Updated: 2024/06/07 19:37:47 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_vec3	calculate_normal(t_object *obj, t_ray ray, float t)
{
	float	dot_cp;
	t_vec3	cp;

	cp = vec3_substract(vec3_add(ray.origin, vec3_multiply(ray.direction, t)),
			obj->position);
	dot_cp = vec3_dot(cp, cp);
	return (vec3_normalize(vec3_substract(vec3_divide(vec3_multiply(cp,
						vec3_dot(obj->rotation, cp)),
					(t_vec3){{dot_cp, dot_cp, dot_cp}}),
			obj->rotation)));
}

float	choose_t_cone(t_object *obj, t_ray ray, t_hit_payload *payload,
		float ts[3])
{
	float	t;
	float	h;
	t_vec3	cp;

	t = ts[0];
	if (t < 0.0f || (ts[1] > 0.0f && ts[1] < t))
		t = ts[1];
	if (ts[2] != FLT_MAX && (obj->is_inside || ts[2] < t))
		return (ts[2]);
	cp = vec3_substract(vec3_add(ray.origin, vec3_multiply(ray.direction, t)),
			obj->position);
	h = vec3_dot(cp, obj->rotation);
	if (h < 0.0f || h > obj->specific.cone.height)
	{
		if (h < 0.0f && ts[2] != FLT_MAX)
		{
			if (t == ts[0])
				t = ts[1];
		}
		else
			return (ts[2]);
	}
	payload->world_normal = calculate_normal(obj, ray, t);
	return (t);
}
