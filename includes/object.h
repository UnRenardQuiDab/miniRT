/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:21:49 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/13 20:56:13 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include <stdbool.h>
# include <stddef.h>

# include "color.h"
# include "vec.h"
# include "matrix.h"
# include "camera.h"

# define TYPE_COUNT 6

# define OBJECT_CAMERA "C"
# define OBJECT_AMBIENT "A"
# define OBJECT_LIGHT "L"
# define OBJECT_PLANE "pl"
# define OBJECT_SPHERE "sp"
# define OBJECT_CYLINDER "cy"

typedef struct s_engine			t_engine;
typedef struct s_ray			t_ray;
typedef struct s_hit_payload	t_hit_payload;
typedef struct s_mat4			t_mat4;

typedef enum e_type_index
{
	CAMERA,
	AMBIENT,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_type_index;

typedef struct s_obj_type
{
	t_type_index	index;
	char			*name;
	size_t			args_count;
	uint8_t			(*init)(t_engine * engine, char **args);
}	t_obj_type;

typedef struct t_ambient
{
	t_color	color;
	float	lighting;
}	t_ambient;

typedef struct s_light
{
	float	brightness;
}	t_light;

typedef struct s_sphere
{
	float	radius;
}	t_sphere;

typedef struct s_cylinder
{
	float	radius;
	float	height;
}	t_cylinder;

typedef union u_specific
{
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_light		light;
}	t_specific;

typedef struct s_object
{
	t_obj_type	*type;
	t_vec3		position;
	t_vec3		rotation;
	t_color		color;
	t_specific	specific;
	bool		is_inside;
	bool		(*is_inside_func)(struct s_object * self, t_vec3 origin);
	float		(*get_hit_distance)(struct s_object *self, t_ray ray,
			t_hit_payload *payload);
	t_vec3		(*get_normal)(struct s_object * self,
		t_ray ray, t_hit_payload payload);
}	t_object;

uint8_t	init_ambient(t_engine *engine, char **args);
uint8_t	init_camera(t_engine *engine, char **args);
uint8_t	init_light(t_engine *engine, char **args);
uint8_t	init_cylinder(t_engine *engine, char **args);
uint8_t	init_plane(t_engine *engine, char **args);
uint8_t	init_sphere(t_engine *engine, char **args);

float	get_hit_distance_plane(t_object *obj, t_ray ray,
			t_hit_payload *payload);
float	get_hit_distance_inf_cylinder(t_object *obj, t_ray ray,
			t_hit_payload *payload);
t_vec3	get_normal_inf_cylinder(t_object *obj, t_ray ray, float t);

float	get_disk_context(float t[3], t_object *obj, t_hit_payload *payload);
float	get_hit_distance_disk(t_object *oldobj, t_ray ray, t_vec3 offset);

#endif
