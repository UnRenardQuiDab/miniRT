/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:58:43 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/07 23:54:59 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "engine.h"
#include "mlx.h"
#include <stddef.h>
#include <math.h>

#include <stdio.h>

t_color	get_pixel_color(t_engine *engine, t_vec2 pos)
{
	(void) engine;
	t_color	color;
	t_vec3	ray_dir;
	float	radius;

	radius = 0.5f;
	ray_dir = (t_vec3){{pos.x, pos.y, -1.0f}};
	float a = vec3_dot(ray_dir, ray_dir);
	float b = 2.0f * vec3_dot(engine->camera.position, ray_dir);
	float c = vec3_dot(engine->camera.position, engine->camera.position) - radius * radius;
	t_vec3	light_dir = (t_vec3){{-1, -1, -1}};
	t_vec3	light_dir2 = (t_vec3){{-1, -1, -1}};
	light_dir = vec3_normalize(light_dir);
	light_dir2 = vec3_normalize(light_dir2);
	
	float discriminant = b * b - 4.0f * a * c;

	color.color = 0;
	if (discriminant >= 0)
	{
		float t0 = (-b - sqrt(discriminant)) / (2.0f * a);
		//float t1 = (b + sqrt(discriminant)) / (2 * a);

		t_vec3 hit_pos_0 = vec3_add(engine->camera.position, vec3_multiply(ray_dir, t0));
		//t_vec3 hit_pos_1 = vec3_add(engine->camera.position, vec3_multiply(ray_dir, t1));
		
		//t_vec3 norm = vec3_substract(hit_pos_0, (t_vec3){{0, 0, 0}});
		t_vec3 norm = vec3_normalize(hit_pos_0);

		float light = vec3_dot(norm, vec3_multiply(light_dir, -1.0));
		float light2 = vec3_dot(norm, vec3_multiply(light_dir2, -1.0));
		if (light < 0.0f)
			light = 0.0f;
		if (light2 < 0.0f)
			light2 = 0.0f;
		else if (light2 > light)
			light = light2;
		
		color.r = (light) * 255;
		color.g = (light) * 255;
		color.b = (light) * 255;

	}
	return (color);
}

void	render(t_engine *engine)
{
	t_vec2	pos;
	float	aspect_ratio;

	aspect_ratio = WIDTH / (float) HEIGHT;
	pos.y = 0;
	while (pos.y < HEIGHT)
	{
		pos.x = 0;
		while (pos.x < WIDTH)
		{	
			put_pixel(&engine->mlx.img, pos.x, pos.y,
				get_pixel_color(engine, (t_vec2){{
					((pos.x / WIDTH) * 2.0f - 1.0f) * tan((float)engine->camera.fov / 2.0f) * aspect_ratio ,
					((1.0f - pos.y / HEIGHT) * 2.0f - 1.0f) * tan((float)engine->camera.fov / 2.0f)}}
					).color);
			pos.x++;
		}
		pos.y++;
	}
	mlx_put_image_to_window(engine->mlx.mlx, engine->mlx.win,
		engine->mlx.img.img, 0, 0);
}
