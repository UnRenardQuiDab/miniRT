/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inf_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 06:04:33 by bwisniew          #+#    #+#             */
/*   Updated: 2024/06/03 17:55:44 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "engine.h"

#include <stdio.h>

t_vec3	get_normal_inf_cylinder(t_object *obj, t_ray ray, float t)
{
	t_vec3	ra;
	t_vec3	va;

	ra = vec3_product(obj->rotation, vec3_substract(ray.origin, obj->position));
	ra = vec3_product(ra, obj->rotation);
	va = vec3_product(obj->rotation, ray.direction);
	va = vec3_multiply(vec3_product(va, obj->rotation), t);
	if (obj->is_inside)
		return (vec3_multiply(vec3_normalize(vec3_add(ra, va)), -1.0f));
	return (vec3_normalize(vec3_add(ra, va)));
}

t_vec3	get_quadri_cylindre(t_object *obj, t_ray ray)
{
	t_vec3	abc;
	t_vec3	oc;
	float	dot_dir_rotation;
	float	dot_oc_rotation;

	oc = vec3_substract(ray.origin, obj->position);
	dot_oc_rotation = vec3_dot(oc, obj->rotation);
	dot_dir_rotation = vec3_dot(ray.direction, obj->rotation);
	abc.x = vec3_dot(ray.direction, ray.direction)
		- dot_dir_rotation * dot_dir_rotation;
	abc.y = 2 * (vec3_dot(ray.direction, oc)
			- dot_dir_rotation * dot_oc_rotation);
	abc.z = vec3_dot(oc, oc) - dot_oc_rotation * dot_oc_rotation
		- obj->specific.cylinder.radius * obj->specific.cylinder.radius;
	return (abc);
}

float	get_hit_distance_inf_cylinder(t_object *obj, t_ray ray,
	t_hit_payload *payload)
{
	t_vec3	abc;
	float	discriminant;
	float	sqrt_discriminant;
	float	delta[2];

	(void)payload;
	abc = get_quadri_cylindre(obj, ray);
	discriminant = abc.y * abc.y - 4 * abc.x * abc.z;
	if (discriminant < 0)
		return (FLT_MAX);
	sqrt_discriminant = sqrt(discriminant);
	delta[0] = (-abc.y + sqrt_discriminant) / (2.0f * abc.x);
	if (obj->is_inside)
		return (delta[0]);
	delta[1] = (-abc.y - sqrt_discriminant) / (2.0f * abc.x);
	if (delta[0] < delta[1])
		return (delta[0]);
	return (delta[1]);
}

t_vec2	get_uv_inf_cylinder(t_object *obj, t_hit_payload *payload)
{
	t_vec2	uv;
	//float	phi = acos(obj->rotation.y) * 180 / M_PI;

	t_mat3	rotation = mat3_rotate(obj.rotation.y, vec3_product(obj->rotation, (t_vec3){{0, 1, 0}}));
	t_vec3	position = mat3vec3_product(vec3_substract(payload->world_position, obj->position), rotation);

	float	theta = atan2(position.x, position.z);
	float	raw_u = theta / (2 * M_PI);
	uv.x = 1 - (raw_u + 0.5);
	uv.y = 1 - (position.y / (obj->specific.cylinder.height) + 0.5);
	return (uv);
}