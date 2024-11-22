/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:09:10 by bwisniew          #+#    #+#             */
/*   Updated: 2024/06/11 12:38:12 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"
#include "ft_error.h"
#include "file.h"
#include "mlx.h"
#include "libft.h"

//	t_color		color;
//	t_texture	texture;
//	t_texture	bumpmap;
//	double		reflection;
//	double		opacity;
//	double		refraction;

t_vec3	texture_get_value(t_texture *texture, t_color accent, t_vec2 uv)
{
	int		x;
	int		y;
	t_vec3	color;

	if (texture->mlx_img == NULL)
		return (color_to_vec3(accent));
	x = (int)(uv.x * texture->width) % texture->width;
	y = (int)(uv.y * texture->height) % (texture->height);
	color.x = (unsigned char)texture->addr
	[(y * texture->line_length + x * (texture->bpp / 8)) + 2] / 255.0f;
	color.y = (unsigned char)texture->addr
	[(y * texture->line_length + x * (texture->bpp / 8)) + 1] / 255.0f;
	color.z = (unsigned char)texture->addr
	[(y * texture->line_length + x * (texture->bpp / 8))] / 255.0f;
	return (color);
}

uint8_t	init_texture(char *path, t_texture *texture, t_engine *engine)
{
	ft_memset(texture, 0, sizeof(t_texture));
	if (ft_strcmp(path, "NONE") == 0)
		return (SUCCESS);
	texture->mlx_img = mlx_xpm_file_to_image(engine->mlx.mlx,
			path, &texture->width, &texture->height);
	if (texture->mlx_img == NULL)
		return (FAILURE);
	texture->addr = mlx_get_data_addr(texture->mlx_img,
			&texture->bpp, &texture->line_length, &texture->endian);
	if (texture->addr == NULL)
		return (FAILURE);
	return (SUCCESS);
}

t_material	*get_material(t_engine *engine, int32_t id)
{
	size_t		i;
	t_material	*material;

	i = 0;
	while (i < engine->materials.len)
	{
		material = (t_material *)engine->materials.tab + i;
		if (material->id == id)
			return (material);
		i++;
	}
	return (NULL);
}

t_material	get_colored_material(t_color color)
{
	t_material	material;

	ft_memset(&material, 0, sizeof(t_material));
	material.id = -1;
	material.color = color;
	material.opacity = 1.0f;
	return (material);
}

uint8_t	init_material(t_engine *engine, char **args)
{
	t_material	material;

	if (str_to_decimal(&material.id, args[1], INT,
			rangei(INT32_MIN, INT32_MAX)) == FAILURE)
		return (FAILURE);
	if (ft_atoc(&material.color, args[2]) == FAILURE)
		return (FAILURE);
	if (str_to_decimal(&material.reflection, args[5], FLOAT,
			rangef(0.0f, 1.0f)) == FAILURE)
		return (FAILURE);
	if (str_to_decimal(&material.opacity, args[6], FLOAT,
			rangef(0.0f, 1.0f)) == FAILURE)
		return (FAILURE);
	if (str_to_decimal(&material.refraction, args[7], FLOAT,
			rangef(0.0f, 1.0f)) == FAILURE)
		return (FAILURE);
	if (init_texture(args[3], &material.texture, engine) == FAILURE)
		return (custom_error(args[3], ERR_TEXTURE_INIT));
	if (init_texture(args[4], &material.bumpmap, engine) == FAILURE)
		return (material_destroy_images(engine, &material),
			custom_error(args[4], ERR_TEXTURE_INIT));
	if (vector_add(&engine->materials, &material))
		return (material_destroy_images(engine, &material), FAILURE);
	return (SUCCESS);
}
