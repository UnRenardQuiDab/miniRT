/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 07:33:19 by lcottet           #+#    #+#             */
/*   Updated: 2024/06/03 16:23:31 by lcottet          ###   ########.fr       */
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

t_vec3	compute_normal_lighting(t_object *light, t_hit_payload *payload,
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

t_vec3	compute_light_color(t_engine *engine, t_object *l,
	t_hit_payload *payload, t_ray ray)
{
	t_vec3	color;
	t_vec4	shadow;
	t_vec3	l_dir;

	color = (t_vec3){{0.0f, 0.0f, 0.0f}};
	l_dir = vec3_normalize(
			vec3_substract(payload->world_position, l->position));
	color = vec3_add(color, compute_normal_lighting(l, payload, l_dir, ray));
	shadow = trace_shadow_color(engine, l_dir, l, payload);
	if (color.x == 0 && color.y == 0 && color.z == 0)
		shadow.w *= 1.0f - payload->object->material.opacity;
	color = vec3_multiply(color, 1.0f - shadow.w);
	color = vec3_add(color, vec3_multiply(shadow.xyz, shadow.w));
	return (color);
}

t_vec3	compute_lights_colors(t_engine *engine, t_hit_payload *payload,
	t_ray ray)
{
	t_vec3		total_color;
	t_vec3		curr_color;
	t_object	*light;
	size_t		i;

	total_color = vec3_multiply(color_to_vec3(engine->ambient.color),
			engine->ambient.lighting);
	i = 0;
	while (i < engine->lights.len
		&& engine->frame_details.lights != AMBIENT_ONLY)
	{
		light = (t_object *)engine->lights.tab + i++;
		curr_color = compute_light_color(engine, light, payload, ray);
		total_color = vec3_add(total_color, curr_color);
	}
	return (apply_color_object(total_color, payload->object, payload));
}
