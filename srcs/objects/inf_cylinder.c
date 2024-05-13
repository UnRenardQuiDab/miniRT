/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inf_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 06:04:33 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/13 21:04:33 by lcottet          ###   ########.fr       */
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
