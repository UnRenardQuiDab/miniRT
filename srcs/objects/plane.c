/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:20 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/26 19:33:00 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "libft.h"
#include "engine.h"
#include "ft_error.h"
#include "file.h"

float	get_hit_distance_plane(t_object *obj, t_ray ray, t_hit_payload *payload)
{
	float		t;
	float		discriment;

	(void)payload;
	discriment = vec3_dot(ray.direction, obj->rotation);
	if (discriment == 0)
		return (FLT_MAX);
	t = vec3_dot(obj->rotation, vec3_substract(obj->position, ray.origin))
		/ discriment;
	return (t);
}

t_vec3	get_normal_plane(t_object *obj, t_ray ray, t_hit_payload payload)
{
	(void)payload;
	if (vec3_dot(ray.direction, obj->rotation) > 0)
		return (vec3_multiply(obj->rotation, -1.0f));
	return (obj->rotation);
}

t_vec2	get_uv_plane(t_object *obj, t_hit_payload *payload)
{
	t_vec3	normal;
	t_vec3	u;
	t_vec3	v;
	t_vec2	uv;
	t_vec3 position = vec3_substract(payload->world_position, obj->position);
	normal = obj->rotation;
	float 	d = -normal.x * obj->position.x - normal.y * obj->position.y - normal.z * obj->position.z;
	if (normal.z != 0)
		u = (t_vec3) {{-1, 0, -(normal.x + normal.y + d) / normal.z}};
	else if (normal.y != 0)
		u = (t_vec3) {{-1 ,-(normal.x + normal.z + d) / normal.y, 0}};
	else
		u = (t_vec3) {{-(normal.y + normal.z + d) / normal.x, -1, 0}};

	(void) obj;
	u = vec3_normalize(u);
	v = vec3_product(normal, u);
	uv.x = vec3_dot(position, u);
	uv.y = vec3_dot(position, v);
	uv.x = uv.x - (int)uv.x;
	uv.y = uv.y - (int)uv.y;
	if (uv.x < 0)
		uv.x = 1 + uv.x;
	if (uv.y < 0)
		uv.y = 1 + uv.y;
	return (uv);
}

uint8_t	init_plane(t_engine *engine, char **args)
{
	t_object	obj;

	obj.type = &engine->types[PLANE];
	obj.get_hit_distance = get_hit_distance_plane;
	obj.get_normal = get_normal_plane;
	obj.is_inside_func = NULL;
	obj.get_uv = get_uv_plane;
	if (ft_atov3(&obj.position, args[1], rangef(FLT_MIN, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atov3(&obj.rotation, args[2], rangef(-1.0f, 1.0f)) == FAILURE)
		return (FAILURE);
	obj.rotation = vec3_normalize(obj.rotation);
	if (ft_atom(engine, &obj.material, args[3]) == FAILURE)
		return (FAILURE);
	if (vector_add(&engine->objects, &obj) == -1)
		return (err(obj.type->name));
	return (SUCCESS);
}
