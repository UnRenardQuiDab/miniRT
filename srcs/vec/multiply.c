/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:15:46 by bwisniew          #+#    #+#             */
/*   Updated: 2024/06/01 10:06:24 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec3	vec3_multiply(t_vec3 a, float b)
{
	return ((t_vec3){{a.x * b, a.y * b, a.z * b}});
}

t_vec3	vec3_multiply_vec(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){{a.x * b.x, a.y * b.y, a.z * b.z}});
}
