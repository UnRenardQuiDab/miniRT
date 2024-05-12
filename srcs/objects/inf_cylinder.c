/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inf_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 06:04:33 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/12 09:55:29 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "engine.h"


bool	is_in_inf_cylinder(t_object *obj, t_ray ray)
{

	t_vec3		translate_center;
	t_object	plane;
	float		h;

	plane.position = ray.origin;
	plane.rotation = obj->rotation;
	h = get_hit_distance_plane(&plane, (t_ray) {
		obj->position,
		obj->rotation
	}, NULL);
	translate_center = vec3_add(obj->position, vec3_multiply(obj->rotation, h));
	return (vec3_dist_sqr(translate_center, ray.origin)
		< obj->specific.cylinder.radius * obj->specific.cylinder.radius);
}

t_vec3	get_normal_inf_cylinder(t_object *obj, t_ray ray, float t)
{
	t_vec3	ra;
	t_vec3	va;

	ra = vec3_product(obj->rotation, vec3_substract(ray.origin, obj->position));
	ra = vec3_product(ra, obj->rotation);
	va = vec3_product(obj->rotation, ray.direction);
	va = vec3_multiply(vec3_product(va, obj->rotation), t);
	if (is_in_inf_cylinder(obj, ray))
		return (vec3_multiply(vec3_normalize(vec3_add(ra, va)), -1.0f));
	return (vec3_normalize(vec3_add(ra, va)));
}

float	get_hit_distance_inf_cylinder(t_object *obj, t_ray ray,
	t_hit_payload *payload)
{
	t_vec3	oc;
	t_vec3	co;
	t_vec3	abc;
	float	discriminant;
	float	delta[2];

	(void)payload;
	oc = vec3_substract(ray.origin, obj->position);
	co = vec3_substract(obj->position, ray.origin);
	abc.x = vec3_dot(ray.direction, ray.direction)
		- pow(vec3_dot(ray.direction, obj->rotation), 2);
	abc.y = 2 * (vec3_dot(ray.direction, oc)
			- vec3_dot(ray.direction, obj->rotation)
			* vec3_dot(oc, obj->rotation));
	abc.z = vec3_dot(oc, oc) - pow(vec3_dot(oc, obj->rotation), 2)
		- pow(obj->specific.cylinder.radius, 2);
	discriminant = abc.y * abc.y - 4 * abc.x * abc.z;
	if (discriminant < 0)
		return (FLT_MAX);
	delta[0] = (-abc.y + sqrt(discriminant)) / (2.0f * abc.x);
	delta[1] = (-abc.y - sqrt(discriminant)) / (2.0f * abc.x);
	if (delta[0] < delta[1])
		return (delta[0]);
	return (delta[1]);
}
