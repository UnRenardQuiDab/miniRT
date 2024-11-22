/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:40:21 by lcottet           #+#    #+#             */
/*   Updated: 2024/06/07 19:38:19 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "file.h"
#include "ft_error.h"
#include <math.h>

bool	calculate_t_cone(t_object *obj, t_ray ray, double t[3])
{
	double	abc[3];
	double	cosa;
	t_vec3	co;
	double	det;

	cosa = cosf(obj->specific.cone.angle * M_PI / 180.0f);
	co = vec3_substract(ray.origin, obj->position);
	abc[0] = vec3_dot(ray.direction, obj->rotation) * vec3_dot(ray.direction,
			obj->rotation) - cosa * cosa;
	abc[1] = 2.0f * (vec3_dot(ray.direction, obj->rotation) * vec3_dot(co,
				obj->rotation) - vec3_dot(ray.direction, co) * cosa * cosa);
	abc[2] = vec3_dot(co, obj->rotation) * vec3_dot(co,
			obj->rotation) - vec3_dot(co, co) * cosa * cosa;
	det = abc[1] * abc[1] - 4.0f * abc[0] * abc[2];
	det = sqrt(det);
	if (det < 0.0f)
		return (false);
	t[0] = (-abc[1] - det) / (2.0f * abc[0]);
	t[1] = (-abc[1] + det) / (2.0f * abc[0]);
	t[2] = get_hit_distance_disk(obj, ray, vec3_multiply(obj->rotation,
				obj->specific.cone.height), obj->specific.cone.height
			* tanf(obj->specific.cone.angle * M_PI / 180.0f));
	return (true);
}

double	get_hit_distance_cone(t_object *obj, t_ray ray, t_hit_payload *payload)
{
	double	ts[3];
	double	t;

	if (calculate_t_cone(obj, ray, ts) == false)
		return (FLT_MAX);
	payload->world_normal = get_normal_plane(obj, ray, *payload);
	t = choose_t_cone(obj, ray, payload, ts);
	if (obj->is_inside && t != ts[2] && t != FLT_MAX)
		payload->world_normal = vec3_multiply(payload->world_normal, -1.0f);
	return (t);
}

t_vec3	get_normal_cone(t_object *obj, t_ray ray, t_hit_payload payload)
{
	(void)ray;
	(void)obj;
	return (payload.world_normal);
}

bool	is_inside_cone(t_object *obj, t_vec3 origin)
{
	double	curr_radius;
	t_vec3	cp;
	double	h;

	cp = vec3_substract(origin, obj->position);
	h = vec3_dot(cp, obj->rotation);
	if (h < 0.0f || h > obj->specific.cone.height)
		return (false);
	curr_radius = h * tanf(obj->specific.cone.angle * M_PI / 180.0f);
	if (curr_radius * curr_radius > vec3_dist_sqr(vec3_add(obj->position,
				vec3_multiply(obj->rotation, h)), origin))
		return (true);
	return (false);
}

uint8_t	init_cone(t_engine *engine, char **args)
{
	t_object	obj;

	obj.type = &engine->types[CONE];
	obj.get_hit_distance = get_hit_distance_cone;
	obj.get_normal = get_normal_cone;
	obj.is_inside_func = is_inside_cone;
	obj.get_uv = NULL;
	if (ft_atov3(&obj.position, args[1], rangef(FLT_MIN, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atov3(&obj.rotation, args[2], rangef(-1.0f, 1.0f)) == FAILURE)
		return (FAILURE);
	obj.rotation = vec3_normalize(obj.rotation);
	if (str_to_decimal(&obj.specific.cone.angle, args[3],
			FLOAT, rangef(0, 90)) == FAILURE)
		return (FAILURE);
	if (str_to_decimal(&obj.specific.cone.height, args[4],
			FLOAT, rangef(0, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atoc(&obj.material.color, args[5]) == FAILURE)
		return (FAILURE);
	obj.material = get_colored_material(obj.material.color);
	if (vector_add(&engine->objects, &obj) != 0)
		return (err(obj.type->name));
	return (SUCCESS);
}
