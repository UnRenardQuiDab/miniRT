/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:29:49 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/09 18:55:03 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

#include "color.h"

typedef union u_vec2
{
	struct
	{
		float	x;
		float	y;
	};
	float	arr[2];
}	t_vec2;

typedef union u_vec3
{
	struct
	{
		float	x;
		float	y;
		float	z;
	};
	float	arr[3];
}	t_vec3;

t_vec3	vec3_multiply(t_vec3 a, float b);
float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_product(t_vec3 a, t_vec3 b);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_substract(t_vec3 a, t_vec3 b);
t_vec3	vec3_normalize(t_vec3 a);
t_vec3	vec3_reflect(t_vec3 incident, t_vec3 normal);
t_vec3	color_to_vec3(t_color color);
t_color	vec3_to_color(t_vec3 vec);

#endif
