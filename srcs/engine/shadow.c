/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:16:53 by lcottet           #+#    #+#             */
/*   Updated: 2024/09/04 00:10:38 by lcottet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

t_vec4	get_shadow_color(t_vec4 shadow_color, t_object *light, t_ray ray,
		t_hit_payload hit)
{
	t_vec3	projected_color;

	ray.origin = light->position;
	ray.direction = vec3_multiply(ray.direction, -1.0f);
	hit.hit_distance = hit.object->get_hit_distance(hit.object, ray, &hit);
	hit.world_position = vec3_add(ray.origin,
			vec3_multiply(ray.direction, hit.hit_distance));
	if (hit.object->get_uv)
		hit.uv = hit.object->get_uv(hit.object, &hit);
	projected_color = apply_color_object(
			color_to_vec3(light->material.color), hit.object, &hit);
	projected_color = vec3_multiply(projected_color,
			hit.object->material.opacity);
	shadow_color.xyz = vec3_add(shadow_color.xyz, projected_color);
	shadow_color.w = 1.0f - (1.0f - shadow_color.w)
		* (1.0f - hit.object->material.opacity);
	return (shadow_color);
}

t_vec4	trace_shadow_color(t_engine *engine, t_vec3 l_dir,
		t_object *light, t_hit_payload *payload)
{
	size_t			i;
	t_vec4			shadow_color;
	t_hit_payload	hit;
	t_ray			ray;
	float			light_distance;

	ray = (t_ray){vec3_add(payload->world_position,
			vec3_multiply(l_dir, -0.001f)), vec3_multiply(l_dir, -1.0f)};
	i = 0;
	light_distance = vec3_dist_sqr(light->position, payload->world_position);
	shadow_color = (t_vec4){{1.0f, 1.0f, 1.0f, 0.0f}};
	while (i < engine->objects.len && engine->frame_details.lights == ALL)
	{
		hit.object = (t_object *)engine->objects.tab + i;
		hit.hit_distance = hit.object->get_hit_distance(hit.object, ray, &hit);
		if (hit.hit_distance >= 0
			&& hit.hit_distance * hit.hit_distance <= light_distance)
		{
			shadow_color = get_shadow_color(shadow_color, light, ray, hit);
		}
		i++;
	}
	shadow_color.xyz = vec3_multiply(shadow_color.xyz, 1.0f - shadow_color.w);
	return (shadow_color);
}
