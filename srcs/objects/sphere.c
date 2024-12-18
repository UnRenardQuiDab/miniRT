/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:20:44 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/24 14:05:23 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "engine.h"
#include "ft_error.h"
#include "file.h"
#include "libft.h"

double	get_hit_distance_sphere(t_object *obj, t_ray ray,
	t_hit_payload *payload)
{
	t_vec3		ray_origin;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	(void)payload;
	ray_origin = vec3_substract(ray.origin, obj->position);
	a = vec3_dot(ray.direction, ray.direction);
	b = 2.0f * vec3_dot(ray_origin, ray.direction);
	c = vec3_dot(ray_origin, ray_origin) - obj->specific.sphere.radius
		* obj->specific.sphere.radius;
	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0)
		return (FLT_MAX);
	if (obj->is_inside)
		return ((-b + sqrt(discriminant)) / (2.0f * a));
	return ((-b - sqrt(discriminant)) / (2.0f * a));
}

bool	is_inside_sphere(t_object *obj, t_vec3 origin)
{
	return (vec3_dist_sqr(origin, obj->position)
		<= obj->specific.sphere.radius * obj->specific.sphere.radius);
}

t_vec3	get_normal_sphere(t_object *obj, t_ray ray, t_hit_payload payload)
{
	(void)ray;
	if (obj->is_inside)
		return (vec3_multiply(vec3_normalize(payload.world_position), -1.0f));
	return (vec3_normalize(payload.world_position));
}

t_vec2	get_uv_sphere(t_object *obj, t_hit_payload *payload)
{
	t_vec3	normal;
	t_vec2	uv;

	normal = vec3_normalize(
			vec3_substract(payload->world_position, obj->position));
	uv.x = 0.5f + atan2(normal.z, normal.x) / (2.0f * M_PI);
	uv.y = 0.5f - asin(normal.y) / M_PI;
	return (uv);
}

uint8_t	init_sphere(t_engine *engine, char **args)
{
	t_object	obj;

	obj.type = &engine->types[SPHERE];
	obj.get_hit_distance = get_hit_distance_sphere;
	obj.get_normal = get_normal_sphere;
	obj.is_inside_func = is_inside_sphere;
	obj.get_uv = get_uv_sphere;
	if (ft_atov3(&obj.position, args[1], rangef(FLT_MIN, FLT_MAX)) == FAILURE)
		return (FAILURE);
	if (str_to_decimal(&obj.specific.sphere.radius, args[2],
			FLOAT, rangef(0, FLT_MAX)) == FAILURE)
		return (FAILURE);
	obj.specific.sphere.radius /= 2.0f;
	if (ft_atom(engine, &obj.material, args[3]) == FAILURE)
		return (FAILURE);
	if (vector_add(&engine->objects, &obj) != 0)
		return (err(obj.type->name));
	return (SUCCESS);
}
