/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 21:15:46 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/07 21:50:54 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

t_vec3	vec3_normalize(t_vec3 a)
{
	float	length;

	length = sqrt(vec3_dot(a, a));
	return ((t_vec3){{a.x / length, a.y / length, a.z / length}});
}