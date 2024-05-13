/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 07:33:19 by lcottet           #+#    #+#             */
/*   Updated: 2024/05/13 21:41:16 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"
#include "engine.h"

bool	is_in_shadow(t_engine *engine, t_hit_payload *payload,
	t_object *light, t_vec3 light_dir)
{
	t_hit_payload	light_payload;

	light_payload = trace_ray(engine, (t_ray){
			vec3_add(payload->world_position,
				vec3_multiply(payload->world_normal, 0.0001f)),
			vec3_multiply(light_dir, -1.0f)
		});
	if (light_payload.hit_distance != -1
		&& vec3_dist_sqr(payload->world_position, light->position)
		> light_payload.hit_distance * light_payload.hit_distance)
		return (true);
	return (false);
}

t_vec3	get_light_color(t_object *light, t_hit_payload *payload,
	t_vec3 light_dir)
{
	float	flight;

	flight = vec3_dot(payload->world_normal,
			vec3_multiply(light_dir,
				-1.0f * (light->specific.light.brightness)));
	if (flight < 0)
		flight = 0;
	return (vec3_multiply(color_to_vec3(light->color), flight));
}

t_vec3	apply_color_object(t_vec3 light_color, t_object *object)
{
	light_color.x *= color_to_vec3(object->color).x;
	light_color.y *= color_to_vec3(object->color).y;
	light_color.z *= color_to_vec3(object->color).z;
	return (light_color);
}

t_vec3	compute_light_colors(t_engine *engine, t_hit_payload *payload)
{
	t_vec3		light_color;
	t_object	*light;
	t_vec3		light_dir;
	size_t		i;

	light_color = vec3_multiply(
			color_to_vec3(engine->ambient.color), engine->ambient.lighting);
	i = 0;
	while (i < engine->lights.len)
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
				get_light_color(light, payload, light_dir));
		i++;
	}
	return (apply_color_object(light_color, payload->object));
}
