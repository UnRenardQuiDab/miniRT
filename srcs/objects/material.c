/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwisniew <bwisniew@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:09:10 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/23 14:27:22 by bwisniew         ###   ########.fr       */
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
//	float		reflection;
//	float		opacity;
//	float		refraction;

uint8_t	init_texture(char *path, t_texture *texture, t_engine *engine)
{
	if (ft_strcmp(path, "NONE") == 0)
	{
		ft_memset(texture, 0, sizeof(t_texture));
		return (SUCCESS);
	}
	texture->mlx_img = mlx_xpm_file_to_image(engine->mlx.mlx, path, &texture->width, &texture->height);
	if (texture->mlx_img == NULL)
		return (FAILURE);
	texture->addr = mlx_get_data_addr(texture->mlx_img, &texture->bpp, &texture->line_length, &texture->endian);
	if (texture->addr == NULL)
		return (FAILURE);
	return (SUCCESS);
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
	if (vector_add(&engine->materials, &material))
		return (FAILURE);
	if (init_texture(args[3], &material.texture, engine) == FAILURE)
		return (custom_error(args[3], ERR_TEXTURE_INIT));
	if (init_texture(args[4], &material.bumpmap, engine) == FAILURE)
		return (mlx_destroy_image(engine->mlx.mlx, material.texture.mlx_img),
			custom_error(args[4], ERR_TEXTURE_INIT));
	return (SUCCESS);
}
