/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:29:49 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/11 07:55:53 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "color.h"

typedef struct s_mat4	t_mat4;

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

typedef union u_vec4
{
	struct
	{
		float	x;
		float	y;
		float	z;
		float	w;
	};
	float	arr[4];
}	t_vec4;

float	vec3_dot(t_vec3 a, t_vec3 b);
float	vec3_dist_sqr(t_vec3 a, t_vec3 b);
t_vec3	vec3_multiply(t_vec3 a, float b);
t_vec3	vec3_product(t_vec3 a, t_vec3 b);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_substract(t_vec3 a, t_vec3 b);
t_vec3	vec3_normalize(t_vec3 a);
t_vec3	vec3_reflect(t_vec3 incident, t_vec3 normal);
t_vec3	color_to_vec3(t_color color);
t_vec4	mat4vec4_product(t_vec4 vec, t_mat4 mat);
t_color	vec3_to_color(t_vec3 vec);

#endif
