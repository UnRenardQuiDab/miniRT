/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 21:52:05 by lcottet           #+#    #+#             */
/*   Updated: 2024/05/11 05:36:45 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec3	vec3_reflect(t_vec3 incident, t_vec3 normal)
{
	t_vec3	reflected;

	reflected = vec3_substract(incident,
			vec3_multiply(normal, 2.0f * vec3_dot(incident, normal)));
	return (reflected);
}
