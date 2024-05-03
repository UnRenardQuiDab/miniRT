/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:51:41 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/03 18:55:53 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <stdint.h>

# include "vector.h"
# include "color.h"

# define OBJECT_CAMERA "C"
# define OBJECT_AMBIENT "A"
# define OBJECT_LIGHT "L"
# define OBJECT_PLANE "pl"
# define OBJECT_SPHERE "sp"
# define OBJECT_CYLINDER "cy"

typedef char*	t_obj_type;

typedef struct s_3dvector
{
	float	x;
	float	y;
	float	z;
}	t_3dvector;

typedef struct s_camera
{
	t_3dvector	position;
	t_3dvector	orientation;
	uint8_t		fov;
}				t_camera;

typedef struct s_object
{
	t_obj_type	type;
	t_3dvector	position;
	t_color		color;
	void		*specific;
}	t_object;

typedef struct t_ambient
{
	t_color	color;
	float	ratio;
}	t_ambient;

typedef struct s_engine
{
	t_vector		*objects;
	t_camera		camera;
	t_ambient		ambient;
}				t_engine;

#endif