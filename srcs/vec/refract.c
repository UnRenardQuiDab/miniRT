/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:10:55 by lcottet           #+#    #+#             */
/*   Updated: 2024/05/28 18:08:13 by bwisniew         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vec.h"

t_vec3	vec3_refract(t_vec3 ray_dir, t_vec3 normal, double refract)
{
	t_vec3	refracted;
	double	cos_theta;
	double	sin_theta;

	cos_theta = -vec3_dot(ray_dir, normal);
	sin_theta = sqrt(1 - refract * refract * (1 - cos_theta * cos_theta));
	refracted = vec3_add(vec3_multiply(ray_dir, refract),
			vec3_multiply(normal, refract * cos_theta - sin_theta));
	return (refracted);
}
