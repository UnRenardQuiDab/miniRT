/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 07:33:19 by lcottet           #+#    #+#             */
/*   Updated: 2024/06/01 12:20:29 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "engine.h"

#include <math.h>

t_vec3	apply_color_object(t_vec3 light_color, t_object *object,
	t_hit_payload	*payload)
{
	t_vec3	albedo;

	albedo = texture_get_value(&object->material.texture,
			object->material.color, payload->uv);
	light_color = vec3_multiply_vec(light_color, albedo);
	return (light_color);
}

t_vec4	get_shadow_color(t_vec4 shadow_color, t_object *light, t_ray ray,
		t_hit_payload hit)
{
	t_vec3	projected_color;

	ray.origin = light->position;
	ray.direction = vec3_multiply(ray.direction, -1.0f);
	hit.hit_distance = hit.object->get_hit_distance(hit.object, ray, &hit);
	hit.world_position = vec3_add(ray.origin,
			vec3_multiply(ray.direction, hit.hit_distance));
	hit.uv = hit.object->get_uv(hit.object, &hit);
	projected_color = apply_color_object(
			color_to_vec3(light->material.color), hit.object, &hit);
	shadow_color.xyz = vec3_multiply_vec(shadow_color.xyz,
			vec3_multiply(projected_color,
				1.0f - hit.object->material.opacity));
	if (shadow_color.w < hit.object->material.opacity)
		shadow_color.w = hit.object->material.opacity;
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
	return (shadow_color);
}

t_vec3	get_light_color(t_object *light, t_hit_payload *payload,
	t_vec3 light_dir, t_ray ray)
{
	float	flight;
	float	specular;

	flight = vec3_dot(payload->world_normal,
			vec3_multiply(light_dir,
				-1.0f * (light->specific.light.brightness)));
	if (flight < 0)
		flight = 0;
	if (payload->object->material.reflection == 0)
		return (vec3_multiply(color_to_vec3(light->material.color), flight));
	specular = vec3_dot(vec3_reflect(light_dir, payload->world_normal),
			vec3_multiply(ray.direction, -1.0f));
	if (specular < 0)
		specular = 0;
	specular = pow(specular, 100) * payload->object->material.reflection;
	flight += specular;
	return (vec3_multiply(color_to_vec3(light->material.color), flight));
}

t_vec3	compute_light_colors(t_engine *engine, t_hit_payload *payload,
	t_ray ray)
{
	t_vec3		l_color;
	t_object	*l;
	t_vec3		l_dir;
	t_vec4		shadow;
	size_t		i;

	l_color = (t_vec3){{0.0f, 0.0f, 0.0f}};
	i = 0;
	while (i < engine->lights.len
		&& engine->frame_details.lights != AMBIENT_ONLY)
	{
		l = (t_object *)engine->lights.tab + i++;
		l_dir = vec3_normalize(
				vec3_substract(payload->world_position, l->position));
		l_color = vec3_add(l_color, get_light_color(l, payload, l_dir, ray));
		shadow = trace_shadow_color(engine, l_dir, l, payload);
		if (l_color.x == 0 && l_color.y == 0 && l_color.z == 0)
			shadow.w *= 1.0f - payload->object->material.opacity;
		l_color = vec3_multiply(l_color, 1.0f - shadow.w);
		l_color = vec3_add(l_color, vec3_multiply(shadow.xyz, shadow.w));
	}
	l_color = vec3_add(l_color, vec3_multiply(color_to_vec3(
					engine->ambient.color), engine->ambient.lighting));
	return (apply_color_object(l_color, payload->object, payload));
}
