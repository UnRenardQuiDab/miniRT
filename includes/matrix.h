/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 18:54:02 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/11 05:40:43 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vec.h"

typedef struct s_mat4
{
	float	matrix[16];
}	t_mat4;

t_mat4	mat4_init(float a);
t_mat4	mat4_rotate(t_mat4 mat, float angle, t_vec3 vec);
t_mat4	mat4_multiply(t_mat4 a, t_mat4 b);
t_mat4	mat4_translate(t_mat4 mat, t_vec3 vec);
t_mat4	mat4_identity(void);
t_mat4	mat4_inverse(t_mat4 matrix);

#endif