/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 22:14:03 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/11 05:32:39 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

t_mat4	mat4_identity(void)
{
	t_mat4	identity;

	identity = mat4_init(0.0f);
	identity.matrix[0] = 1.0f;
	identity.matrix[5] = 1.0f;
	identity.matrix[10] = 1.0f;
	identity.matrix[15] = 1.0f;
	return (identity);
}
