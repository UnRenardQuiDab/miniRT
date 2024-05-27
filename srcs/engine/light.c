/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 07:33:19 by lcottet           #+#    #+#             */
/*   Updated: 2024/05/27 15:05:09 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "engine.h"

#include <math.h>

bool	is_in_shadow(t_engine *engine, t_hit_payload *payload,
	t_object *light, t_vec3 light_dir)
{
	t_hit_payload	light_payload;

	if (engine->frame_details.lights == NO_SHADOW
		|| engine->frame_details.lights == AMBIENT_ONLY)
		return (false);
	light_payload = trace_ray(engine, (t_ray){
			vec3_add(payload->world_position,
				vec3_multiply(payload->world_normal, 0.001f)),
			vec3_multiply(light_dir, -1.0f)
		});
	if (light_payload.hit_distance != -1
		&& vec3_dist_sqr(payload->world_position, light->position)
		> light_payload.hit_distance * light_payload.hit_distance)
		return (true);
	return (false);
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

t_vec3	apply_color_object(t_vec3 light_color, t_object *object,
	t_hit_payload	*payload)
{
	t_vec3	albedo;

	albedo = texture_get_value(&object->material.texture,
			object->material.color, payload->uv);
	//light_color.x = payload->uv.x;
	//light_color.y = payload->uv.y;
	//light_color.z = 0;
	//if (payload->uv.x > 1 || payload->uv.y > 1)
	//	light_color.z = 1;
	light_color.x *= albedo.x;
	light_color.y *= albedo.y;
	light_color.z *= albedo.z;
	return (light_color);
}

t_vec3	compute_light_colors(t_engine *engine, t_hit_payload *payload,
	t_ray ray)
{
	t_vec3		light_color;
	t_object	*light;
	t_vec3		light_dir;
	size_t		i;

	light_color = vec3_multiply(
			color_to_vec3(engine->ambient.color), engine->ambient.lighting);
	i = 0;
	while (i < engine->lights.len
		&& engine->frame_details.lights != AMBIENT_ONLY)
	{
		light = (t_object *)engine->lights.tab + i;
		light_dir = vec3_normalize(
				vec3_substract(payload->world_position, light->position));
		if (is_in_shadow(engine, payload, light, light_dir))
		{
			i++;
			continue ;
		}
		light_color = vec3_add(light_color,
				get_light_color(light, payload, light_dir, ray));
		i++;
	}
	return (apply_color_object(light_color, payload->object, payload));
}
