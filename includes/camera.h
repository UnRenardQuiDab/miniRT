/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:16:10 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/15 17:07:27 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "object.h"

typedef struct s_camera
{
	t_vec3		position;
	t_vec3		rotation;
	t_vec3		up;
	int32_t		fov;
	t_mat4		projection;
	t_mat4		view;
	double		rad_fov;
	double		far;
	double		near;
	double		aspect_ratio;
}				t_camera;

void	project_camera(t_camera *camera);
void	mat4_perspective(t_camera *camera);
void	mat4_view(t_camera *camera);

#endif