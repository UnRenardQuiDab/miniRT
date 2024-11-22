/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disturb_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 17:48:12 by bwisniew          #+#    #+#             */
/*   Updated: 2024/11/22 13:22:11 by lcottet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_ray	get_refracted_ray(t_ray ray, t_hit_payload payload)
{
	ray.direction = vec3_refract(ray.direction, payload.world_normal,
			payload.object->material.refraction);
	ray.origin = vec3_add(payload.world_position,
			vec3_multiply(payload.world_normal, -FLT_EPSILON));
	return (ray);
}

t_ray	get_reflected_ray(t_ray ray, t_hit_payload payload)
{
	ray.direction = vec3_reflect(ray.direction, payload.world_normal);
	ray.origin = vec3_add(payload.world_position,
			vec3_multiply(payload.world_normal, FLT_EPSILON));
	return (ray);
}
