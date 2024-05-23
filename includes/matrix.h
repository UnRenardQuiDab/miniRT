/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:54:02 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/21 17:37:29 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vec.h"

typedef struct s_mat4
{
	float	matrix[16];
}	t_mat4;

typedef struct s_mat3
{
	float	matrix[9];
}	t_mat3;

t_mat4	mat4_init(float a);
t_mat4	mat4_rotate(t_mat4 mat, float angle, t_vec3 vec);
t_mat4	mat4_multiply(t_mat4 a, t_mat4 b);
t_mat4	mat4_translate(t_mat4 mat, t_vec3 vec);
t_mat4	mat4_identity(void);
t_mat4	mat4_inverse(t_mat4 matrix);
t_mat3	mat3_init(float a);
t_mat3	mat3_multiply(t_mat3 a, t_mat3 b);
t_mat3	mat3_rotate(float angle, t_vec3 vec);

#endif