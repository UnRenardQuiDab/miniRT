/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcottet <lcottet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:53:12 by bwisniew          #+#    #+#             */
/*   Updated: 2024/05/28 18:26:36 by lcottet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "engine.h"

void	free_textures(t_engine *engine)
{
	size_t		i;
	t_material	*material;

	i = 0;
	while (i < engine->materials.len)
	{
		material = &((t_material *)engine->materials.tab)[i];
		if (material->texture.mlx_img != NULL)
			mlx_destroy_image(engine->mlx.mlx, material->texture.mlx_img);
		if (material->bumpmap.mlx_img != NULL)
			mlx_destroy_image(engine->mlx.mlx, material->bumpmap.mlx_img);
		i++;
	}
}

int	exit_rt(t_engine *engine, int status)
{
	if (engine->frame_details.thread_count)
		join_threads(&engine->frame_details);
	vector_free(&engine->objects);
	vector_free(&engine->lights);
	free_textures(engine);
	vector_free(&engine->materials);
	if (engine->mlx.mlx != NULL)
		mlx_destroy_mlx(&engine->mlx);
	return (status);
}
