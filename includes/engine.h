/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:51:41 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/06 18:39:25 by bwisniew         ###   ########.fr       */
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

# define FAILURE 1
# define SUCCESS 0

# define TYPE_COUNT 6

typedef struct s_engine t_engine;

typedef	struct s_obj_type
{
	size_t	index;
	char	*name;
	size_t	args_count;
	uint8_t	(*init)(t_engine *engine, char **);
}	t_obj_type;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_camera
{
	t_vec3		position;
	t_vec3		orientation;
	uint8_t		fov;
}				t_camera;

typedef struct s_sphere
{
	float	diameter;
}	t_sphere;

typedef struct s_cylinder
{
	float	diameter;
	float	height;
}	t_cylinder;

typedef struct s_light
{
	float	brightness;
}	t_light;

typedef union u_specific
{
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_light		light;
}	t_specific;

typedef struct s_object
{
	t_obj_type	type;
	t_vec3		position;
	t_vec3		rotation;
	t_color		color;
	t_specific	specific;
}	t_object;

typedef struct t_ambient
{
	t_color	color;
	float	ratio;
}	t_ambient;

typedef struct s_engine
{
	t_obj_type		types[TYPE_COUNT];
	t_vector		objects;
	t_camera		camera;
	t_ambient		ambient;
}				t_engine;

#endif