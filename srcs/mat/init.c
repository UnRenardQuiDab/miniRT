/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 19:04:28 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/21 17:36:33 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "libft.h"

t_mat3	mat3_init(double a)
{
	t_mat3	mat;

	mat = (t_mat3){{
		a, a, a,
		a, a, a,
		a, a, a
	}};
	return (mat);
}

t_mat4	mat4_init(double a)
{
	return ((t_mat4){{
			a, a, a, a,
			a, a, a, a,
			a, a, a, a,
			a, a, a, a
		}});
}
